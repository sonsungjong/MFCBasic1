// FirstWinSocketServerDlg.h : header file
//

#pragma once
#include "WinSocketServer.h"

//#define MAX_USER_COUNT			2000		// 서버에 접속 가능한 최대 클라이언트 수

class MyServerSocket : public WinSocketServer
{
// 오버라이딩
public:
	// 새로운 클라이언트가 접속되었을 때 호출
	virtual void AcceptUserProc(UserData* ap_user_data);
	// 메시지 수신 후 작업할 공간
	virtual int ProcessNetMessage();
	// 클라이언트 접속 해제
	virtual void CloseUserProc(UserData* ap_user_data, int a_error_flag);
};

/*
// 1개의 클라이언트 정보를 저장할 구조체
struct UserData {
	SOCKET h_socket;				// 개별 클라이언트와 통신할 소켓 핸들
	wchar_t ip_address[16];		// 접속한 클라이언트의 주소
};
*/

// CFirstWinSocketServerDlg dialog
class CFirstWinSocketServerDlg : public CDialogEx
{
private:
	MyServerSocket m_server_socket;			// 서버의 소켓 객체 선언
protected:
	const wchar_t* ipconfig = L"192.168.12.21";		// 내 IP
	const int thisPort = 1900;										// 해당 port
	/*
	SOCKET mh_listen_socket;		// 클라이언트 접속 처리할 때 사용할 소켓
	UserData m_users[MAX_USER_COUNT];		// 서버에 접속한 전체 사용자 정보
	*/
	// SOCKET mh_client_socket;		// 한 개의 클라이언트만 접속을 허락
// Construction
public:
	CFirstWinSocketServerDlg(CWnd* pParent = nullptr);	// standard constructor

	// 리스트 박스에 이벤트 로그 추가
	void AddEventString(const wchar_t* ap_string)
	{
		int index = m_event_list.InsertString(-1, ap_string);
		m_event_list.SetCurSel(index);
	}

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIRSTWINSOCKETSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_event_list;
	afx_msg void OnDestroy();
	afx_msg void OnLbnSelchangeEventList();
protected:
	afx_msg LRESULT OnAcceptProc(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSocketMessage(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedOk();
	int ReceiveData(SOCKET ah_socket, char* ap_data, int a_size);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
