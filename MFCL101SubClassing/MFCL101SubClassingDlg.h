
// MFCL101SubClassingDlg.h : header file
//

#pragma once
#include "SubClassingButton.h"

// CMFCL101SubClassingDlg dialog
class CMFCL101SubClassingDlg : public CDialogEx
{
protected:
	SubClassingButton m_increase_btn, m_decrease_btn;
	
// Construction
public:
	CMFCL101SubClassingDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL101SUBCLASSING_DIALOG };
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
	afx_msg void OnBnClickedIncBtn();
	afx_msg void OnBnClickedDecBtn();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};
