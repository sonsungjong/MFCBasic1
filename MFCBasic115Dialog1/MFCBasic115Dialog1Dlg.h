
// MFCBasic115Dialog1Dlg.h : header file
//

#pragma once


// CMFCBasic115Dialog1Dlg dialog
class CMFCBasic115Dialog1Dlg : public CDialogEx
{
// Construction
public:
	CMFCBasic115Dialog1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC115DIALOG1_DIALOG };
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
	afx_msg void OnBnClickedShowDlgBtn();
};
