
// MFCBasic227CSocketServerDlg.h : header file
//

#pragma once
#include "SocketServer.h"
#define PORT							10005

// CMFCBasic227CSocketServerDlg dialog
class CMFCBasic227CSocketServerDlg : public CDialogEx
{
protected:
	SocketServer m_server;
	
// Construction
public:
	CMFCBasic227CSocketServerDlg(CWnd* pParent = nullptr);	// standard constructor
	void AddEventString(const TCHAR* ap_string);						// 리스트박스는 문자열타입으로 관리

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC227CSOCKETSERVER_DIALOG };
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
	afx_msg void OnBnClickedOk();
	CListBox m_list1;
};
