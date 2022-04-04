#include "pch.h"
#include "WinSocketClient.h"

// #define _WINSOCK_DEPRECATED_NO_WARNINGS		를 framework.h 에 추가해야합니다!!
#include <WS2tcpip.h>			// InetPton 함수 사용을 위해 추가함 (유니코드를 일반정수로 변환하는 함수)
#pragma comment(lib, "WS2_32.lib")

// 기본 생성자
WinSocketClient::WinSocketClient()
{
	InitObject('\0');		// key = NUL
}

// 내부적으로 key를 정의하지않고 외부에서 key를 입력받아 설정하는 생성자
WinSocketClient::WinSocketClient(unsigned char a_key)
{
	InitObject(a_key);
}

// 객체 파괴자
WinSocketClient::~WinSocketClient()
{
	// 사용하던 소켓을 제거
	CloseSocket();
	// 데이터 수신에 사용하던 메모리를 해제
	if (mp_net_body_data != NULL) {
		delete[] mp_net_body_data;
	}

	WSACleanup();		// 소켓 라이브러리 사용 중지 상태로 셋팅
}

// 객체를 초기화하는 함수 (내부적으로 호출되는 함수)
void WinSocketClient::InitObject(unsigned char a_key)
{
	WSADATA temp;
	WSAStartup(0x0202, &temp);			// 소켓 라이브러리를 사용 가능 상태로 셋팅

	mh_socket = INVALID_SOCKET;
	m_is_connected = 0;
	m_connect_msg_id = 26001;
	m_read_close_msg_id = 26002;
	mp_notify_wnd = NULL;

	m_key = a_key;
	mp_net_body_data = NULL;
	m_net_body_size = 0;
}

// 정해진 Packet Frame으로 원하는 데이터를 전송하는 함수
void WinSocketClient::SendFrameData(char a_msg_id, const void* ap_data, int a_size)		// a_msg_id 아이디로 ap_data 주소에 a_size 사이즈값을 보냄
{
	// 전송할 데이터 프레임을 저장하기 위한 메모리를 할당 (+4byte는 헤더메시지의 사이즈)
	char* p_data = new char[a_size + 4];
	// 구별 키 값을 설정
	*p_data = m_key;
	// 메시지 아이디 설정
	*(p_data + 1) = a_msg_id;
	// 전송할 실제 데이터 크기를 설정
	*(unsigned short*)(p_data + 2) = a_size;
	// 전송할 실제 데이터 크기를 설정
	memcpy(p_data + 4, ap_data, a_size);
	// mh_socket으로 데이터를 a_size+4 크기만큼 전송
	send(mh_socket, p_data, a_size + 4, 0);
	// 프레임 저장에 사용한 메모리를 해제
	delete[] p_data;
}

// 서버에 접속을 시도하는 함수. 접속할 서버의 ip와 port
// 그리고 접속 결과를 알려줄 메시지 아이디와 데이터가 수신되었거나 접속이 해제되었을 때의 메시지 아이디를 설정
void WinSocketClient::ConnectToServer(const TCHAR* ap_ip_address, int a_port, CWnd* ap_notify_wnd, int a_connect_id, int a_read_close_id)
{
	if (mh_socket == INVALID_SOCKET) {
		// 사용할 메시지 아이디 설정
		m_connect_msg_id = a_connect_id;
		m_read_close_msg_id = a_read_close_id;
		// 메시지를 수신할 윈도우의 주소 저장
		mp_notify_wnd = ap_notify_wnd;

		// AF_INET 주소 체계를 사용하는 TCP 방식의 소켓 생성
		mh_socket = socket(AF_INET, SOCK_STREAM, 0);

		// IP 주소 체계, 프로그램 식별 번호(포트 번호)
		sockaddr_in addr_data = { AF_INET, htons(a_port), };
		// ap_ip_address 주소를 사용하는 네트워크를 사용하도록 설정
		InetPton(AF_INET, ap_ip_address, &addr_data.sin_addr.s_addr);
		// 서버 접속을 비동기 방식으로 처리
		// 서버 접속 결과에 따라 ah_notify_wnd 윈도우로 a_connect_id(26001) 메시지를 전송
		WSAAsyncSelect(mh_socket, ap_notify_wnd->m_hWnd, a_connect_id, FD_CONNECT);
		// 서버에 접속이 진행되고 있음을 설정
		m_is_connected = 1;
		// 서버에 접속을 시도
		// 비동기 모드에서 connect 함수가 접속 결과가 나올때까지 대기하지 않고 바로 빠져나옴
		connect(mh_socket, (sockaddr*)&addr_data, sizeof(addr_data));
	}
}

// 통신에 사용하던 소켓을 제거하는 함수
void WinSocketClient::CloseSocket()
{
	if (mh_socket != INVALID_SOCKET) {
		closesocket(mh_socket);			// 소켓을 닫는다
		mh_socket = INVALID_SOCKET;		// 다시 사용할 수 있도록 초기화
		m_is_connected = 0;				// 접속 안됨으로 설정
	}
}

