#pragma once
#include "MyInnerWnd.h"				// 자식윈도우 클래스 포함하기

// CMemoryDCInnerWndDlg dialog
class CMemoryDCInnerWndDlg : public CDialogEx
{
private:
	MyInnerWnd m_inner_wnd;

// Construction
public:
	CMemoryDCInnerWndDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEMORYDCINNERWND_DIALOG };
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
