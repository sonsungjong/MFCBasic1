
// MFCBasic226CSocketServerDlg.h : header file
//

#pragma once
#include "MFCServer.h"

// CMFCBasic226CSocketServerDlg dialog
class CMFCBasic226CSocketServerDlg : public CDialogEx
{
protected:
	MFCServer m_server;

// Construction
public:
	CMFCBasic226CSocketServerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC226CSOCKETSERVER_DIALOG };
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
};
