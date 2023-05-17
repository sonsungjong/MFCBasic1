#include "pch.h"
#include "WinSocketServer.h"

// #define _WINSOCK_DEPRECATED_NO_WARNINGS 를 framework.h에 추가하기
#include <WS2tcpip.h>
#pragma comment(lib, "WS2_32.lib")

// 기본 생성자
WinSocketServer::WinSocketServer()
{
	InitObject(27);
}

WinSocketServer::WinSocketServer(unsigned char a_key)
{
	InitObject(a_key);
}

// 초기화 함수
void WinSocketServer::InitObject(unsigned char a_key)
{
	WSADATA temp;
	WSAStartup(0x0202, &temp);						// 소켓 라이브러리 로드

	for (int i = 0; i < MAX_USER_COUNT; i++)
	{
		m_users[i].h_socket = INVALID_SOCKET;
	}
	mh_listen_socket = INVALID_SOCKET;
	mp_notify_wnd = NULL;
	m_key = a_key;
	m_accept_msg_id = 25001;
	m_read_close_msg_id = 25002;
	mp_net_body_data = NULL;
	m_net_body_size = 0;
	mp_net_user = NULL;
}

WinSocketServer::~WinSocketServer()
{
	DestroyClientSockets();					// 접속 클라이언트 소켓 전부 제거, 리슨 소켓 제거

	if (mp_net_body_data != NULL)				// 데이터 수신에 사용하던 메모리 해제
	{ delete[] mp_net_body_data; }

	WSACleanup();					// 소켓 라이브러리 해제
}

// 모든 클라이언트 접속 해제 후 리슨소켓 종료
void WinSocketServer::DestroyClientSockets()
{
	UserData* p = m_users;
	for (int i = 0; i < MAX_USER_COUNT; i++, p++)
	{
		if (p->h_socket != INVALID_SOCKET)					// 할당된 클라이언트 소켓이 있으면
		{
			closesocket(p->h_socket);						// 클라이언트 소켓 종료
			p->h_socket = INVALID_SOCKET;					// 클라이언트 소켓 초기화
		}
	}

	if (mh_listen_socket != INVALID_SOCKET)				// 리슨 소켓이 있으면
	{
		closesocket(mh_listen_socket);				// 리슨소켓 종료
		mh_listen_socket = INVALID_SOCKET;				// 리슨 소켓 초기화
	}
}

// 1명의 클라이언트에게 데이터 전송
void WinSocketServer::SendFrameData(SOCKET ah_socket, char a_msg_id, const void* ap_data, int a_size)
{
	char* p_data = new char[a_size + 4];					// 헤더 사이즈 4 + 바디 사이즈 할당

	*p_data = m_key;							// 보안키값 대입
	*(p_data + 1) = a_msg_id;				// 식별값 대입
	*(unsigned short*)(p_data + 2) = a_size;				// 바디사이즈 대입
	memcpy(p_data + 4, ap_data, a_size);					// 바디 데이터 복제

	send(ah_socket, p_data, a_size + 4, 0);					// 패킷 전송
	delete[] p_data;
}

// 모든 클라이언트에게 전송
void WinSocketServer::BroadcastFrameData(char a_msg_id, const void* ap_data, int a_size)
{
	char* p_data = new char[a_size + 4];				// 헤더사이즈4 + 바디사이즈 할당

	*p_data = m_key;										// 보안키 대입
	*(p_data + 1) = a_msg_id;							// 식별값 대입
	*(unsigned short*)(p_data + 2) = a_size;				// 전송할 바디사이즈 대입
	memcpy(p_data + 4, ap_data, a_size);					// 바디 내용 복제

	// 모든 사용자에게 전송
	UserData* p = m_users;
	for (int i = 0; i < MAX_USER_COUNT; i++, p++)
	{
		if (p->h_socket != INVALID_SOCKET)
		{ send(p->h_socket, p_data, a_size + 4, 0); }
	}
	delete[] p_data;
}

