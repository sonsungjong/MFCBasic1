
// MFCBasic116LoginDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic116Login.h"
#include "MFCBasic116LoginDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic116LoginDlg dialog



CMFCBasic116LoginDlg::CMFCBasic116LoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC116LOGIN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic116LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic116LoginDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCBasic116LoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCBasic116LoginDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_NCCREATE()
END_MESSAGE_MAP()


// CMFCBasic116LoginDlg message handlers

BOOL CMFCBasic116LoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	PostMessage(23000);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic116LoginDlg::OnPaint()
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
HCURSOR CMFCBasic116LoginDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic116LoginDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCBasic116LoginDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CMFCBasic116LoginDlg::CloseLoginDialog()
{
	if (mp_login_dlg != NULL) {
		mp_login_dlg->DestroyWindow();
		delete mp_login_dlg;
		mp_login_dlg = NULL;
	}
}

// 메시지 등록 따로 안하고 WindowProc 가상함수 추가해서 사용
LRESULT CMFCBasic116LoginDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if (message == 23000) {
		//ShowWindow(SW_HIDE);								// 숨겼다가 2초후에 나오게 하자(테스트)
		//SetTimer(1, 2000, NULL);
		mp_login_dlg = new LoginDlg;
		mp_login_dlg->Create(IDD_LOGIN, this);
	}
	else if (message == 23001) {
		CloseLoginDialog();
		if ((int)wParam == 1) {
			LONG ex_style = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);									// 현재 윈도우의 속성을 가져옴
			::SetWindowLong(m_hWnd, GWL_EXSTYLE, ex_style & ~WS_EX_LAYERED);					// LAYERED 속성만 제거함
			Invalidate(TRUE);
		}
		else if ((int)wParam == 0) {
			EndDialog(IDCANCEL);
		}

	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}


void CMFCBasic116LoginDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		//ShowWindow(SW_SHOWNORMAL);								// 하이드 취소
		//KillTimer(1);
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}

}


void CMFCBasic116LoginDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	//KillTimer(1);

	if (mp_login_dlg != NULL) {
		mp_login_dlg->DestroyWindow();
		delete mp_login_dlg;
		mp_login_dlg = NULL;
	}
}

// Non-Client Create (NCCreate->Create->InitialDialog)
BOOL CMFCBasic116LoginDlg::OnNcCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (!CDialogEx::OnNcCreate(lpCreateStruct))
		return FALSE;

	// TODO:  Add your specialized creation code here
	// 로그인 하기 전까지 투명처리
	LONG ex_style = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);									// 현재 윈도우의 속성을 가져옴
	::SetWindowLong(m_hWnd, GWL_EXSTYLE, ex_style | WS_EX_LAYERED);					// LAYERED 속성을 추가함

	return TRUE;
}
