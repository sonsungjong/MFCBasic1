// NewChild.cpp : implementation file
//

#include "pch.h"
#include "ChildDlg.h"
#include "NewChild.h"
#include "afxdialogex.h"


// NewChild dialog

IMPLEMENT_DYNAMIC(NewChild, CDialogEx)

NewChild::NewChild(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEW_CHILD, pParent)
{

}

NewChild::~NewChild()
{
}

void NewChild::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NewChild, CDialogEx)
	ON_BN_CLICKED(IDOK, &NewChild::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &NewChild::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SEND_BTN, &NewChild::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_TAP1, &NewChild::OnBnClickedTap1)
	ON_BN_CLICKED(IDC_TAP2, &NewChild::OnBnClickedTap2)
	ON_BN_CLICKED(IDC_TAP3, &NewChild::OnBnClickedTap3)
END_MESSAGE_MAP()


// NewChild message handlers


void NewChild::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void NewChild::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();
}

void NewChild::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL NewChild::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetBackgroundColor(RGB(0, 100, 250));

	return TRUE;
}

void NewChild::OnBnClickedSendBtn()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_CHILD_EDIT1, str);
	GetParent()->SetDlgItemText(IDC_MAIN_EDIT1, str);
}


void NewChild::OnBnClickedTap1()
{
	// TODO: Add your control notification handler code here
	GetParent()->PostMessage(33001);
}


void NewChild::OnBnClickedTap2()
{
	// TODO: Add your control notification handler code here
	GetParent()->PostMessage(33002);
}


void NewChild::OnBnClickedTap3()
{
	// TODO: Add your control notification handler code here
	GetParent()->PostMessage(33003);
}
