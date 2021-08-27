
// MFCBasic115DoModalDlg.h : header file
//

#pragma once
#include "Dialog1.h"
#include "Dialog2.h"

// CMFCBasic115DoModalDlg dialog
class CMFCBasic115DoModalDlg : public CDialogEx
{
// Construction
public:
	CMFCBasic115DoModalDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC115DOMODAL_DIALOG };
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
	afx_msg void OnBnClickedShowNumDlg();
};
