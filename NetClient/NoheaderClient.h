#ifndef _NOHEADER_CLIENT_H_
#define _NOHEADER_CLIENT_H_

#define MAX_SIZE				32767

#define RECV_DATA				WM_APP + 2100
#define CONNECTED				WM_APP + 2101
#define DISCONNECTED			WM_APP + 2102

class NoheaderClient
{
protected:
	SOCKET mh_socket;					// 통신을 위한 소켓
	BOOL m_is_connected;					// 서버와의 접속 상태 (0:미접속, 1:접속완료)
	int m_connect_msg_id, m_read_msg_id, m_close_msg_id;

	int m_nSoketIdx;			// 소켓 인덱스 저장
	unsigned char m_net_msg_id;						// 메시지 ID
	unsigned short m_net_size;					// 데이터 크기
	char* mp_net_data;						// 데이터 정보 저장
	CWnd* mp_notify_wnd;					// 메시지함수를 받을 윈도우의 주소 저장

public:
	NoheaderClient();
	virtual ~NoheaderClient();

	// 초기화, 내부호출함수
	void InitObject();
	BOOL IsConnect() { return m_is_connected == TRUE; }				// 접속상태를 체크하는 함수
	// 데이터 전송
	void SendFrameData(const void* ap_data, int a_size);
	// connect시도, IP와 PORT, 접속 결과 안내를 위해 발동하는 메시지ID, 수신 또는 접속해제시 발동하는 메시지ID
	void ConnectToServer(const TCHAR* ap_ip_address, int a_port, CWnd* ap_notify_wnd, int a_connect_id = CONNECTED, int a_read_id = RECV_DATA, int a_close_id = DISCONNECTED);
	// 통신하던 소켓제거
	void CloseSocket();
	// 서버의 메시지를 수신
	int RecvData(char* ap_data, int a_size);
	// 수신된 데이터를 프레임단위로 읽기
	int BeginNetworkProcess();				// 바디 읽는 함수
	// 비동기를 다시 걸어주는 함수
	void EndNetworkProcess();
	
	// 비동기 메시지를 처리하는 함수
	void MessageProc(UINT msg, WPARAM wParam, LPARAM lParam);
	
	// 접속결과에 따른 호출함수 (접속결과에 따라 후작업을 위해 재정의할 수 있음)
	virtual void ConnectedProcess() {}
	// 데이터 수신시 처리함수 (수신결과에 따라 후작업을 위해 재정의할 수 있음), 1:성공, 0: 실패
	virtual int ProcessNetMessage() { return 1; }
	// 접속 해제시 처리함수 (접속 강제해제시 후작업을 위해 재정의할 수 있음), 1 : 자체오류발생, 0: 서버에서 강퇴
	virtual void ClosedProcess(int a_error_flag){}
};

#endif