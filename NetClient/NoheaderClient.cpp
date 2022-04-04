#include "pch.h"
#include <WinSock2.h>
#include "NoheaderClient.h"
#include <WS2tcpip.h>						// InetPton
#pragma comment(lib, "WS2_32.lib")

NoheaderClient::NoheaderClient()
{
	InitObject();
}

NoheaderClient::~NoheaderClient()
{
	// 사용중인 소켓을 제거
	CloseSocket();
	// 수신용 메모리를 해제
	if (mp_net_data != nullptr) { delete[] mp_net_data; }
	WSACleanup();			// 소켓중지
}

// 초기화용 함수, 내부호출용
void NoheaderClient::InitObject()
{
	WSADATA temp;
	WSAStartup(0x0202, &temp);

	mh_socket = INVALID_SOCKET;
	m_is_connected = FALSE;
	m_connect_msg_id = CONNECTED;
	m_close_msg_id = DISCONNECTED;
	m_read_msg_id = RECV_DATA;
	mp_notify_wnd = nullptr;
	m_nSoketIdx = -1;
}

void NoheaderClient::SendFrameData(const void* ap_data, int a_size)
{
	m_net_size = a_size;
	char* p_data = new char[a_size];
	memcpy(p_data, ap_data, a_size);
	send(mh_socket, p_data, a_size, 0);
	delete[] p_data;
}

void NoheaderClient::ConnectToServer(const TCHAR* ap_ip_address, int a_port, CWnd* ap_notify_wnd, int a_connect_id, int a_read_id, int a_close_id)
{
	if (mh_socket == INVALID_SOCKET) {
		m_connect_msg_id = a_connect_id;
		m_read_msg_id = a_read_id;
		m_close_msg_id = a_close_id;
		// 메시지를 수신할 화면
		mp_notify_wnd = ap_notify_wnd;
		mh_socket = socket(AF_INET, SOCK_STREAM, 0);

		sockaddr_in addr_data = { AF_INET, htons(a_port), };
		InetPton(AF_INET, ap_ip_address, &addr_data.sin_addr.s_addr);				// IP 유니코드를 정수값으로 바꿈
		// FD_CONNECT 비동기 : 해당 화면으로 a_connect_id의 메시지를 보낸다.
		WSAAsyncSelect(mh_socket, ap_notify_wnd->m_hWnd, CONNECTED, FD_CONNECT);
		m_is_connected = TRUE;
		connect(mh_socket, (sockaddr*)&addr_data, sizeof(addr_data));
	}
}

void NoheaderClient::CloseSocket()
{
	if (mh_socket != INVALID_SOCKET) {
		closesocket(mh_socket);
		mh_socket = INVALID_SOCKET;
		m_is_connected = FALSE;
	}
}

int NoheaderClient::RecvData(char* ap_data, int a_size)
{
	int total_size = 0, read_size, retry_count = 0;
	// 보내온 크기만큼 모두 수신할때까지 시도한다.
	while (total_size < a_size)
	{
		read_size = recv(mh_socket, ap_data + total_size, a_size - total_size, 0);
		if (read_size == SOCKET_ERROR || read_size == 0) {				// 읽기 실패
			Sleep(10);
			retry_count++;
			if (retry_count > 300) { break; }
		}
		else {
			retry_count = 0;
			total_size += read_size;				// 수신 데이터크기 합산
		}
	}
	return total_size;			// 수신한 모든 데이터를 출력
}

int NoheaderClient::BeginNetworkProcess()
{
	WSAAsyncSelect(mh_socket, mp_notify_wnd->m_hWnd, DISCONNECTED, FD_CLOSE);
	BOOL state = FALSE;
	// 데이터 크기가 0보다 크면 수신
	if (m_net_size > 0) {
		mp_net_data = new char[m_net_size];				// delete[]는 BeginNetworkProcess()를 사용하는 메시지처리부에서
		state = m_net_size == RecvData(mp_net_data, m_net_size);
	}
	return state;		// 수신 상태를 리턴
}

// 메시지 정상수신 후 마무리 작업하고 FD_READ 재설정하기
void NoheaderClient::EndNetworkProcess()
{
	//WSAAsyncSelect(mh_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_READ | FD_CLOSE);
}

// 대화상자에서 만들수도 있지만 이 함수만 호출하면 될 수 있도록 만든 메시지에 대한 처리함수(사용안하고 대화상자에서 다시 만들어야함)
void NoheaderClient::MessageProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == m_connect_msg_id) {
		if (WSAGETSELECTERROR(lParam)) { CloseSocket(); }
		else {
			m_is_connected = TRUE;
			WSAAsyncSelect(mh_socket, mp_notify_wnd->m_hWnd, RECV_DATA, FD_READ);
		}
		// 연결시 추가작업하고 싶은게 있으면 이 함수에 재정의로 작성해넣기
		ConnectedProcess();
	}
	else if (msg == m_read_msg_id) {
		if (WSAGETSELECTEVENT(lParam) == FD_READ) {
			if (BeginNetworkProcess()) {
				if(ProcessNetMessage()){
					// 메시지 정상수신 후 마무리 작업하고 FD_READ 재설정하기 (FD_CLOSE 추가처리 안해줘도 되는지 점검하기)
					WSAAsyncSelect(mh_socket, mp_notify_wnd->m_hWnd, RECV_DATA, FD_READ);
				}
				if (mp_net_data != NULL) {
					delete[] mp_net_data;
					mp_net_data = NULL;
				}
			}
			else {					// 비정상메시지 종료시키기
				CloseSocket();
				ClosedProcess(1);			// 오류로 종료
			}
		}
	}
	else if (msg == m_close_msg_id) {
		if (WSAGETSELECTEVENT(lParam) == FD_CLOSE) {
			CloseSocket();
			ClosedProcess(0);				// 정상 종료 FD_CLOSE
		}
	}
}
