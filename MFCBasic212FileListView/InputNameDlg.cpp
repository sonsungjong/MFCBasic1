// InputNameDlg.cpp : implementation file
//

#include "pch.h"
#include "MFCBasic212FileListView.h"
#include "InputNameDlg.h"
#include "afxdialogex.h"


// InputNameDlg dialog

IMPLEMENT_DYNAMIC(InputNameDlg, CDialogEx)

InputNameDlg::InputNameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INPUT_NAME_DLG, pParent)
{

}

InputNameDlg::~InputNameDlg()
{
}

void InputNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InputNameDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CREATE_BTN, &InputNameDlg::OnBnClickedCreateBtn)
	ON_BN_CLICKED(IDC_CANCEL_BTN, &InputNameDlg::OnBnClickedCancelBtn)
END_MESSAGE_MAP()


// InputNameDlg message handlers


void InputNameDlg::OnBnClickedCreateBtn()
{
	// TODO: Add your control notification handler code here
	if (GetDlgItemText(IDC_NAME_EDIT, m_name) > 0) CDialogEx::OnOK();
}


void InputNameDlg::OnBnClickedCancelBtn()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
