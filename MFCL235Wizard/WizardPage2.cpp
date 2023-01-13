// WizardPage2.cpp : implementation file
//

#include "pch.h"
#include "MFCL235Wizard.h"
#include "WizardPage2.h"
#include "afxdialogex.h"


// WizardPage2 dialog

IMPLEMENT_DYNAMIC(WizardPage2, CDialogEx)

WizardPage2::WizardPage2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAGE2, pParent)
{

}

WizardPage2::~WizardPage2()
{
}

void WizardPage2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OP_LIST, m_op_list);
}


BEGIN_MESSAGE_MAP(WizardPage2, CDialogEx)
	ON_BN_CLICKED(IDOK, &WizardPage2::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &WizardPage2::OnBnClickedCancel)
END_MESSAGE_MAP()


// WizardPage2 message handlers


void WizardPage2::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void WizardPage2::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();
}


BOOL WizardPage2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetBackgroundColor(RGB(232, 200, 200, 228));

	m_op_list.InsertString(0, _T("+"));
	m_op_list.InsertString(1, _T("-"));
	m_op_list.InsertString(2, _T("*"));
	m_op_list.InsertString(3, _T("/"));
	m_op_list.SetCurSel(0);

	return TRUE;
}

// ¼±ÅÃÇÑ ¿¬»êÀÚ¸¦ ¼ýÀÚ·Î ¹ÝÈ¯ÇØÁÖ´Â ÇÔ¼ö
int WizardPage2::GetOpType()
{
	// µ¡¼À 0, –E¼À 1, °ö¼À 2, ³ª´°¼À 3
	int index = m_op_list.GetCurSel();
	return index;
}
