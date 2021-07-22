
// FirstWinSocketServerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "FirstWinSocketServer.h"
#include "FirstWinSocketServerDlg.h"
#include "afxdialogex.h"
// Socket ���� �Լ��� ����ϱ� ���� ������ϰ� ���̺귯���� ���Խ�Ų��.
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFirstWinSocketServerDlg dialog



CFirstWinSocketServerDlg::CFirstWinSocketServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FIRSTWINSOCKETSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	WSADATA temp;
	WSAStartup(0x0202, &temp);		// ���� ���̺귯���� ��� ���� ���·� �����. (0x0202 == 2.2)
}

void CFirstWinSocketServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENT_LIST, m_event_list);
}

BEGIN_MESSAGE_MAP(CFirstWinSocketServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_LBN_SELCHANGE(IDC_EVENT_LIST, &CFirstWinSocketServerDlg::OnLbnSelchangeEventList)
	ON_BN_CLICKED(IDC_WAIT_RECV_BTN, &CFirstWinSocketServerDlg::OnBnClickedWaitRecvBtn)
END_MESSAGE_MAP()


// CFirstWinSocketServerDlg message handlers

BOOL CFirstWinSocketServerDlg::OnInitDialog()
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

void CFirstWinSocketServerDlg::OnPaint()
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
HCURSOR CFirstWinSocketServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFirstWinSocketServerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	WSACleanup();		// ���� ���̺귯���� �׸� ����ϵ��� �����Ѵ�.
}

// #define _WINSOCK_DEPRECATED_NO_WARNINGS		framework.h��

void CFirstWinSocketServerDlg::OnLbnSelchangeEventList()
{
	// TODO: Add your control notification handler code here

}

/*
	#include <WinSock2.h>
	#pragma comment(lib, "WS2_32.lib")

	WSADATA temp;
	WSAStartup(0x0202, &temp);		// ������

	WSACleanup();		// ����
*/


void CFirstWinSocketServerDlg::OnBnClickedWaitRecvBtn()
{
	// ������ ��Ʈ��ũ ��ġ�� ���ε��ϱ� ���� ������ ������ ����
	// IP �ּ� ü��, ���α׷� �ĺ� ��ȣ(��Ʈ��ȣ)
	sockaddr_in addr_data = {AF_INET, htons(1900), };		// ��Ʈ��ũ ī�������� ����
	// IP �ּ� ����
	addr_data.sin_addr.s_addr = inet_addr("192.168.0.60");		// �ڵ��� ���Ÿ� ���� �����ۼ�
	
	// IPPROTO_TCP
	SOCKET h_listen_socket = socket(AF_INET, SOCK_STREAM, 0);	// socket : �ڵ�������

	// addr_data�� ������ ������ ����Ͽ� ������ ��Ʈ��ũ �ý��ۿ� ����
	bind(h_listen_socket, (sockaddr*)&addr_data, sizeof(addr_data));		// binb : �ڵ��� ����
	// ������ ó���� ���� ����, Ŭ���̾�Ʈ�� ���� ������ ����
	listen(h_listen_socket, 1);		// listen : �ڵ��� �߽����� -> ���ż���

	CString str;
	int addr_data_size = sizeof(addr_data), temp, read_bytes;
	// Ŭ���̾�Ʈ ������ ������ ����Ѵ�. --���� ���� ����

	SOCKET h_client_socket = accept(h_listen_socket, (sockaddr*)&addr_data, &addr_data_size);		// accept : ��ȭ�� �޴� ���� (��ǥ��ȭ + �������� ��ȭ1��)
	while (1) {
		read_bytes = recv(h_client_socket, (char*)&temp, 4, 0);		// �����ð����� �����͸� �޾� temp������ ����. (4byte)
		if (read_bytes == 4) {		// �������� 4byte ���
			str.Format(L"%d", temp);		// �������� ���ڿ��� ��ȯ�Ѵ�.
			AddEventString(str);				// ����Ʈ �ڽ��� ����Ѵ�.
			break;
		}
	}
	closesocket(h_client_socket);		// Ŭ���̾�Ʈ�� ����ϴ� ������ �����Ѵ�. ��ȭ����
	closesocket(h_listen_socket);		// ���� ������ �����Ѵ�.
}

/*
	socket -> bind -> listen -> accept -> recv -> closesocket
*/