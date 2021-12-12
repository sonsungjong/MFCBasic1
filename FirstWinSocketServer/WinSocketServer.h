#ifndef _WIN_SOCKET_SERVER_H_
#define _WIN_SOCKET_SERVER_H_

// Socket 함수 사용을 위해 헤더와 라이브러리 포함
#include <WinSock2.h>

#define MAX_USER_COUNT			2000			// 접속 가능한 최대 클라이언트 수

// 클라이언트 정보를 각각 저장할 구조체
struct UserData {
	SOCKET h_socket;						// 개별 클라이언트와 통신할 소켓핸들
	TCHAR ip_address[16];				// 접속한 클라이언트 주소
};

class WinSocketServer
{
protected:
	// 시스템 사용자 전체 정보
	UserData m_users[MAX_USER_COUNT];
	// 클라이언트 접속에 사용할 Listen 소켓
	SOCKET mh_listen_socket;
	// 비동기 메시지 번호 (접속, 읽기, 종료)
	int m_accept_msg_id, m_read_close_msg_id;

	// 현재 처리가 진행되고 있는 수신 데이터 정보
	unsigned char m_key;						// 유효 클라이언트 구별을 위한 key값
	unsigned char m_net_msg_id;				// 메시지 ID
	unsigned short m_net_body_size;		// Body 데이터 크기
	char* mp_net_body_data;					// Body 데이터 정보
	UserData* mp_net_user;					// 데이터를 전송한 클라이언트의 정보

	UserData m_temp_user_data;				// 내보내기전에 정보 백업 (나간 사람에 대한 후처리)
	CWnd* mp_notify_wnd;

public:
	// 기본 생성자 (기본 key값 27)
	WinSocketServer();
	// key값을 받아서 설정할 수 있는 생성자
	WinSocketServer(unsigned char a_key);
	// 객체 파괴자
	virtual ~WinSocketServer();

	// 객체를 초기화하기 위한 함수, 생성자에서 호출
	void InitObject(unsigned char a_key);
	// 서버가 관리하는 사용자 목록의 시작 주소를 반환하는 함수
	inline UserData* GetUserData() {
		return m_users;
	}

	// Listen 서비스를 시작할 때 사용하는 함수
	// 서비스를 시작할 IP와 port와 비동기메시지를 받을 윈도우 핸들과 비동기에 사용할 메시지ID를 매개변수로 전달
	// 비동기 메시지로 사용할 ID는 접속을 25001, 읽기와 종료는 25002 로 기본값을 셋팅해놓음
	void StartListenService(const wchar_t* ap_ip_address, int a_port, CWnd* ap_notify_wnd, int a_accept_id = 25001, int a_read_close_id = 25002);
	// 서버에 접속한 모든 클라이언트 접속을 해제하고 Listen 소켓도 종료하는 함수
	void DestroyClientSockets();
	// 클라이언트로 1개의 네트워크 프레임 데이터를 하나 전송
	// 프레임 구성 : "Key, Message ID, Body size, BVody Data"
	void SendFrameData(SOCKET ah_socket, char a_msg_id, const void* ap_data, int a_size);
	// 접속한 모든 클라이언트에게 네트워크 프레임 데이트를 전송한다.
	void BroadcastFrameData(char a_msg_id, const void* ap_data, int a_size);
	// 새로운 사용자가 접속했을 때, 이 함수를 호출하면 사용자의 접속을 처리
	UserData* ProcessAccept();
	// 소켓 핸들을 가지고 해당 소켓 핸들이 저장된 m_users 배열의 항목 주소를 얻는 함수
	UserData* GetUserData(SOCKET ah_socket);
	// 한번에 받기 어려운 크기의 네트워크 메시지를 재시도하면서 받을 수 있도록 하는 함수
	// 반환값이 a_size와 일치하지 않으면 중간에 오류가 발생한 것
	int ReceiveData(SOCKET ah_socket, char* ap_data, int a_size);
	// m_users 배열에서 a_index 위치에 있는 항목의 주소를 얻는 함수 (특정 위치에 있는 주소를 찾을때)
	inline UserData* GetUserData(int a_index) {
		return m_users + a_index;
	}

	// 네트워크 메시지에서 헤더 정보를 처리하는 함수
	virtual int ProcessHeaderInfo(SOCKET ah_socket);
	// 네트워크로 데이터가 수신된 경우, header와 body 데이터를 읽어서 작업을 진행할 수 있는 함수
	// FD_READ 이벤트에 의해 25002 메시지가 발생했을때 사용
	virtual int BeginNetworkProcess(SOCKET ah_socket);
	// FD_READ 이벤트에 의해 발생된 25002 메시지 작업이 완료되었을 때 호출,
	// BeginNetworkProcess() 에서 만든 정보들을 정리하는 작업
	virtual int EndNetworkProcess();
	// 새로운 사용자 접속처리
	// m_users배열의 h_socket값이 INVALID_SOCKET인 항목에 새로운 사용자 소켓을 저장
	virtual int AddNewUser(SOCKET ah_new_socket, const wchar_t* ap_ip_address);
	// FD_CLOSE에 의해 25002 메시지가 발생하여 접속 정보를 해제할 때 사용
	// 특정 사용자를 종료시킬 때 사용해도 됨
	// 두번째 인자 ap_close_user는 접속을 해제한 사용자의 정보가 복사됨
	// UserData 구조체 변수를 선언해서 해당 변수의 주소를 전달해야 정보를 받을 수 있음
	virtual void CloseSocket(SOCKET ah_socket, UserData* ap_close_user);
	

	// 상속받은 곳에서 재정의해서 사용
	// 새로운 클라이언트 접속 시 추가 작업이 필요하면 AcceptUserProc()을 사용
	virtual void AcceptUserProc(UserData* ap_user_data) {}
	// ProcessNetMessage() : 수신된 데이터를 어떻게 처리할 것인지 재정의
	// 성공시 return 1, 실패시 return 0
	// return 0을 하면 FD_READ 재설정 안됨 (소켓 제거시 0반환)
	virtual int ProcessNetMessage() { return 1; }
	// CloseUserProc() : 접속 해제시 호출, 접속이 해제되었을 때 추가작업을 재정의하면 됨
	// a_error_flag 값이 1이면 오류가 발생해서 해제된 것이고 0이면 서버에서 접속을 해제시킨 것
	virtual void CloseUserProc(UserData* ap_user_data, int a_error_flag) {}


	void MessageProc(UINT message, WPARAM wParam, LPARAM lParam);
};

#endif