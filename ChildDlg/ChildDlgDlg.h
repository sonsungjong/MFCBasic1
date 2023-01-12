
// ChildDlgDlg.h : header file
//

#pragma once
// 대화상자 추가
#include "NewChild.h"
#include "NewDlg.h"

// CChildDlgDlg dialog
class CChildDlgDlg : public CDialogEx
{
private:
	NewChild* m_child_tap = NULL;
	NewDlg* m_popup_dlg = NULL;

	int m_tap_status = 0;

// Construction
public:
	CChildDlgDlg(CWnd* pParent = nullptr);	// standard constructor
	void DestroyPopup();
	void DrawBack();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHILDDLG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnDestroy();
protected:
	afx_msg LRESULT On27000(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On27001(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On33001(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On33002(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On33003(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedOpenNewDlg();
	afx_msg void OnBnClickedBroadBtn();
};
