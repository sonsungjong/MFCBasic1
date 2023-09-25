// InputData.cpp : implementation file
//

#include "pch.h"
#include "GdipUserControl1.h"
#include "afxdialogex.h"
#include "InputData.h"


// InputData dialog

IMPLEMENT_DYNAMIC(InputData, CDialogEx)

InputData::InputData(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INPUT_DATA_DLG, pParent)
{

}

InputData::~InputData()
{
}

void InputData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InputData, CDialogEx)
	ON_BN_CLICKED(IDOK, &InputData::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &InputData::OnBnClickedCancel)
END_MESSAGE_MAP()


// InputData message handlers


void InputData::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
	AfxMessageBox(L"ok");
}


void InputData::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
