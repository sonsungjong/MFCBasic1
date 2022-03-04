
// MFCL116PenDlg.h : header file
//

#pragma once
#include "DrawWnd.h"


// CMFCL116PenDlg dialog
class CMFCL116PenDlg : public CDialogEx
{
// Construction
public:
	CMFCL116PenDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL116PEN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	DrawWnd m_draw_wnd;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

};
