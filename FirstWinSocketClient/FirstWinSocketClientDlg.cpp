
// FirstWinSocketClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "FirstWinSocketClient.h"
#include "FirstWinSocketClientDlg.h"
#include "afxdialogex.h"

#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFirstWinSocketClientDlg dialog



CFirstWinSocketClientDlg::CFirstWinSocketClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FIRSTWINSOCKETCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	WSADATA temp;
	WSAStartup(0x0202, &temp);			// ���� ���̺귯�� ��� ���� ���·� �����
}

void CFirstWinSocketClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFirstWinSocketClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SEND_BTN, &CFirstWinSocketClientDlg::OnBnClickedSendBtn)
END_MESSAGE_MAP()


// CFirstWinSocketClientDlg message handlers

BOOL CFirstWinSocketClientDlg::OnInitDialog()
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

void CFirstWinSocketClientDlg::OnPaint()
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
HCURSOR CFirstWinSocketClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFirstWinSocketClientDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	WSACleanup();		// ���� ���̺귯���� ����
}


void CFirstWinSocketClientDlg::OnBnClickedSendBtn()
{
	// IP �ּ� ü��, ���α׷� �ĺ� ��ȣ(��Ʈ ��ȣ)
	// ������ �ڱ��� IP�� �Է������� Ŭ���̾�Ʈ�� �����ϰ����ϴ� ������ IP�� �Է��Ѵ�.
	sockaddr_in addr_data = { AF_INET, htons(1900), };
	addr_data.sin_addr.s_addr = inet_addr("192.168.0.60");		// �����ϰ����ϴ� ������ IP�� �Է�
	
	SOCKET h_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (0 == connect(h_socket, (sockaddr*)&addr_data, sizeof(addr_data)))		// ������ ���� : ������ return 0;
	{
		int num = GetDlgItemInt(IDC_NUM_EDIT);		// Edit Control�� �Է��� ������ ���
		send(h_socket, (char*)&num, sizeof(int), 0);
	}
	closesocket(h_socket);		// ���� ����
}

/*
	socket -> connect -> send -> closesocket
*/