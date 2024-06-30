
// MFCS003CTaskDialog3ProgressBarDlg.h : header file
//

#pragma once
#include "TaskDialogProgressBar.h"

// CMFCS003CTaskDialog3ProgressBarDlg dialog
class CMFCS003CTaskDialog3ProgressBarDlg : public CDialogEx
{
// Construction
public:
	CMFCS003CTaskDialog3ProgressBarDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCS003CTASKDIALOG3PROGRESSBAR_DIALOG };
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
};
