// Dialog2.cpp : implementation file
//

#include "pch.h"
#include "MFCBasic115DoModal.h"
#include "Dialog2.h"
#include "afxdialogex.h"


// Dialog2 dialog

IMPLEMENT_DYNAMIC(Dialog2, CDialogEx)

Dialog2::Dialog2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

Dialog2::~Dialog2()
{
}

void Dialog2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Dialog2, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dialog2::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Dialog2::OnBnClickedCancel)
END_MESSAGE_MAP()

// 화면에 나타나기 전에 실행되는 함수
BOOL Dialog2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO : m_num을 IDC_CHILD_EDIT에 셋팅
	if (m_num != 0) {
		SetDlgItemInt(IDC_CHILD_EDIT, m_num);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void Dialog2::SetNum(int a_num)
{
	m_num = a_num;
}

int Dialog2::GetNum()
{
	return m_num;
}

void Dialog2::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_num = GetDlgItemInt(IDC_CHILD_EDIT);

	CDialogEx::OnOK();
}


void Dialog2::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here

	CDialogEx::OnCancel();
}
