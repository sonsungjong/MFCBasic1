
// MFCBasic105EditControlDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic105EditControl.h"
#include "MFCBasic105EditControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic105EditControlDlg dialog



CMFCBasic105EditControlDlg::CMFCBasic105EditControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC105EDITCONTROL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

// 값으로 변수추가하면 연결
void CMFCBasic105EditControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic105EditControlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_READ_BTN, &CMFCBasic105EditControlDlg::OnBnClickedReadBtn)
	ON_BN_CLICKED(IDC_WRITE_BTN, &CMFCBasic105EditControlDlg::OnBnClickedWriteBtn)
	ON_BN_CLICKED(IDOK, &CMFCBasic105EditControlDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCBasic105EditControlDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMFCBasic105EditControlDlg message handlers

BOOL CMFCBasic105EditControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic105EditControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic105EditControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 읽기버튼
void CMFCBasic105EditControlDlg::OnBnClickedReadBtn()
{
	wchar_t str[4];
	
	int siz = sizeof(str)/2;		// wchar_t 는 한 문자에 2byte
	unsigned int len = GetDlgItem(IDC_MSG_EDIT)->GetWindowTextLength();		// 해당 아이템의 길이를 가져옴

	if (len < siz) {
		GetDlgItemText(IDC_MSG_EDIT, str, siz);
		MessageBox(str);
	}
	else {
		MessageBox(L"너무 길게 입력했습니다.");
	}
}

// 쓰기버튼
void CMFCBasic105EditControlDlg::OnBnClickedWriteBtn()
{
	SetDlgItemText(IDC_MSG_EDIT, L"sonsungjong");
	// SetDlgItemInt(IDC_MSG_EDIT, 5);
}


void CMFCBasic105EditControlDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCBasic105EditControlDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
