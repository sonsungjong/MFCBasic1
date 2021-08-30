// InnerDlg1.cpp : implementation file
//

#include "pch.h"
#include "MFCBasic116ModalessInner.h"
#include "InnerDlg1.h"
#include "afxdialogex.h"


// InnerDlg1 dialog

IMPLEMENT_DYNAMIC(InnerDlg1, CDialogEx)

InnerDlg1::InnerDlg1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INNER_DLG1, pParent)
{

}

InnerDlg1::~InnerDlg1()
{
}

void InnerDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InnerDlg1, CDialogEx)
	ON_BN_CLICKED(IDOK, &InnerDlg1::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &InnerDlg1::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_CHILD, &InnerDlg1::OnBnClickedBtnChild)
END_MESSAGE_MAP()


// InnerDlg1 message handlers


void InnerDlg1::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void InnerDlg1::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();
}


BOOL InnerDlg1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetBackgroundColor(RGB(0, 100, 250));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void InnerDlg1::OnBnClickedBtnChild()
{
	// TODO: Add your control notification handler code here
	int num = GetDlgItemInt(IDC_EDIT_CHILD);
	GetParent()->SetDlgItemInt(IDC_EDIT_PARENT, num);
}
