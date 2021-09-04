
// MFCBasic122TimerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic122Timer.h"
#include "MFCBasic122TimerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCBasic122TimerDlg dialog



CMFCBasic122TimerDlg::CMFCBasic122TimerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC122TIMER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic122TimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic122TimerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCBasic122TimerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCBasic122TimerDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_GET_TIME, &CMFCBasic122TimerDlg::OnBnClickedGetTime)
	ON_BN_CLICKED(IDC_MFC_TIME, &CMFCBasic122TimerDlg::OnBnClickedMfcTime)
	ON_BN_CLICKED(IDC_SYSTEM_TIME, &CMFCBasic122TimerDlg::OnBnClickedSystemTime)
	ON_BN_CLICKED(IDC_START_TIMER, &CMFCBasic122TimerDlg::OnBnClickedStartTimer)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_STOP_TIMER, &CMFCBasic122TimerDlg::OnBnClickedStopTimer)
	ON_BN_CLICKED(IDC_CALLBACK_TIME, &CMFCBasic122TimerDlg::OnBnClickedCallbackTime)
END_MESSAGE_MAP()


// CMFCBasic122TimerDlg message handlers

BOOL CMFCBasic122TimerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCBasic122TimerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic122TimerDlg::OnPaint()
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
HCURSOR CMFCBasic122TimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic122TimerDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCBasic122TimerDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	int result = MessageBox(L"종료하시겠습니까?", L"종료", MB_OKCANCEL | MB_ICONQUESTION);
	if (result == IDOK) {
		CDialogEx::OnCancel();
	}
}


void CMFCBasic122TimerDlg::OnBnClickedGetTime()
{
	// TODO: Add your control notification handler code here
	time_t cur_time = time(NULL);			// 1970년 1월 1일부터 계산한 현재 second값
	tm* local_time = localtime(&cur_time);

	CString str;
	str.Format(L"%d년 %d월 %d일 %d시 %d분 %d초", local_time->tm_year+1900, local_time->tm_mon+1, local_time->tm_mday, local_time->tm_hour, local_time->tm_min, local_time->tm_sec);
	SetDlgItemText(IDC_SHOW_TIME, str);
}


void CMFCBasic122TimerDlg::OnBnClickedMfcTime()
{
	// TODO: Add your control notification handler code here
	CTime mfc_time = CTime::GetCurrentTime();

	CString str;
	str.Format(L"%d년 %d월 %d일 %d시 %d분 %d초", mfc_time.GetYear(), mfc_time.GetMonth(), mfc_time.GetDay(), mfc_time.GetHour(), mfc_time.GetMinute(), mfc_time.GetSecond());
	SetDlgItemText(IDC_SHOW_TIME, str);
}


void CMFCBasic122TimerDlg::OnBnClickedSystemTime()
{
	// TODO: Add your control notification handler code here
	SYSTEMTIME sys_time;
	GetLocalTime(&sys_time);

	CString str;
	str.Format(L"%d년 %d월 %d일 %d시 %d분 %d초 (%dms)", sys_time.wYear, sys_time.wMonth, sys_time.wDay, sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds);
	SetDlgItemText(IDC_SHOW_TIME, str);
}

// SetTimer 타이머

void CMFCBasic122TimerDlg::OnBnClickedStartTimer()
{
	// TODO: Add your control notification handler code here
	if (timer_flag != 1) {
		if (timer_flag == 2) {
			KillTimer(2);
		}

		SetTimer(1, 500, NULL);		// 타이머 만들기(ID, ms, functionPointer=WM_TIMER)
		timer_flag = 1;
	}
}


void CMFCBasic122TimerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1 || nIDEvent == 2) {
		OnBnClickedSystemTime();
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}
}

void CMFCBasic122TimerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	if (timer_flag == 1) {
		KillTimer(1);
	}
	else if (timer_flag == 2) {
		KillTimer(2);
	}
}

void CMFCBasic122TimerDlg::OnBnClickedStopTimer()
{
	// TODO: Add your control notification handler code here
	if (timer_flag == 1) {
		KillTimer(1);
		timer_flag = 0;
	}
	else if (timer_flag == 2) {
		KillTimer(2);
		timer_flag = 0;
	}
}

void CALLBACK MyTimerProc(HWND h_wnd, UINT msg_id, UINT_PTR timer_id, DWORD time)
{
	if (timer_id == 2) {
		::SendMessage(h_wnd, WM_COMMAND, MAKEWPARAM(IDC_SYSTEM_TIME, BN_CLICKED), 0);
	}
}

void CMFCBasic122TimerDlg::OnBnClickedCallbackTime()
{
	// TODO: Add your control notification handler code here
	if (timer_flag != 2) {
		if (timer_flag == 1) {
			KillTimer(1);
		}
		SetTimer(2, 1000, MyTimerProc);		// 타이머 만들기(ID, ms, functionPointer=WM_TIMER)
		timer_flag = 2;
	}
}
