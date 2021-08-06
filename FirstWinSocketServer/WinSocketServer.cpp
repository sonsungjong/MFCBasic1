#include "pch.h"
#include "WinSocketServer.h"

// #define _WINSOCK_DEPRECATED_NO_WARNINGS 를 framework.h에 추가하기
#include <WS2tcpip.h>				// InetPton 함수 사용을 위해 포함
#pragma comment(lib, "WS2_32.lib")

// 기본 생성자
WinSocketServer::WinSocketServer()
{
	InitObject(27);				// key를 27로 셋팅
}
// 내부적으로 key를 고정하지 않고 외부에서 셋팅하려면 생성자에서 key값을 받게 만듦
WinSocketServer::WinSocketServer(unsigned char a_key)
{
	InitObject(a_key);
}

// 객체를 초기화하는 함수, 생성자에서 호출
void WinSocketServer::InitObject(unsigned char a_key) {
	WSADATA temp;
	WSAStartup(0x0202, &temp);				// 소켓 라이브러리를 사용가능 상태로 셋팅

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

WinSocketServer::~WinSocketServer() {
	// 접속된 클라이언트 소켓 전부 제거, 리슨 소켓 제거
	DestroyClientSockets();

	// 데이터 수신에 사용하던 메모리 해제
	if (mp_net_body_data != NULL) delete[] mp_net_body_data;

	WSACleanup();			// 소켓 라이브러리 사용 해제 셋팅
}

// 서버에 접속한 모든 클라이언트 접속 해제 후 Listen소켓 종료
void WinSocketServer::DestroyClientSockets()
{
	UserData* p = m_users;
	for (int i = 0; i < MAX_USER_COUNT; i++, p++)
	{
		if (p->h_socket != INVALID_SOCKET) {			// 할당된 소켓이 있다면
			closesocket(p->h_socket);						// 소켓을 종료
			p->h_socket = INVALID_SOCKET;			// 소켓을 다시 사용할 수 있도록 초기화
		}
	}

	if (mh_listen_socket != INVALID_SOCKET) {		// 리슨 소켓이 만들어져 있다면
		closesocket(mh_listen_socket);					// 리슨 소켓을 닫는다.
		mh_listen_socket = INVALID_SOCKET;				// 리슨 소켓을 초기화
	}
}

// 1명의 클라이언트에게 데이터를 전송
// 프레임 구성 : "Key, Message ID, Body size, Body Data"
void WinSocketServer::SendFrameData(SOCKET ah_socket, char a_msg_id, const void* ap_data, int a_size)
{
	// 전송할 데이터 프레임을 저장하기 위한 메모리를 할당
	char* p_data = new char[a_size + 4];
	// 구별 키 값을 설정
	*p_data = m_key;
	// 메시지 아이디 설정
	*(p_data + 1) = a_msg_id;
	// 전송할 실제 데이터 크기를 설정
	*(unsigned short*)(p_data + 2) = a_size;
	// 전송할 실제 데이터를 복사
	memcpy(p_data + 4, ap_data, a_size);
	// ah_socket 으로 데이터를 a_size +4 크기 만큼 전송한다.
	send(ah_socket, p_data, a_size + 4, 0);
	// 프레임 저장에 사용한 메모리를 해제
	delete[] p_data;
}

// 접속한 모든 클라이언트에게 데이터를 전송
void WinSocketServer::BroadcastFrameData(char a_msg_id, const void* ap_data, int a_size)
{
	// 전송할 데이터 프레임을 저장하기 위한 메모리 할당
	char* p_data = new char[a_size + 4];
	// 구별 키값을 설정
	*p_data = m_key;
	// 메시지 아이디 설정
	*(p_data + 1) = a_msg_id;
	// 전송할 실제 데이터 크기 설정
	*(unsigned short*)(p_data + 2) = a_size;
	// 전송할 실제 데이터를 복사
	memcpy(p_data + 4, ap_data, a_size);

	UserData* p = m_users;
	// 접속된 모든 사용자에게 데이터를 전송
	for (int i = 0; i < MAX_USER_COUNT; i++, p++)
	{
		// 소켓이 사용되고 있다면 p->h_socket으로 데이터를 a_size +4 크기 만큼 전송
		if (p->h_socket != INVALID_SOCKET) {
			send(p->h_socket, p_data, a_size + 4, 0);
		}
	}
	// 프레임 저장에 사용한 메모리 해제
	delete[] p_data;
}

// 서버시작할때 Listen 서비스를 시작할 때 사용하는 함수
void WinSocketServer::StartListenService(const wchar_t* ap_ip_address, int a_port, CWnd* ap_notify_wnd, int a_accept_id, int a_read_close_id)
{
	mp_notify_wnd = ap_notify_wnd;
	m_accept_msg_id = a_accept_id;
	m_read_close_msg_id = a_read_close_id;

	// AF_INET 주소 체계를 사용하는 TCP방식의 소켓 생성
	mh_listen_socket = socket(AF_INET, SOCK_STREAM, 0);

	// IP 주소 체계, 프로그램 식별 번호(port)
	sockaddr_in addr_data = { AF_INET, htons(a_port), };
	// ap_ip_address 주소를 사용하는 네트워크를 사용하도록 설정
	InetPton(AF_INET, ap_ip_address, &addr_data.sin_addr.s_addr);

	// addr_data에 설정된 정보를 사용하여 소켓을 네투워크 시스템에 연결한다.
	bind(mh_listen_socket, (sockaddr*)&addr_data, sizeof(addr_data));
	// 접속을 처리할 단위를 설정한다.
	// 하지만 동시 처리가 아니라 순차처리이기 때문에 숫자가 크다고 빨라지지는 않음
	listen(mh_listen_socket, 5);
	// mh_listen_socket 에 사ㅓ용자가 접속을 시도(FD_ACCEPT)했을 때
	// 현재 대화상자 (m_hWnd)에 25001번 메시지가 발생하도록 비동기로 셋팅한다.
	WSAAsyncSelect(mh_listen_socket, mp_notify_wnd->m_hWnd, m_accept_msg_id, FD_ACCEPT);
}

// 새로운 사용자가 접속했을 때, 이 함수를 호출하면 사용자의 접속을 처리한다.
UserData* WinSocketServer::ProcessAccept()
{
	// 접속을 시도한 소켓(클라이언트와 통신할 소켓)의 주소를 저장할 변수
	sockaddr_in addr_data;
	// 자신의 사용할 주소 저장 변수의 크기를 계산
	int addr_data_size = sizeof(addr_data);

	// 클라이언트 소켓의 접속을 허락한다.
	// 접속을 허락하면 복제 소켓이 생성되어 그 핸들 값이 반환된다(h_client_socket)
	// addr_data 변수에는 접속을 시도한 소켓의 IP가 정수값 형태로 저장된다.
	SOCKET h_client_socket = accept(mh_listen_socket, (sockaddr*)&addr_data, &addr_data_size);

	wchar_t temp_ip_address[32];
	// addr_data 변수에 정수 형태로 저장되어 있는 IP를 문자열 형태로 변경해서 temp_ip_address에 저장.
	InetNtop(AF_INET, &addr_data.sin_addr, temp_ip_address, 32);
	int index = AddNewUser(h_client_socket, temp_ip_address);
	// 만약 배열 전체를 다 체크헀는데 빈 공간이 없다면 최대 접속자 수를 초과한 것
	// 소켓을 해제하고 접속을 취소
	if (index == MAX_USER_COUNT) {
		closesocket(h_client_socket);
		return NULL;			// 접속자 수가 초과하여 접속 실패
	}
	return m_users + index;			// 현재 접속한 사용자의 정보가 담긴 주소를 반환
}

// 새로운 사용자의 접속을 처리한다
// m_users 배열의 h_socket 값이 INVALID_SOCKET인 항목에 새로운 사용자 소켓을 저장
int WinSocketServer::AddNewUser(SOCKET ah_new_socket, const wchar_t* ap_ip_address)
{
	UserData* p = m_users;
	// h_client_socket은 지역변수이기 때문에 해당 함수가 종료되면 사라진다.
	// 따라서 자신이 관리하고 있는 클라이언트 정보 공간에 빈 곳이 있는지 확인해서 저장한다
	for (int i = 0; i < MAX_USER_COUNT; i++, p++)
	{
		// 각 배열의 h_socket에 INVALID_SOCKET 값이 저장되어 있다면 해당 배열은 소켓의 핸들이 저장되지 않은 것.
		if (p->h_socket == INVALID_SOCKET) {
			// 배열의 비어있는 공간에 접속한 소켓의 핸들을 복사
			p->h_socket = ah_new_socket;
			// 접속한 사용자의 IP를 복사한다.
			wcscpy_s(p->ip_address, 16, ap_ip_address);
			// h_client_socket에 FD_READ 또는 FD_CLOSE 이벤트가 발생하면 대화상자로 25002번 메시지를 전송하도록 비동기로 셋팅
			WSAAsyncSelect(ah_new_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_READ | FD_CLOSE);
			return i;
		}
	}
	return MAX_USER_COUNT;			// 비어있는 항목이 없으면
}

// 소켓 핸들을 가지고 해당 소켓 핸들이 저장된 m_users 배열의 항목 주소를 얻는 함수
UserData* WinSocketServer::GetUserData(SOCKET ah_socket)
{
	// 자신이 관리하고 있는 클라이언트 중 이벤트를 발생시킨 특정 클라이언트를 확인하기 위해 배열을 순회
	for (int i = 0; i < MAX_USER_COUNT; i++)
	{
		// ah_socket와 값이 일치하는 소켓이 현재 이벤트를 발생시킨 클라이언트
		if (m_users[i].h_socket == ah_socket) return m_users + i;
	}
	return NULL;			// 검색 실패시
}

// FD_CLOSE에 의해 25002 메시지가 발생하여 사용자의 접속 정보를 해제할 때 사용
// 25002 메시지 에서만 사용하는 것이 아니라 특정 사용자를 종료시킬 때에도 사용
// 두번째 아규먼트 ap_close_user에 접속을 해제한 사용자의 데이터가 복사됨.
// UserData 구조체를 지역변수로 선언해서 해당 변수의 주소를 전달해야 정보를 받을 수 있음
void WinSocketServer::CloseSocket(SOCKET ah_socket, UserData* ap_close_user)
{
	// ah_socket에 해당하는 사용자 정보를 찾는다.
	UserData* p_user = GetUserData(ah_socket);
	// 사용자 정보를 찾았고 이 정보를 복사할 메모리가 전달되면 삭제될 사용자 정보를 ap_close_user에 복사
	if (p_user != NULL) {
		if (ap_close_user != NULL) {
			memcpy(ap_close_user, p_user, sizeof(UserData));
			// 배열에 저장된 소켓을 초기화
			p_user->h_socket = INVALID_SOCKET;
		}
	}
	closesocket(ah_socket);			// 소켓 제거
}

// 클라이언트가 전송한 데이터를 수신할 때 사용하는 함수
int WinSocketServer::ReceiveData(SOCKET ah_socket, char* ap_data, int a_size) {
	int read_size, total_size = 0, retry_count = 0;
	// a_size 크기와 같아질때까지 수신을 반복
	while (total_size < a_size) {
		// 남은 크기만큼 수신
		read_size = recv(ah_socket, ap_data + total_size, a_size - total_size, 0);
		if (read_size == SOCKET_ERROR || read_size == 0) {		// 읽기 실패
			Sleep(10);			// 10ms 대기
			retry_count++;			// 재시도횟수 증가
			if (retry_count > 300) break;			// 300회 재시도에도 실패하면 작업 중단
		}
		else {
			retry_count = 0;			// 재시도 횟수 초기화
			total_size += read_size;			// 수신된 데이터의 크기 합산
		}
	}
	return total_size;			// 전체 수신한 바이트 크기 반환
}

// 네트워크 메시지에서 헤더 정보를 처리하는 함수
int WinSocketServer::ProcessHeaderInfo(SOCKET ah_socket) {
	unsigned char key;
	// 첫 바이트의 key값을 읽음
	recv(ah_socket, (char*)&key, 1, 0);
	// key 값이 지정된 key 값과 일치한지 비교
	if (key == m_key) {
		recv(ah_socket, (char*)&m_net_msg_id, 1, 0);
		recv(ah_socket, (char*)&m_net_body_size, 2, 0);
		return 1;		// key가 일치할 경우 (정상 헤더)
	}
	return 0;			// key가 일치하지 않을 경우 (비정상적인 헤더)
}

// 네트워크로 데이터가 수신되면 헤더를 읽고 body데이터를 읽어 작업을 진행할 수 있도록 준비하는 함수
// FD_READ에 의해 25002가 발생하면 사용
int WinSocketServer::BeginNetworkProcess(SOCKET ah_socket) {
	// 끊어읽기 및 재시도 를 위해 FD_READ는 제외하고 다시 비동기를 설정
	WSAAsyncSelect(ah_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_CLOSE);
	// 데이터를 전송한 클라이언트의 정보를 찾아서 mp_net_user에 저장
	mp_net_user = GetUserData(ah_socket);

	// 헤더를 먼저 읽는다.
	int state = ProcessHeaderInfo(ah_socket);
	// 정상헤더이면 Body가 0보다 클때 Body 수신
	if (state && m_net_body_size > 0) {
		// Body 데이터를 저장하기 위한 메모리 할당
		mp_net_body_data = new char[m_net_body_size];
		// Body 데이터를 수신, 수신여부 결과를 state에 저장
		state = m_net_body_size == ReceiveData(ah_socket, mp_net_body_data, m_net_body_size);
	}
	return state;
}

// FD_READ 이벤트에 의해 발생된 25002 메시지 작업을 완료하면 호출
// BeginNetworkProcess() 에서 만든 정보들을 정리하는 작업 수행
int WinSocketServer::EndNetworkProcess()
{
	// 다시 데이터 수신 상태를 확인할 수 있도록 FD_READ 이벤트를 재설정
	WSAAsyncSelect(mp_net_user->h_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_READ | FD_CLOSE);
	return 1;
}

// 소켓 관련 비동기 메시지를 처리하는 함수
void WinSocketServer::MessageProc(UINT message, WPARAM wParam, LPARAM lParam) {
	if (message == m_accept_msg_id) {			// 새로운 클라이언트가 접속을 시도하는 경우
		UserData* p_user = ProcessAccept();			// 기본적인 접속 처리
		if (p_user != NULL) AcceptUserProc(p_user);			// 추가적인 접속처리를 할 수 있도록 함수 호출
	}
	else if (message == m_read_close_msg_id) {
		if (LOWORD(lParam) == FD_READ) {		// 데이터가 수신됨
			if (BeginNetworkProcess((SOCKET)wParam)) {			// 헤더를 읽는다
				// 정상적으로 메시지를 처리했다면 마무리작업도 호출(FD_READ 재설정 포함)
				if (1 == ProcessNetMessage()) {
					EndNetworkProcess();
				}
				// 데이터 수신에 사용하던 메모리 해제
				if (mp_net_body_data != NULL) {
					delete[] mp_net_body_data;
					mp_net_body_data = NULL;
				}
			}
			else {			// key값이 일치하지 않음
				// 접속 해제된 소켓을 제거하고 해제한 사용자 정보를 m_temp_user_data에 저장
				CloseSocket(mp_net_user->h_socket, &m_temp_user_data);
				// 접속이 해제된 클라이언트에 추가적인 작업을 할 수 있도록 함수 호출
				CloseUserProc(&m_temp_user_data, 1);
			}
		}
		else {			// FD_CLOSE, 상대편 종료시
			// 접속 해제된 소켓을 제거 후 해제한 사용자 정보를 m_temp_user_data에 저장
			CloseSocket((SOCKET)wParam, &m_temp_user_data);
			// 접속이 해제된 클라이언트에 추가적인 작업을 할 수 있도록 함수 호출
			CloseUserProc(&m_temp_user_data, 0);
		}
	}
}