
// LadderGameDlg.h : header file
//

#pragma once
#include "LadderWnd.h"					// 자식 inner 클래스 포함

// CLadderGameDlg dialog
class CLadderGameDlg : public CDialogEx
{
private:
	LadderWnd m_ladder_wnd;

// Construction
public:
	CLadderGameDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LADDERGAME_DIALOG };
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
	afx_msg void OnDestroy();
};
