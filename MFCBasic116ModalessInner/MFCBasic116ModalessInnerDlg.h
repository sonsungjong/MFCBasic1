
// MFCBasic116ModalessInnerDlg.h : header file
//

#pragma once
#include "InnerDlg1.h"

// CMFCBasic116ModalessInnerDlg dialog
class CMFCBasic116ModalessInnerDlg : public CDialogEx
{
protected:
	InnerDlg1* mp_innerDlg1 = NULL;
// Construction
public:
	CMFCBasic116ModalessInnerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC116MODALESSINNER_DIALOG };
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
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnParent();
};
