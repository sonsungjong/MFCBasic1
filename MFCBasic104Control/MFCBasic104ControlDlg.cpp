
// MFCBasic104ControlDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic104Control.h"
#include "MFCBasic104ControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMFCBasic104ControlDlg::CMFCBasic104ControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC104CONTROL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic104ControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic104ControlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SHOW_MSG_BTN, &CMFCBasic104ControlDlg::OnBnClickedShowMsgBtn)
END_MESSAGE_MAP()


// CMFCBasic104ControlDlg message handlers

BOOL CMFCBasic104ControlDlg::OnInitDialog()
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

void CMFCBasic104ControlDlg::OnPaint()
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
HCURSOR CMFCBasic104ControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*
	대화상자 리소스 편집

	On : 메시지 처리 함수라는 접두어표시
	Bn : 버튼
	Clicked : 클릭됨
*/

void CMFCBasic104ControlDlg::OnBnClickedShowMsgBtn()
{
	// TODO: Add your control notification handler code here
	wchar_t str[64];		// C++
	CString show_str;		// MFC

	GetDlgItemText(IDC_INPUT_MSG_EDIT, str, 64);
	show_str.Format(L"사용자가 입력한 문자열 : %s", str);
	// show_str = L"사용자가 입력한 문자열 : " + (CString)str;	 //대입연산자 오버로딩 활용

	//MessageBox(str);		// Win32
	AfxMessageBox(show_str);		// MFC
}
