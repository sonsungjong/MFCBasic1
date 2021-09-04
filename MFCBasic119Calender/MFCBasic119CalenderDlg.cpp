
// MFCBasic119CalenderDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic119Calender.h"
#include "MFCBasic119CalenderDlg.h"
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


// CMFCBasic119CalenderDlg dialog



CMFCBasic119CalenderDlg::CMFCBasic119CalenderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC119CALENDER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic119CalenderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CALENDAR, calendar);
	DDX_Control(pDX, IDC_DATE_STATIC, date_static);
}

BEGIN_MESSAGE_MAP(CMFCBasic119CalenderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(MCN_SELCHANGE, IDC_CALENDAR, &CMFCBasic119CalenderDlg::OnMcnSelchangeCalendar)
	ON_BN_CLICKED(IDOK, &CMFCBasic119CalenderDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCBasic119CalenderDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SET, &CMFCBasic119CalenderDlg::OnBnClickedSet)
END_MESSAGE_MAP()


// CMFCBasic119CalenderDlg message handlers

BOOL CMFCBasic119CalenderDlg::OnInitDialog()
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
	font.CreatePointFont(120, L"굴림");
	date_static.SetFont(&font);

	ShowNote();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCBasic119CalenderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCBasic119CalenderDlg::OnPaint()
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
HCURSOR CMFCBasic119CalenderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic119CalenderDlg::OnMcnSelchangeCalendar(NMHDR* pNMHDR, LRESULT* pResult)
{
	//LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	ShowNote();

	*pResult = 0;
}


void CMFCBasic119CalenderDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCBasic119CalenderDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	int result = MessageBox(L"종료하시겠습니까?", L"종료", MB_OKCANCEL | MB_ICONQUESTION);
	if (result == IDOK) {
		CDialogEx::OnCancel();
	}
}


void CMFCBasic119CalenderDlg::OnBnClickedSet()
{
	// TODO: Add your control notification handler code here
	SYSTEMTIME time;
	calendar.GetCurSel(&time);

	CString str;
	str.Format(L"%04d%02d%02d.dat", time.wYear, time.wMonth, time.wDay);

	FILE* writeFile;
	if (0 == _wfopen_s(&writeFile, str, L"wt,ccs=UNICODE")) {
		GetDlgItemText(IDC_NOTE, str);
		str.Replace(L"\r\n", L"\n");
		fwrite((const wchar_t*)str, (str.GetLength()+1)*2, 1, writeFile);
		fclose(writeFile);	
	}
}

void CMFCBasic119CalenderDlg::ShowNote()
{
	SYSTEMTIME time;
	wchar_t* week[7] = { L"일", L"월", L"화", L"수", L"목", L"금", L"토" };
	calendar.GetCurSel(&time);

	CString str;
	str.Format(L"%d년 %d월 %d일 [ %s요일 ]", time.wYear, time.wMonth, time.wDay, week[time.wDayOfWeek]);
	SetDlgItemText(IDC_DATE_STATIC, str);

	str.Format(L"%04d%02d%02d.dat", time.wYear, time.wMonth, time.wDay);
	FILE* readFile;
	if (0 == _wfopen_s(&readFile, str, L"rt,ccs=UNICODE")) {
		wchar_t temp_str[1024];
		str = L"";
		while (fgetws(temp_str, 1024, readFile) != NULL) {
			str += temp_str;
		}
		fclose(readFile);

		str.Replace(L"\n", L"\r\n");
		SetDlgItemText(IDC_NOTE, str);
	}
	else {
		SetDlgItemText(IDC_NOTE, L"");
	}
}