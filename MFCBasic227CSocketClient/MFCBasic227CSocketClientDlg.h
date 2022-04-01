
// MFCBasic227CSocketClientDlg.h : header file
//

#pragma once
#include "SocketClient.h"
#define IP				_T("127.0.0.1")
#define PORT			10005

// CMFCBasic227CSocketClientDlg dialog
class CMFCBasic227CSocketClientDlg : public CDialogEx
{
protected:
	SocketClient m_client;
// Construction
public:
	CMFCBasic227CSocketClientDlg(CWnd* pParent = nullptr);	// standard constructor

	void AddEventString(const TCHAR* ap_string);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC227CSOCKETCLIENT_DIALOG };
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
	afx_msg void OnBnClickedSendBtn();
	CListBox m_list1;
};
