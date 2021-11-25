
// MFCBasic226CSocketClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic226CSocketClient.h"
#include "MFCBasic226CSocketClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic226CSocketClientDlg dialog



CMFCBasic226CSocketClientDlg::CMFCBasic226CSocketClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC226CSOCKETCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic226CSocketClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic226CSocketClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCBasic226CSocketClientDlg::OnBnClickedSendBtn)
END_MESSAGE_MAP()


// CMFCBasic226CSocketClientDlg message handlers

BOOL CMFCBasic226CSocketClientDlg::OnInitDialog()
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

void CMFCBasic226CSocketClientDlg::OnPaint()
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
HCURSOR CMFCBasic226CSocketClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic226CSocketClientDlg::OnBnClickedSendBtn()
{
	int value = GetDlgItemInt(IDC_VALUE_EDIT);

	CSocket temp;
	temp.Create();				// Client는 적지않는다.
	temp.Connect(_T("192.168.89.21"), 44444);			// 서버에 접속
	temp.Send(&value, sizeof(int));				// 4byte크기 메모리를 전송
}
