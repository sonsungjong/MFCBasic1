
// MFCBasic104ScreenToClientDlg.h : header file
//

#pragma once


// CMFCBasic104ScreenToClientDlg dialog
class CMFCBasic104ScreenToClientDlg : public CDialogEx
{
// Construction
public:
	CMFCBasic104ScreenToClientDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC104SCREENTOCLIENT_DIALOG };
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
	afx_msg void OnBnClickedCancel();
	afx_msg void OnMove(int x, int y);
};
