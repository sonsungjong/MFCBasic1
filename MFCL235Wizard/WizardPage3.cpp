// WizardPage3.cpp : implementation file
//

#include "pch.h"
#include "MFCL235Wizard.h"
#include "WizardPage3.h"
#include "afxdialogex.h"


// WizardPage3 dialog

IMPLEMENT_DYNAMIC(WizardPage3, CDialogEx)

WizardPage3::WizardPage3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAGE3, pParent)
{

}

WizardPage3::~WizardPage3()
{
}

void WizardPage3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WizardPage3, CDialogEx)
	ON_BN_CLICKED(IDOK, &WizardPage3::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &WizardPage3::OnBnClickedCancel)
END_MESSAGE_MAP()


// WizardPage3 message handlers


void WizardPage3::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void WizardPage3::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();
}


BOOL WizardPage3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetBackgroundColor(RGB(228, 160, 232));

	return TRUE;
}

void WizardPage3::SetResultValue(int a_result)
{
	SetDlgItemInt(IDC_RESULT_EDIT, a_result);
}
