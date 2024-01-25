// LoginView.cpp : implementation file
//

#include "pch.h"
#include "MVCMFC.h"
#include "afxdialogex.h"
#include "LoginView.h"


// LoginView dialog

IMPLEMENT_DYNAMIC(LoginView, CDialogEx)

LoginView::LoginView(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN_DLG, pParent)
{

}

LoginView::~LoginView()
{
}

void LoginView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(LoginView, CDialogEx)
	ON_BN_CLICKED(IDOK, &LoginView::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &LoginView::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_LOGIN_BTN, &LoginView::OnBnClickedLoginBtn)
END_MESSAGE_MAP()


// LoginView message handlers


void LoginView::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void LoginView::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void LoginView::OnBnClickedLoginBtn()
{
	::MessageBox(m_hWnd, L"LoginView Msg", L"LoginView", MB_OK);
}
