#pragma once
#include "afxdialogex.h"


// LoginView dialog

class LoginView : public CDialogEx
{
	DECLARE_DYNAMIC(LoginView)

public:
	LoginView(CWnd* pParent = nullptr);   // standard constructor
	virtual ~LoginView();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedLoginBtn();
};
