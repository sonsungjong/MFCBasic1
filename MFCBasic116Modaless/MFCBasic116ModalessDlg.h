
// MFCBasic116ModalessDlg.h : header file
//

#pragma once


// CMFCBasic116ModalessDlg dialog
class CMFCBasic116ModalessDlg : public CDialogEx
{
// Construction
public:
	CMFCBasic116ModalessDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC116MODALESS_DIALOG };
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
