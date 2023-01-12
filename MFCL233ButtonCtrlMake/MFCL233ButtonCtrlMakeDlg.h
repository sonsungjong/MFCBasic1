#pragma once
#include "TipsButton.h"

// CMFCL233ButtonCtrlMakeDlg dialog
class CMFCL233ButtonCtrlMakeDlg : public CDialogEx
{
private:
	TipsButton m_test_btn1;
	TipsButton m_test_btn2;

// Construction
public:
	CMFCL233ButtonCtrlMakeDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL233BUTTONCTRLMAKE_DIALOG };
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
protected:
	afx_msg LRESULT OnLmBtnClicked(WPARAM wParam, LPARAM lParam);
};
