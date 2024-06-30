
// MFCS002CTaskDialog2AddBtnDlg.h : header file
//

#pragma once
#include "MyUserTaskDlg.h"

// CMFCS002CTaskDialog2AddBtnDlg dialog
class CMFCS002CTaskDialog2AddBtnDlg : public CDialogEx
{
// Construction
public:
	CMFCS002CTaskDialog2AddBtnDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCS002CTASKDIALOG2ADDBTN_DIALOG };
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
