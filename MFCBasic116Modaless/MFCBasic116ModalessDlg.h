
// MFCBasic116ModalessDlg.h : header file
//

#pragma once
#include "Dialog1.h"

// CMFCBasic116ModalessDlg dialog
class CMFCBasic116ModalessDlg : public CDialogEx
{
protected:
	Dialog1* mp_dialog1 = NULL;

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
public:
	afx_msg void OnBnClickedBtnShow();
	afx_msg void OnDestroy();
protected:
	afx_msg LRESULT On44444(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedBtnStart();
};