// 서버가 전송한 데이터를 수신할 때 사용하는 함수
int WinSocketClient::ReceiveData(char* ap_data, int a_size)
{
	int read_size, total_size = 0, retry_count = 0;
	// a_size 크기만큼 다 수신될 때까지 반복
	while (total_size < a_size) {
		// 남은 크기만큼 수신을 시도
		read_size = recv(mh_socket, ap_data + total_size, a_size - total_size, 0);
		if (read_size == SOCKET_ERROR || read_size == 0) {		// 읽기 실패
			Sleep(10);		// 10ms 대기
			retry_count++;		// 재시도 횟수 증가
			if (retry_count > 300) break;			// 300회 재시도가 넘어가면 작업 중단
		}
		else {		// 읽기 완료
			retry_count = 0;			// 재시도 횟수 초기화
			total_size += read_size;		// 수신된 데이터의 크기를 합산
		}
	}
	return total_size;			// 수신한 전체 바이트를 리턴
}

// 수신한 데이터 중 프레임 헤더를 읽어서 처리하는 함수
// 1: 정상헤더, 0: 비정상헤더
int WinSocketClient::ProcessHeaderInfo()
{
	unsigned char key;
	// 첫 바이트에 있는 key값을 읽음
	recv(mh_socket, (char*)&key, 1, 0);
	// key값이 지정된 key값과 일치한지 비교
	if (key == m_key) {
		recv(mh_socket, (char*)&m_net_msg_id, 1, 0);
		recv(mh_socket, (char*)&m_net_body_size, 2, 0);
		return 1;		// key일치하면 리턴1
	}
	return 0;		// key가 다르면 리턴0
}

// 수신된 데이터를 프레임 단위로 읽는 함수 (헤더와 바디 모두 읽음)
int WinSocketClient::BeginNetworkProcess()
{
	// 끊어읽기 및 재시도읽기를 위해 FD_READ 이벤트를 제외하고 다시 비동기를 설정 (중복실행 방지)
	WSAAsyncSelect(mh_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_CLOSE);

	// 먼저 헤더를 읽는다.
	int state = ProcessHeaderInfo();
	// 정상헤더이고 Body의 크기가 0보다 크다면 Body 데이터도 추가로 수신
	if (state && m_net_body_size > 0) {
		// Body 저장을 위한 메모리를 할당
		mp_net_body_data = new char[m_net_body_size];
		// Body 데이터를 수신. 수신 결과를 state변수에 저장
		state = m_net_body_size == ReceiveData(mp_net_body_data, m_net_body_size);
	}
	return state;		// 수신 상태를 리턴
}

// 수신 작업이 완료되었을 때 호출되는 함수 (FD_READ 재설정 및 메모리 해제)
void WinSocketClient::EndNetworkProcess()
{
	// 다시 데이터 수신 상태를 확인할 수 있도록 FD_READ 이벤트를 재설정
	WSAAsyncSelect(mh_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_READ | FD_CLOSE);
}

// 소켓 관련 비동기 메시지를 처리하는 함수
void WinSocketClient::MessageProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == m_connect_msg_id) {		// 서버 접속 결과가 나온 경우
		if (WSAGETSELECTERROR(lParam)) CloseSocket();
		else {
			m_is_connected = 2;		// 접속 상태로 변경
			// 접속 소켓에 데이터가 수신되거나 접속해제되었을때 메시지 발생하도록 비동기 설정
			WSAAsyncSelect(mh_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_READ | FD_CLOSE);
		}
		// 이 클래스를 사용하는 사람이 추가로 해야할 일이 있다면 처리하게 해준다.
		ConnectedProcess();
	}
	else if (message == m_read_close_msg_id) {
		if (WSAGETSELECTEVENT(lParam) == FD_READ) {		// 데이터 수신
			if (BeginNetworkProcess()) {			// 헤더를 읽음
				// 정상적으로 메시지를 처리했다면 마무리 작업(FD_READ 재설정 포함)도 호출한다.
				if (ProcessNetMessage()) EndNetworkProcess();

				// 데이터 수신에 사용하던 메모리를 해제
				if (mp_net_body_data != NULL) {
					delete[] mp_net_body_data;
					mp_net_body_data = NULL;
				}
			}
			else {			// Key값이 일치하지 않아서 서버와의 접속을 끊는다.
				CloseSocket();		// 소켓을 제거
				ClosedProcess(1);		// 추가적인 작업을 할 수 있는 함수 (오류로 인한 종료)
			}
		}
		else {		// FD_CLOSE 서버와 연결이 해제됨
			CloseSocket();			// 소켓 제거
			ClosedProcess(0);		// 추가적인 작업을 할 수 있는 함수 (정상 종료)
		}
	}
}