// WizardPage1.cpp : implementation file
//

#include "pch.h"
#include "MFCL235Wizard.h"
#include "WizardPage1.h"
#include "afxdialogex.h"


// WizardPage1 dialog

IMPLEMENT_DYNAMIC(WizardPage1, CDialogEx)

WizardPage1::WizardPage1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAGE1, pParent)
{

}

WizardPage1::~WizardPage1()
{
}

void WizardPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WizardPage1, CDialogEx)
	ON_BN_CLICKED(IDOK, &WizardPage1::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &WizardPage1::OnBnClickedCancel)
END_MESSAGE_MAP()


// WizardPage1 message handlers


void WizardPage1::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void WizardPage1::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();
}


BOOL WizardPage1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetBackgroundColor(RGB(228, 232, 300));

	return TRUE;
}

void WizardPage1::GetNumData(int* ap_num1, int* ap_num2)
{
	*ap_num1 = GetDlgItemInt(IDC_EDIT1);
	*ap_num2 = GetDlgItemInt(IDC_EDIT2);
}