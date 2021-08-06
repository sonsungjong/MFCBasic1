
// FirstWinSocketClientDlg.h : header file
//

#pragma once
#include "WinSocketClient.h"

class MyClientSocket : public WinSocketClient
{
public:
	virtual void ConnectedProcess();			// ������ ������ ����� ������ ȣ��Ǵ� �Լ�
	virtual int ProcessNetMessage();			// ProcessNetMessage() �Լ��� �������ؼ� ���ŵ� �����͸� ��� ó���� ������ �۾�
	virtual void ClosedProcess(int a_error_flag);			// ������ ������ ��쿡 ȣ��Ǵ� �Լ�
};

// CFirstWinSocketClientDlg dialog
class CFirstWinSocketClientDlg : public CDialogEx
{
protected:
	MyClientSocket m_client_socket;		// ������ ��ſ� ����� ���� ��ü

	/*
	const char* ipconfig = "192.168.219.21";			// ������ IP
	SOCKET mh_socket;			// ������ �����ؼ� ����� ����
	char m_is_connected;			// ���� ���� ( 0:���Ӿȵ�, 1:������, 2:���ӵ�)
	*/

// Construction
public:
	CFirstWinSocketClientDlg(CWnd* pParent = nullptr);	// standard constructor

	// ����Ʈ �ڽ��� �̺�Ʈ �α׸� �߰��ϴ� �Լ�
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
