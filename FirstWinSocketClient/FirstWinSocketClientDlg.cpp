
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

	mh_socket = INVALID_SOCKET;		// ���� �ڵ� �ʱ�ȭ (-1 or 0xFFFFFFFF)
	m_is_connected = 0;						// ���� ���� �ʱ�ȭ
}

void CFirstWinSocketClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENT_LIST, m_event_list);
}

BEGIN_MESSAGE_MAP(CFirstWinSocketClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SEND_BTN, &CFirstWinSocketClientDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CFirstWinSocketClientDlg::OnBnClickedConnectBtn)
	ON_BN_CLICKED(IDC_DISCONNECT_BTN, &CFirstWinSocketClientDlg::OnBnClickedDisconnectBtn)
	ON_MESSAGE(26001, &CFirstWinSocketClientDlg::OnConnected)
	ON_MESSAGE(26002, &CFirstWinSocketClientDlg::OnSocketMessage)
	ON_BN_CLICKED(IDOK, &CFirstWinSocketClientDlg::OnBnClickedOk)
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
	// ������ ���� ���¶�� ���ӿ� ����ϴ� ������ ����
	if (mh_socket != INVALID_SOCKET) closesocket(mh_socket);
	WSACleanup();		// ���� ���̺귯���� ����
}


void CFirstWinSocketClientDlg::OnBnClickedSendBtn()
{
	// ������ ����� �����̸鼭 ���� ����� �����ϸ� �������� ����
	if (m_is_connected == 2 && mh_socket != INVALID_SOCKET) {
		int num = GetDlgItemInt(IDC_NUM_EDIT);		// �Է��� �������� ����
		// mh_socket ������ ����Ͽ� ������ �������� ����
		send(mh_socket, (char*)&num, sizeof(int), 0);
		// ���� ����� ����Ʈ �ڽ��� ������
		CString str;
		str.Format(L"������ ������(%d)�� �����߽��ϴ�.", num);
		AddEventString(str);
	}
}

void CFirstWinSocketClientDlg::AddEventString(const wchar_t* ap_string)
{
	int index = m_event_list.InsertString(-1, ap_string);
	m_event_list.SetCurSel(index);
}

/*
	socket -> connect -> send -> closesocket
*/

void CFirstWinSocketClientDlg::OnBnClickedConnectBtn()
{
	if (mh_socket == INVALID_SOCKET) {			// ���� ���� ���� üũ
		sockaddr_in addr_data = { AF_INET, htons(1900), };
		addr_data.sin_addr.s_addr = inet_addr(ipconfig);			// ������ ���� IP

		mh_socket = socket(AF_INET, SOCK_STREAM, 0);		// ������ �����ؼ� �������� ������ ���� ����
		// ���� ���ӿ� ����ϴ� connect �Լ��� ������ ������ �ְų� ��Ʈ��ũ�� ������ ������
		// �ִ� 28�ʰ� '���� ����' ���°� �� �� �ֱ� ������ ������ üũ���ִ� �񵿱� ������ �Ѵ�.
		// mh_socket �� FD_CONNECT �̺�Ʈ�� �߻��ϸ� ���� ��ȭ ���ڿ� 26001�� �޽����� �߻���Ŵ
		WSAAsyncSelect(mh_socket, m_hWnd, 26001, FD_CONNECT);
		// ������ ������ �õ�
		connect(mh_socket, (sockaddr*)&addr_data, sizeof(addr_data));
		m_is_connected = 1;			// ���� �õ������� ���¸� ����
		AddEventString(L"������ ������ �õ��մϴ�.");
	}
	else {
		// ������ �õ����̰ų� ������ �� ���¶�� ���� �����ش�
		if (m_is_connected == 2)	AddEventString(L"�̹� ���� �� �Դϴ�");
		else AddEventString(L"������ ������ �õ��ϰ� �ֽ��ϴ�. ��ٷ��ּ���...");
	}
}

void CFirstWinSocketClientDlg::OnBnClickedDisconnectBtn()
{
	// ������ ������� ���� �� ������ �����ϴ� �۾�
	if (mh_socket != INVALID_SOCKET) {
		m_is_connected = 0;		// ���� ���� ���·� ����
		closesocket(mh_socket);		// ����� ���� ����
		mh_socket = INVALID_SOCKET;		// ���� ���� �ʱ�ȭ
		AddEventString(L"������ ������ �����߽��ϴ�.");
	}
	else AddEventString(L"������ ����Ǿ� ���� �ʽ��ϴ�.");
}

// 26001
afx_msg LRESULT CFirstWinSocketClientDlg::OnConnected(WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(lParam)) {		// ������Ʈ�� �������� �������
		closesocket(mh_socket);			// ������ ������ ���� ����
		mh_socket = INVALID_SOCKET;		// ���� �ʱ�ȭ
		AddEventString(L"������ �������� ���߽��ϴ�.");
		m_is_connected = 0;			// ���� ���� ���·� ����
	}
	else {		// ���� ����
		// mh_socket���� üũ�ؾ��� ������ 2����
		// 1. �����Ͱ� ���ŵ� ���, 2. ������ ������ ������ ���
		// �ΰ��� ������ �񵿱�� �����Ͽ� ��ٸ��� �ʰ� �߻��ϸ� 26002�� �޽����� �߻���Ű���� ����
		WSAAsyncSelect(mh_socket, m_hWnd, 26002, FD_READ | FD_CLOSE);		// mh_socket�� �ش� �޽����� ������ m_hWndâ���� 26002�޽��� ������
		AddEventString(L"������ �����߽��ϴ�.");
		m_is_connected = 2;			// ���� ���·� ����
	}

	return 1;
}

// 26002
afx_msg LRESULT CFirstWinSocketClientDlg::OnSocketMessage(WPARAM wParam, LPARAM lParam)
{
	if (LOWORD(lParam) == FD_READ) {		// ������ ���� ��
		// NULL
	}
	else if (LOWORD(lParam) == FD_CLOSE) {		// FD_CLOSE ������ �����Ŵ
		closesocket(mh_socket);					// ����� ���� ����
		mh_socket = INVALID_SOCKET;		// ���� ���� �ʱ�ȭ
		AddEventString(L"�������� ������ �����߽��ϴ�.");
		m_is_connected = 0;			// ���� ���� ���·� ����
	}
	return 1;
}


void CFirstWinSocketClientDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}
