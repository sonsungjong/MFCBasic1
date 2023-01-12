// NewDlg.cpp : implementation file
//

#include "pch.h"
#include "ChildDlg.h"
#include "NewDlg.h"
#include "afxdialogex.h"


// NewDlg dialog

IMPLEMENT_DYNAMIC(NewDlg, CDialogEx)

NewDlg::NewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEW_DLG, pParent)
{

}

NewDlg::~NewDlg()
{
}

void NewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NewDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &NewDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &NewDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &NewDlg::OnBnClickedButton1)
	ON_WM_DESTROY()
	ON_MESSAGE(33001, &NewDlg::On33001)
	ON_MESSAGE(33002, &NewDlg::On33002)
	ON_MESSAGE(33003, &NewDlg::On33003)
	ON_BN_CLICKED(IDC_SEND_SECRET, &NewDlg::OnBnClickedSendSecret)
END_MESSAGE_MAP()


// NewDlg message handlers


void NewDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void NewDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();

	// 메시지를 보내 부모에서 닫게한다
	GetParent()->PostMessage(27000);
}

void NewDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}

// 에디트 컨트롤에 적은 값을 부모로 보냄
void NewDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_POPUP_EDIT1, str);
	GetParent()->SetDlgItemText(IDC_MAIN_EDIT1, str);
}

BOOL NewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	SetBackgroundColor(RGB(128, 128, 128));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

afx_msg LRESULT NewDlg::On33001(WPARAM wParam, LPARAM lParam)
{
	SetBackgroundColor(RGB(128, 128, 128));
	Invalidate();
	return 0;
}


afx_msg LRESULT NewDlg::On33002(WPARAM wParam, LPARAM lParam)
{
	SetBackgroundColor(RGB(0, 255, 0));
	Invalidate();
	return 0;
}


afx_msg LRESULT NewDlg::On33003(WPARAM wParam, LPARAM lParam)
{
	SetBackgroundColor(RGB(0, 0, 255));
	Invalidate();
	return 0;
}

// 부모로 메시지를 보내서 부모에서 받은 메시지를 조작하기
void NewDlg::OnBnClickedSendSecret()
{
	// TODO: Add your control notification handler code here
	CString* p_str = new CString;						// 문자열을 PostMessage로 넘기기 위해 동적할당
	int num = -314;

	GetDlgItemText(IDC_POPUP_EDIT1, *p_str);
	GetParent()->PostMessage(27001, num, (LPARAM)p_str);

	delete p_str;
}
