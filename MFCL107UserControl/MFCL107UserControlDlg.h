
// MFCL107UserControlDlg.h : header file
//

#pragma once
#include "UserWnd.h"

// CMFCL107UserControlDlg dialog
class CMFCL107UserControlDlg : public CDialogEx
{
private:
	UserWnd m_user_wnd;

// Construction
public:
	CMFCL107UserControlDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL107USERCONTROL_DIALOG };
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
};
