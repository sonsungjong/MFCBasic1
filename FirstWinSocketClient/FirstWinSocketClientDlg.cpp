
// FirstWinSocketClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "FirstWinSocketClient.h"
#include "FirstWinSocketClientDlg.h"
#include "afxdialogex.h"

// ���� ���̺귯���� ������� �߰�
/*
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")
*/
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ������ ������ ����� ������ ȣ��Ǵ� �Լ�
void MyClientSocket::ConnectedProcess() {
	if (m_is_connected) ((CFirstWinSocketClientDlg*)mp_notify_wnd)->AddEventString(L"������ �����߽��ϴ�.");
	else ((CFirstWinSocketClientDlg*)mp_notify_wnd)->AddEventString(L"������ �������� ���߽��ϴ�.");
}

// ���ŵ� �����͸� ��� ó���� ������ �����ϴ� �Լ�
int MyClientSocket::ProcessNetMessage()
{
	// ���⿡ ���ŵ� �����͸� ó��
	// m_net_msg_id == 1�̸� ä������. ����Ʈ �ڽ��� ���ڿ� �߰�ó��
	if (m_net_msg_id == 1) {
		// ���ŵ� ���ڿ��� ����Ʈ �ڽ��� ���
		((CFirstWinSocketClientDlg*)mp_notify_wnd)->AddEventString((TCHAR*)mp_net_body_data);
	}

	return 1;
}

// ������ ������ ��쿡 ȣ��Ǵ� �Լ�
void MyClientSocket::ClosedProcess(int a_error_flag) {
	if (!a_error_flag) ((CFirstWinSocketClientDlg*)mp_notify_wnd)->AddEventString(L"�������� ������ �����߽��ϴ�.");
}

// CFirstWinSocketClientDlg dialog



CFirstWinSocketClientDlg::CFirstWinSocketClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FIRSTWINSOCKETCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//WSADATA temp;
	//WSAStartup(0x0202, &temp);			// ���� ���̺귯�� ��� ���� ���·� �����

	//mh_socket = INVALID_SOCKET;		// ���� �ڵ� �ʱ�ȭ (-1 or 0xFFFFFFFF)
	//m_is_connected = 0;						// ���� ���� �ʱ�ȭ
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
	//ON_MESSAGE(26001, &CFirstWinSocketClientDlg::OnConnected)
	//ON_MESSAGE(26002, &CFirstWinSocketClientDlg::OnSocketMessage)
	ON_BN_CLICKED(IDOK, &CFirstWinSocketClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BigData_Btn, &CFirstWinSocketClientDlg::OnBnClickedBigdataBtn)
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
	//if (mh_socket != INVALID_SOCKET) closesocket(mh_socket);
	//WSACleanup();		// ���� ���̺귯���� ����
}


void CFirstWinSocketClientDlg::OnBnClickedSendBtn()
{
	// ������ ����� �����̸鼭 ���� ����� �����ϸ� �������� ����
	if(m_client_socket.IsConnect()) {
		CString str;
		// EditControl���� ���ڿ��� ��´�.
		GetDlgItemText(IDC_CHAT_EDIT, str);
		int len = str.GetLength();
		// ������ ä�� ���ڿ��� �����Ѵ�.
		if (len > 0) {				// ���鹮�ڸ� ���۾���
			// ������ ����
			m_client_socket.SendFrameData(1, (const wchar_t*)str, (len + 1) * 2);
			// �Է��� ���ڿ��� ����
			SetDlgItemText(IDC_CHAT_EDIT, _T(""));
			// ���� ����� ����Ʈ �ڽ��� ������
			AddEventString(L"������ ("+str+L")�� �����߽��ϴ�.");
		}
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
	if (!m_client_socket.IsConnect()) {			// ���� ���� ���� üũ
		//  ������ ip�� port�� ����ؼ� ������ ���� �õ�
		m_client_socket.ConnectToServer(IP, PORT, this, 26001, 26002);
		AddEventString(L"������ ������ �õ��մϴ�.");
	}
	else {
		// ������ �õ����̰ų� ������ �� ���¶�� ���� �����ش�
		AddEventString(L"������ ������ �õ��ϰ� �ְų� ���ӵ� �����Դϴ�.");
	}
}

void CFirstWinSocketClientDlg::OnBnClickedDisconnectBtn()
{
	// ������ ������� ���� �� ������ �����ϴ� �۾�
	if (m_client_socket.IsConnect()) {
		m_client_socket.CloseSocket();
		AddEventString(L"������ ������ �����߽��ϴ�.");
	}
	else AddEventString(L"������ ����Ǿ� ���� �ʽ��ϴ�.");
}

/*
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
*/

void CFirstWinSocketClientDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	// ����
	OnBnClickedSendBtn();

	//CDialogEx::OnOK();
}


void CFirstWinSocketClientDlg::OnBnClickedBigdataBtn()
{
	// TODO: Add your control notification handler code here
	if (m_client_socket.IsConnect()) {
		int send_data_size = 35 * 1024;				// �ʰ��� �����͸� ���� 35kb
		char* p_send_data = new char[send_data_size];
		m_client_socket.SendFrameData(2, p_send_data, send_data_size);		// ������ ���ڿ� ����
		delete[] p_send_data;		// �׽�Ʈ�� ����� �޸� ����
	}
}

// �޽��� �߻� �� ȣ��Ǵ� �Լ�
LRESULT CFirstWinSocketClientDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	// ���� ��ü�� �޽����� ó���� �� �ֵ��� �Լ��� ȣ��(26001, 26002)
	m_client_socket.MessageProc(message, wParam, lParam);

	return CDialogEx::WindowProc(message, wParam, lParam);
}