// 서버 Listen 시작
void WinSocketServer::StartListenService(const wchar_t* ap_ip_address, int a_port, CWnd* ap_notify_wnd, int a_accept_id, int a_read_close_id)
{
	mp_notify_wnd = ap_notify_wnd;					// 적용 화면 정보
	m_accept_msg_id = a_accept_id;					// 접속 ID
	m_read_close_msg_id = a_read_close_id;			// 읽기 또는 해제 ID

	mh_listen_socket = socket(AF_INET, SOCK_STREAM, 0);				// TCP 소켓 생성

	sockaddr_in addr_data = { AF_INET, htons(a_port), };				// IP체계, PORT 할당
	InetPton(AF_INET, ap_ip_address, &addr_data.sin_addr.s_addr);				// ap_ip_address 주소를 사용하는 네트워크를 사용하도록 설정

	bind(mh_listen_socket, (sockaddr*)&addr_data, sizeof(addr_data));				// 소켓을 네트워크 시스템에 연결한다

	listen(mh_listen_socket, 5);				// 소켓을 시작한다

	WSAAsyncSelect(mh_listen_socket, mp_notify_wnd->m_hWnd, m_accept_msg_id, FD_ACCEPT);			// 접속 시도시, 화면에 25001 메시지가 발생하게 비동기 셋팅
}

// 사용자가 접속하면, 이 함수를 통해 접속처리를 해준다
UserData* WinSocketServer::ProcessAccept()
{
	sockaddr_in addr_data;
	int addr_data_size = sizeof(addr_data);

	SOCKET h_client_socket = accept(mh_listen_socket, (sockaddr*)&addr_data, &addr_data_size);			// 접속 허용

	wchar_t temp_ip_address[32];
	InetNtop(AF_INET, &addr_data.sin_addr, temp_ip_address, 32);				// 정수 addr_data 를 문자열로 temp_ip_address 에 저장
	int index = AddNewUser(h_client_socket, temp_ip_address);

	if (index == MAX_USER_COUNT)					// 접속자수 초과
	{
		closesocket(h_client_socket);
		return NULL;
	}
	return m_users + index;				// 현재 접속한 사용자의 정보를 담은 주소 반환
}

// 새로운 사용자 접속 처리
int WinSocketServer::AddNewUser(SOCKET ah_new_socket, const wchar_t* ap_ip_address)
{
	UserData* p = m_users;
	for (int i = 0; i < MAX_USER_COUNT; i++, p++)				// INVALID_SOCKET 인 곳을 찾아 순회
	{
		if (p->h_socket == INVALID_SOCKET)
		{
			p->h_socket = ah_new_socket;
			wcscpy_s(p->ip_address, 16, ap_ip_address);
			WSAAsyncSelect(ah_new_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_READ | FD_CLOSE);
			return i;
		}
	}
	return MAX_USER_COUNT;				// 접속자수가 이미 최대
}

// 소켓 핸들을 통해 해당 접속자 정보 찾기
UserData* WinSocketServer::GetUserData(SOCKET ah_socket)
{
	for (int i = 0; i < MAX_USER_COUNT; i++)
	{
		if (m_users[i].h_socket == ah_socket)
		{ return m_users + i; }
	}
	return NULL;			// 없으면 NULL
}

// 25002 메시지 발생 또는 강퇴시 사용
void WinSocketServer::CloseSocket(SOCKET ah_socket, UserData* ap_close_user)
{
	UserData* p_user = GetUserData(ah_socket);

	// 찾아서 있으면 소켓 제거
	if (p_user != NULL)
	{
		if (ap_close_user != NULL)
		{
			memcpy(ap_close_user, p_user, sizeof(UserData));
			p_user->h_socket = INVALID_SOCKET;
		}
	}
	closesocket(ah_socket);					// 해당 소켓 제거
}

