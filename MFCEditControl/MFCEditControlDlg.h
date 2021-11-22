
// MFCEditControlDlg.h : header file
//

#pragma once


// CMFCEditControlDlg dialog
class CMFCEditControlDlg : public CDialogEx
{
protected:
	CEdit m_edit1;
	CEdit m_edit2;
	CString m_getEdit1;
	CString m_getEdit2;

// Construction
public:
	CMFCEditControlDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCEDITCONTROL_DIALOG };
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnSetfocusEdit1();
	afx_msg void OnEnKillfocusEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnSetfocusEdit2();
	afx_msg void OnEnKillfocusEdit2();
	afx_msg void OnBnClickedButton2();
};
