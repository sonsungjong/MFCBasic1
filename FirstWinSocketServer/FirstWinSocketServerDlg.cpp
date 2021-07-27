
// FirstWinSocketServerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "FirstWinSocketServer.h"
#include "FirstWinSocketServerDlg.h"
#include "afxdialogex.h"
// Socket ���� �Լ��� ����ϱ� ���� ������ϰ� ���̺귯���� ���Խ�Ų��.
#include <WinSock2.h>
#include <WS2tcpip.h>		// InetPton �Լ� ����� ���� �߰�
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

	mh_client_socket = INVALID_SOCKET;	// -1, 0xFFFFFFFF, ~0
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
	ON_MESSAGE(25001, &CFirstWinSocketServerDlg::OnAcceptProc)
	ON_MESSAGE(25002, &CFirstWinSocketServerDlg::OnSocketMessage)
	ON_BN_CLICKED(IDOK, &CFirstWinSocketServerDlg::OnBnClickedOk)
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
	// ������ ��Ʈ��ũ ��ġ�� ���ε��ϱ� ���� ������ ������ ����
	// IP �ּ� ü��, ���α׷� �ĺ� ��ȣ(��Ʈ��ȣ)
	sockaddr_in addr_data = { AF_INET, htons(1900), };		// ��Ʈ��ũ ī�������� ����
	// IP �ּ� ����
	addr_data.sin_addr.s_addr = inet_addr(ipconfig);		// �ڵ��� ���Ÿ� ���� �����ۼ�

	// IPPROTO_TCP
	mh_listen_socket = socket(AF_INET, SOCK_STREAM, 0);	// socket : �ڵ�������

	// addr_data�� ������ ������ ����Ͽ� ������ ��Ʈ��ũ �ý��ۿ� ����
	bind(mh_listen_socket, (sockaddr*)&addr_data, sizeof(addr_data));		// binb : �ڵ��� ����
	// ������ ó���� ���� ����, Ŭ���̾�Ʈ�� ���� ������ ����
	listen(mh_listen_socket, 1);		// listen : �ڵ��� �߽����� -> ���ż���

	// �񵿱� accept
	WSAAsyncSelect(mh_listen_socket, m_hWnd, 25001, FD_ACCEPT);
	// mh_listen_socket�� ����ڰ� ������ �õ�(FD_ACCEPT)���� ��
	// ���� ��ȭ ����(m_hWnd)�� 25001�� �޽����� �߻��ϵ��� �񵿱⸦ �����Ѵ�.
	// �񵿱� Ȥ�� �����带 ���� accept�� �ϸ� �ȴ�.

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
	closesocket(mh_listen_socket);		// ���� ������ �����Ѵ�.

	// Ŭ���̾�Ʈ�� ������ ���¶�� ��ſ� ���ϵ� ����
	if (mh_client_socket != INVALID_SOCKET)
		closesocket(mh_client_socket);

	WSACleanup();		// ���� ���̺귯���� �׸� ����ϵ��� �����Ѵ�.
}

// #define _WINSOCK_DEPRECATED_NO_WARNINGS		framework.h��

void CFirstWinSocketServerDlg::OnLbnSelchangeEventList()
{
	// TODO: Add your control notification handler code here

}

// 25001�� �Լ�
afx_msg LRESULT CFirstWinSocketServerDlg::OnAcceptProc(WPARAM wParam, LPARAM lParam)
{
	// ������ Ŭ���̾�Ʈ�� ������ ������ ����ü�� �ʱ�ȭ
	sockaddr_in addr_data = { 0, };
	// ����ü ũ�� ����
	int data_size = sizeof(addr_data);
	// Ŭ���̾�Ʈ ������ ������ ��� (���� ���� ����)
	SOCKET h_client_socket = accept(mh_listen_socket, (sockaddr*)&addr_data, &data_size);

	wchar_t temp_ip_address[32];
	// addr_data ������ ���� ���·� ������ִ� IP �ּҸ� ���ڿ� ���·� �����ؼ� temp_ip_address �� ����
	InetNtop(AF_INET, &addr_data.sin_addr, temp_ip_address, 32);		// Ŭ���̾�Ʈ�� IP����
	AddEventString(temp_ip_address + CString(L" ���� ������ ������ �õ��ϰ� �ֽ��ϴ�."));

	CString str;
	if (mh_client_socket != INVALID_SOCKET) {		// �������� ���
		AddEventString(L"�̹� ������ Ŭ���̾�Ʈ�� �־ ������ �ź��Ͽ����ϴ�.");
		closesocket(h_client_socket);		// Ŭ���̾�Ʈ�� ����Ϸ� ���� ������ ����
	}
	else {
		AddEventString(L"Ŭ���̾�Ʈ�� �����Ͽ����ϴ�.");
		// ���� ������ Ŭ���̾�Ʈ�� �ڵ� ���� ��� ������ �����ؼ� ������ ������Ŵ, �ش� �ڵ�� ���
		mh_client_socket = h_client_socket;
		// ���� ������ �����ϰ� �񵿱�� üũ�� �� mh_client_socket ���� üũ�ؾ��� ����2
		// 1. �����Ͱ� ���ŵ� ��� 2. Ŭ���̾�Ʈ�� ������ ������ ���
		// �ΰ��� ������ �񵿱�� �����Ͽ� ��Ȳ�� �߻��� ���� 25002�� �޽����� ��ȭ���ڿ� �߻��ϵ��� ����
		WSAAsyncSelect(mh_client_socket, m_hWnd, 25002, FD_READ | FD_CLOSE);		// ���ô� or�� ����Ͽ� �ѹ��� üũ�������. FD_READ | FD_CLOSE

	}
	return 0;
}

// 25002�� �Լ� (������ �޽����� �����ϰų� Ŭ���̾�Ʈ�� �������ų�)
afx_msg LRESULT CFirstWinSocketServerDlg::OnSocketMessage(WPARAM wParam, LPARAM lParam)
{
	// lParam �� ������Ʈ�� �� �޽���(25002)�� �߻���Ų �̺�Ʈ ������ ����Ǿ� ����
	if (LOWORD(lParam) == FD_READ) {		// ������ ���� ��
		unsigned short body_size;
		recv(mh_client_socket, (char*)&body_size, 2, 0);			// ���Ź��� �����Ϳ��� 2byte���� ��´�.

		char* p_recv_data = new char[body_size];
		recv(mh_client_socket, p_recv_data, body_size, 0);		// ���Ź��� body_size ����Ʈ���� ��´�.

		AddEventString((wchar_t*)p_recv_data);		// ����Ʈ �ڽ��� ���
		delete[] p_recv_data;
	}
	else if (LOWORD(lParam) == FD_CLOSE){		// ����� ����
		closesocket(mh_client_socket);		// Ŭ���̾�Ʈ�� ����ϴ� ���� ����
		mh_client_socket = INVALID_SOCKET;		// ������ ���������� ���� (�ߺ����� ����)
		AddEventString(L"Ŭ���̾�Ʈ�� ������ �����߽��ϴ�.");
	}

	return 0;
}

/*
	#include <WinSock2.h>
	#pragma comment(lib, "WS2_32.lib")

	WSADATA temp;
	WSAStartup(0x0202, &temp);		// ������

	WSACleanup();		// ����

	socket -> bind -> listen -> accept -> recv -> closesocket
*/

void CFirstWinSocketServerDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}
