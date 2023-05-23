#ifndef _WIN_SOCKET_SERVER_H_
#define _WIN_SOCKET_SERVER_H_

#include <WinSock2.h>

#define MAX_USER_COUNT				2000

struct UserData
{
	SOCKET h_socket;					// 클라이언트 소켓 정보
	TCHAR ip_address[16];			// 클라이언트 아이피
};

class WinSocketServer
{
public:
	// 기본 생성자
	WinSocketServer();
	WinSocketServer(unsigned char a_key);				// 보안키 1byte
	virtual ~WinSocketServer();

	// 초기화 함수
	void InitObject(unsigned char a_key);
	inline UserData* GetUserData() { return m_users; }
	inline UserData* GetUserData(int a_index) { return m_users + a_index; }
	UserData* GetUserData(SOCKET ah_socket);					// 소켓으로 유저검색

protected:
	UserData m_users[MAX_USER_COUNT];					// 시스템 사용자 전체 정보
	SOCKET mh_listen_socket;										// 접속용 리슨소켓
	int m_accept_msg_id;											// 접속 메시지 번호
	int m_read_close_msg_id;										// 수신 및 해제 메시지 번호

	UserData* mp_net_user;					// 데이터를 전송한 클라이언트 정보
	UserData m_temp_user_data;				// 접속 해제유저 정보
	CWnd* mp_notify_wnd;						// 정보처리 윈도우 정보

	// 수신데이터 정보
	unsigned char m_key;				// 1byte (보안키)
	unsigned char m_net_msg_id;				// 1byte (ID)
	unsigned short m_net_body_size;				// 2byte (Body 사이즈)
	char* mp_net_body_data;							// (Body)

public:
	void StartListenService(const wchar_t* ap_ip_address, int a_port, CWnd* ap_notify_wnd, int a_accept_id = 25001, int a_read_close_id = 25002);			// 서버 시작
	void DestroyClientSockets();			// 서버 종료
	void SendFrameData(SOCKET ah_socket, char a_msg_id, const void* ap_data, int a_size);			// 송신
	void BroadcastFrameData(char a_msg_id, const void* ap_data, int a_size);				// 모든 클라이언트에게 송신
	UserData* ProcessAccept();					// 접속 허용
	int ReceiveData(SOCKET ah_socket, char* ap_data, int a_size);				// 수신
	
	void MessageProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual int ProcessHeaderInfo(SOCKET ah_socket);					// 헤더 정보 처리
	virtual int BeginNetworkProcess(SOCKET ah_socket);				// 수신 시 읽음
	virtual int EndNetworkProcess();							// 수신 읽고 후 처리
	virtual int AddNewUser(SOCKET ah_new_socket, const wchar_t* ap_ip_address);				// 접속 허용
	virtual void CloseSocket(SOCKET ah_socket, UserData* ap_close_user);				// 사용자 제거

	// 재정의 전용
	virtual void AcceptUserProc(UserData* ap_user_data) {}				// 접속 시 추가작업
	virtual int ProcessNetMessage() { return 1; }					// 수신 데이터 후처리
	virtual void CloseUserProc(UserData* ap_user_data, int a_error_flag) {}					// 접속 해제시 a_error_flag == 0:강퇴, 1:오류발생
};

#endif