
// MFCBasic226CSocketClientDlg.h : header file
//

#pragma once


// CMFCBasic226CSocketClientDlg dialog
class CMFCBasic226CSocketClientDlg : public CDialogEx
{
// Construction
public:
	CMFCBasic226CSocketClientDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC226CSOCKETCLIENT_DIALOG };
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
	afx_msg void OnBnClickedSendBtn();
};
