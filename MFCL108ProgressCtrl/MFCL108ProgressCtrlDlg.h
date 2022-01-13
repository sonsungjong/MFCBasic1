
// MFCL108ProgressCtrlDlg.h : header file
//

#pragma once
#include "UserProgress.h"

// CMFCL108ProgressCtrlDlg dialog
class CMFCL108ProgressCtrlDlg : public CDialogEx
{
// Construction
public:
	CMFCL108ProgressCtrlDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL108PROGRESSCTRL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	//CRect m_user_rect;
	UserProgress m_my_progress;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_progress1;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};
