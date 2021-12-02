
// MFCBasic227CSocketClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic227CSocketClient.h"
#include "MFCBasic227CSocketClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic227CSocketClientDlg dialog



CMFCBasic227CSocketClientDlg::CMFCBasic227CSocketClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC227CSOCKETCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic227CSocketClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic227CSocketClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCBasic227CSocketClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCBasic227CSocketClientDlg::OnBnClickedSendBtn)
END_MESSAGE_MAP()


// CMFCBasic227CSocketClientDlg message handlers

BOOL CMFCBasic227CSocketClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_client.Create();
	m_client.Connect(IP, PORT);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic227CSocketClientDlg::OnPaint()
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
HCURSOR CMFCBasic227CSocketClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic227CSocketClientDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCBasic227CSocketClientDlg::OnBnClickedSendBtn()
{
	int value = GetDlgItemInt(IDC_EDIT1);
	//CSocket temp;
	//temp.Create();
	//temp.Connect(IP, PORT);
	//temp.Send(&value, sizeof(int));
	
	// 양방향하려면 CSocket에서 상속받고 멤버변수로 사용
	m_client.Send(&value, sizeof(int));
}
