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
	// ������� ������ ����
	CloseSocket();
	// ���ſ� �޸𸮸� ����
	if (mp_net_data != nullptr) { delete[] mp_net_data; }
	WSACleanup();			// ��������
}

// �ʱ�ȭ�� �Լ�, ����ȣ���
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
		// �޽����� ������ ȭ��
		mp_notify_wnd = ap_notify_wnd;
		mh_socket = socket(AF_INET, SOCK_STREAM, 0);

		sockaddr_in addr_data = { AF_INET, htons(a_port), };
		InetPton(AF_INET, ap_ip_address, &addr_data.sin_addr.s_addr);				// IP �����ڵ带 ���������� �ٲ�
		// FD_CONNECT �񵿱� : �ش� ȭ������ a_connect_id�� �޽����� ������.
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
	// ������ ũ�⸸ŭ ��� �����Ҷ����� �õ��Ѵ�.
	while (total_size < a_size)
	{
		read_size = recv(mh_socket, ap_data + total_size, a_size - total_size, 0);
		if (read_size == SOCKET_ERROR || read_size == 0) {				// �б� ����
			Sleep(10);
			retry_count++;
			if (retry_count > 300) { break; }
		}
		else {
			retry_count = 0;
			total_size += read_size;				// ���� ������ũ�� �ջ�
		}
	}
	return total_size;			// ������ ��� �����͸� ���
}

int NoheaderClient::BeginNetworkProcess()
{
	WSAAsyncSelect(mh_socket, mp_notify_wnd->m_hWnd, DISCONNECTED, FD_CLOSE);
	BOOL state = FALSE;
	// ������ ũ�Ⱑ 0���� ũ�� ����
	if (m_net_size > 0) {
		mp_net_data = new char[m_net_size];				// delete[]�� BeginNetworkProcess()�� ����ϴ� �޽���ó���ο���
		state = m_net_size == RecvData(mp_net_data, m_net_size);
	}
	return state;		// ���� ���¸� ����
}

// �޽��� ������� �� ������ �۾��ϰ� FD_READ �缳���ϱ�
void NoheaderClient::EndNetworkProcess()
{
	//WSAAsyncSelect(mh_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_READ | FD_CLOSE);
}

// ��ȭ���ڿ��� ������� ������ �� �Լ��� ȣ���ϸ� �� �� �ֵ��� ���� �޽����� ���� ó���Լ�(�����ϰ� ��ȭ���ڿ��� �ٽ� ��������)
void NoheaderClient::MessageProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == m_connect_msg_id) {
		if (WSAGETSELECTERROR(lParam)) { CloseSocket(); }
		else {
			m_is_connected = TRUE;
			WSAAsyncSelect(mh_socket, mp_notify_wnd->m_hWnd, RECV_DATA, FD_READ);
		}
		// ����� �߰��۾��ϰ� ������ ������ �� �Լ��� �����Ƿ� �ۼ��سֱ�
		ConnectedProcess();
	}
	else if (msg == m_read_msg_id) {
		if (WSAGETSELECTEVENT(lParam) == FD_READ) {
			if (BeginNetworkProcess()) {
				if(ProcessNetMessage()){
					// �޽��� ������� �� ������ �۾��ϰ� FD_READ �缳���ϱ� (FD_CLOSE �߰�ó�� �����൵ �Ǵ��� �����ϱ�)
					WSAAsyncSelect(mh_socket, mp_notify_wnd->m_hWnd, RECV_DATA, FD_READ);
				}
				if (mp_net_data != NULL) {
					delete[] mp_net_data;
					mp_net_data = NULL;
				}
			}
			else {					// ������޽��� �����Ű��
				CloseSocket();
				ClosedProcess(1);			// ������ ����
			}
		}
	}
	else if (msg == m_close_msg_id) {
		if (WSAGETSELECTEVENT(lParam) == FD_CLOSE) {
			CloseSocket();
			ClosedProcess(0);				// ���� ���� FD_CLOSE
		}
	}
}
