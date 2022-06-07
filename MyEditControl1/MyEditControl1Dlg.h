
// MyEditControl1Dlg.h : header file
//

#pragma once
#include "TW_CodeEdit.h"

// CMyEditControl1Dlg dialog
class CMyEditControl1Dlg : public CDialogEx
{
protected:
	TW_CodeEdit m_code_edit;

// Construction
public:
	CMyEditControl1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYEDITCONTROL1_DIALOG };
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
	afx_msg void OnClose();
	afx_msg void OnDestroy();
};
