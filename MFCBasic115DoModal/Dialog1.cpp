// Dialog1.cpp : implementation file
//

#include "pch.h"
#include "MFCBasic115DoModal.h"
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
END_MESSAGE_MAP()


// Dialog1 message handlers
