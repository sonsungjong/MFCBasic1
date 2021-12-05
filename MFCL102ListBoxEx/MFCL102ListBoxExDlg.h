
// MFCL102ListBoxExDlg.h : header file
//

#pragma once


// CMFCL102ListBoxExDlg dialog
class CMFCL102ListBoxExDlg : public CDialogEx
{
// Construction
public:
	CMFCL102ListBoxExDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL102LISTBOXEX_DIALOG };
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
