
// MFCL122HookingDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL122Hooking.h"
#include "MFCL122HookingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL122HookingDlg dialog



CMFCL122HookingDlg::CMFCL122HookingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL122HOOKING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL122HookingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENT_LIST, m_event_list);
	DDX_Control(pDX, IDC_SHOW_EDIT, m_show_edit);
}

BEGIN_MESSAGE_MAP(CMFCL122HookingDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_MESSAGE(27001, &CMFCL122HookingDlg::On27001)
	ON_BN_CLICKED(IDOK, &CMFCL122HookingDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMFCL122HookingDlg message handlers

BOOL CMFCL122HookingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_hook_dll = ::LoadLibrary(TEXT("MFCL122HookingDll.dll"));						// dll라이브러리 불러오기
	void (*fp)(HWND) = (void(*)(HWND))GetProcAddress(m_hook_dll, "InstallKeyHook");							// 인자가 HWND인 InstallKeyHook 함수를 저장
	if (fp != NULL) (*fp)(m_hWnd);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL122HookingDlg::OnPaint()
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
HCURSOR CMFCL122HookingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCL122HookingDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	void (*fp)() = (void(*)())GetProcAddress(m_hook_dll, "UnInstallKeyHook");						// 인자가 없는 UnInstallKeyHook 함수를 저장
	if (fp != NULL) (*fp)();
	::FreeLibrary(m_hook_dll);						// dll연결 해제
}


afx_msg LRESULT CMFCL122HookingDlg::On27001(WPARAM wParam, LPARAM lParam)
{
	CString str;
	if (lParam & 0x80000000) {
		str.Format(TEXT("[Key Up] %08X(%c) %08X"), wParam, wParam, lParam);
		m_show_edit.PostMessage(WM_KEYUP, wParam, lParam);
	}
	else {
		str.Format(TEXT("[Key Down] %08X(%c) %08X"), wParam, wParam, lParam);
		m_show_edit.PostMessage(WM_KEYDOWN, wParam, lParam);
	}
	int index = m_event_list.InsertString(-1, str);
	m_event_list.SetCurSel(index);

	return 0;
}

void CMFCL122HookingDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}
