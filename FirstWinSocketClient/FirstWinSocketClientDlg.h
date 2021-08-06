
// FirstWinSocketClientDlg.h : header file
//

#pragma once
#include "WinSocketClient.h"

class MyClientSocket : public WinSocketClient
{
public:
	virtual void ConnectedProcess();			// 서버에 접속한 결과가 나오면 호출되는 함수
	virtual int ProcessNetMessage();			// ProcessNetMessage() 함수를 재정의해서 수신된 데이터를 어떻게 처리할 것인지 작업
	virtual void ClosedProcess(int a_error_flag);			// 접속이 해제된 경우에 호출되는 함수
};

// CFirstWinSocketClientDlg dialog
class CFirstWinSocketClientDlg : public CDialogEx
{
protected:
	MyClientSocket m_client_socket;		// 서버와 통신에 사용할 소켓 객체

	/*
	const char* ipconfig = "192.168.219.21";			// 서버의 IP
	SOCKET mh_socket;			// 서버에 접속해서 통신할 소켓
	char m_is_connected;			// 접속 상태 ( 0:접속안됨, 1:접속중, 2:접속됨)
	*/

// Construction
public:
	CFirstWinSocketClientDlg(CWnd* pParent = nullptr);	// standard constructor

	// 리스트 박스에 이벤트 로그를 추가하는 함수
	void AddEventString(const wchar_t* ap_string);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIRSTWINSOCKETCLIENT_DIALOG };
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
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedSendBtn();
	CListBox m_event_list;
	afx_msg void OnBnClickedConnectBtn();
	afx_msg void OnBnClickedDisconnectBtn();
protected:
	//afx_msg LRESULT OnConnected(WPARAM wParam, LPARAM lParam);
	//afx_msg LRESULT OnSocketMessage(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBigdataBtn();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