// 메시지 수신
int WinSocketServer::ReceiveData(SOCKET ah_socket, char* ap_data, int a_size)
{
	int read_size = 0, total_size = 0, retry_count = 0;

	// a_size와 크기가 같아질때까지 수신
	while (total_size < a_size)
	{
		read_size = recv(ah_socket, ap_data + total_size, a_size - total_size, 0);

		if (read_size == SOCKET_ERROR || read_size == 0)					// 읽기 실패
		{
			Sleep(10);
			retry_count++;
			if(retry_count > 300)						// 재시도 300회에도 실패했으면 작업 중단
			{ break; }
		}
		else 
		{
			retry_count = 0;
			total_size += read_size;						// 수신 데이터 합산
		}
	}
	return total_size;				// 수신한 바이트크기 반환
}

// 헤더 정보를 처리
int WinSocketServer::ProcessHeaderInfo(SOCKET ah_socket)
{
	unsigned char key;

	recv(ah_socket, (char*)&key, 1, 0);				// 수신받은 보안키를 읽는다

	if (key == m_key)				// 서버의 보안키와 일치할 경우
	{
		recv(ah_socket, (char*)&m_net_msg_id, 1, 0);				// 식별자 수신
		recv(ah_socket, (char*)&m_net_body_size, 2, 0);			// 바디 사이즈 수신
		return 1;
	}
	return 0;				// 보안키와 일치하지 않을 경우
}

// FD_READ로 25002 메시지가 발생하면 사용됨
int WinSocketServer::BeginNetworkProcess(SOCKET ah_socket)
{
	WSAAsyncSelect(ah_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_CLOSE);				// 끊어읽기와 재시도를 위해 FD_READ는 제외하고 다시 비동기 셋팅
	
	mp_net_user = GetUserData(ah_socket);					// 메시지를 보낸 클라이언트 정보 대입

	int state = ProcessHeaderInfo(ah_socket);				// 헤더를 읽는다

	if (state != 0 && m_net_body_size > 0)				// 헤더 수신에 성공하고 바디 크기가 0 이상일 때 수신
	{
		mp_net_body_data = new char[m_net_body_size];
		state = m_net_body_size == ReceiveData(ah_socket, mp_net_body_data, m_net_body_size);
	}
	return state;					// 성공여부
}

// FD_READ로 25002 발생 후 끝나면 BeginNetworkProcess() 의 후처리
int WinSocketServer::EndNetworkProcess()
{
	WSAAsyncSelect(mp_net_user->h_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_READ | FD_CLOSE);
	return 1;
}

// 소켓 비동기 메시지를 처리
void WinSocketServer::MessageProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == m_accept_msg_id)				// 접속 시도시
	{
		UserData* p_user = ProcessAccept();
		if(p_user != NULL)
		{ AcceptUserProc(p_user); }
	}
	else if (message == m_read_close_msg_id)
	{
		if (LOWORD(lParam) == FD_READ)
		{
			if (BeginNetworkProcess((SOCKET)wParam))			// 헤더를 읽는다
			{
				if (ProcessNetMessage() == 1)				// 메시지 수신시
				{
					EndNetworkProcess();
				}

				if (mp_net_body_data != NULL)				// 수신에 사용된 메모리 해제
				{
					delete[] mp_net_body_data;
					mp_net_body_data = NULL;
				}
			}
			else								// 헤더 읽기 실패 (보안키 불일치)
			{
				CloseSocket(mp_net_user->h_socket, &m_temp_user_data);		// 소켓 제거하고 m_temp_user_data에 정보 저장
				CloseUserProc(&m_temp_user_data, 1);				// 수상한 클라이언트에 대한 추가작업(비정상 1)
			}
		}
		else					// FD_CLOSE
		{
			CloseSocket((SOCKET)wParam, &m_temp_user_data);				// 소켓 제거 후 m_temp_user_data에 정보를 저장
			CloseUserProc(&m_temp_user_data, 0);				// 접속 종료한 클라이언트에 대한 추가작업(정상 0)
		}
	}
}

