
// MFCBasic227CSocketServerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic227CSocketServer.h"
#include "MFCBasic227CSocketServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic227CSocketServerDlg dialog



CMFCBasic227CSocketServerDlg::CMFCBasic227CSocketServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC227CSOCKETSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CMFCBasic227CSocketServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
}

BEGIN_MESSAGE_MAP(CMFCBasic227CSocketServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCBasic227CSocketServerDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMFCBasic227CSocketServerDlg message handlers

BOOL CMFCBasic227CSocketServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// m_server.Create(44445, 1, _T("192.168.--.--"));				// port, 1, L"IP"
	m_server.Create(PORT);				// port번호
	m_server.Listen();							// 접근허용

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic227CSocketServerDlg::OnPaint()
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
HCURSOR CMFCBasic227CSocketServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic227CSocketServerDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}

void CMFCBasic227CSocketServerDlg::AddEventString(const TCHAR* ap_string)
{
	int index = m_list1.InsertString(-1, ap_string);				// 맨끝에 추가하고 해당 인덱스를 저장
	m_list1.SetCurSel(index);						// 해당 인덱스로 커서이동
}