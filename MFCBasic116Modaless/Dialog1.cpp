// Dialog1.cpp : implementation file
//

#include "pch.h"
#include "MFCBasic116Modaless.h"
#include "Dialog1.h"
#include "afxdialogex.h"


// Dialog1 dialog

IMPLEMENT_DYNAMIC(Dialog1, CDialogEx)

Dialog1::Dialog1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

Dialog1::~Dialog1()
{
}

void Dialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Dialog1, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dialog1::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Dialog1::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_SET, &Dialog1::OnBnClickedBtnSet)
END_MESSAGE_MAP()


// Dialog1 message handlers


void Dialog1::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	
	//CDialogEx::OnOK();
}

// 부모에서 닫기
void Dialog1::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	GetParent()->PostMessage(44444);
	//CDialogEx::OnCancel();
}

// 비정형 대화상자 -> 부모대화상자 정수값전송
void Dialog1::OnBnClickedBtnSet()
{
	// TODO: Add your control notification handler code here
	int num = GetDlgItemInt(IDC_EDIT_NUM);
	GetParent()->SetDlgItemInt(IDC_EDIT_START, num);
}
