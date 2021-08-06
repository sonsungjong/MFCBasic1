
// FirstWinSocketServerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "FirstWinSocketServer.h"
#include "FirstWinSocketServerDlg.h"
#include "afxdialogex.h"
// Socket ���� �Լ��� ����ϱ� ���� ������ϰ� ���̺귯���� ���Խ�Ų��.
/*
#include <WinSock2.h>
#include <WS2tcpip.h>		// InetPton �Լ� ����� ���� �߰�
#pragma comment(lib, "WS2_32.lib")
*/

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Ŭ���̾�Ʈ ���� �� ȣ��Ǵ� �Լ�
void MyServerSocket::AcceptUserProc(UserData* ap_user_data)
{
	CString str;
	str.Format(L"%s ���� ������ �����߽��ϴ�.", ap_user_data->ip_address);
	((CFirstWinSocketServerDlg*)mp_notify_wnd)->AddEventString(str);
}
// ���ŵ� �����͸� ó���ϴ� �Լ�
int MyServerSocket::ProcessNetMessage()
{
	// m_net_msg_id���� 1�̸� ä�� �����̹Ƿ� ����Ʈ �ڽ��� ���ڿ� ���
	if (m_net_msg_id == 1) {
		CString str;
		// ä�ñ� �տ� �ش� ������� IP�� �߰���
		str.Format(L"%s : %s", mp_net_user->ip_address, (wchar_t*)mp_net_body_data);
		// ���ڿ��� ����Ʈ �ڽ��� ���
		((CFirstWinSocketServerDlg*)mp_notify_wnd)->AddEventString(str);
	}
	return 1;
}
// Ŭ���̾�Ʈ ������ ������ ��쿡 ȣ��Ǵ� �Լ�
void MyServerSocket::CloseUserProc(UserData* ap_user_data, int a_error_flag)
{
	if (a_error_flag == 0) {			// ������ ������ 0
		CString str;
		str.Format(L"%s���� ������ �����߽��ϴ�.", ap_user_data->ip_address);
		((CFirstWinSocketServerDlg*)mp_notify_wnd)->AddEventString(str);
	}
}

// CFirstWinSocketServerDlg dialog
CFirstWinSocketServerDlg::CFirstWinSocketServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FIRSTWINSOCKETSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//WSADATA temp;
	//WSAStartup(0x0202, &temp);		// ���� ���̺귯���� ��� ���� ���·� �����. (0x0202 == 2.2)

	// mh_client_socket = INVALID_SOCKET;		// -1, 0xFFFFFFFF, ~0		�ϳ��� Ŭ���̾�Ʈ ����
	//for (int i = 0; i < MAX_USER_COUNT; i++) m_users[i].h_socket = INVALID_SOCKET;		// ��ü �ʱ�ȭ
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
	//ON_MESSAGE(25001, &CFirstWinSocketServerDlg::OnAcceptProc)
	//ON_MESSAGE(25002, &CFirstWinSocketServerDlg::OnSocketMessage)
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
	//sockaddr_in addr_data = { AF_INET, htons(1900), };		// ��Ʈ��ũ ī�������� ����
	// IP �ּ� ����
	//addr_data.sin_addr.s_addr = inet_addr(ipconfig);		// �ڵ��� ���Ÿ� ���� �����ۼ�

	// IPPROTO_TCP
	//mh_listen_socket = socket(AF_INET, SOCK_STREAM, 0);	// socket : �ڵ�������

	// addr_data�� ������ ������ ����Ͽ� ������ ��Ʈ��ũ �ý��ۿ� ����
	//bind(mh_listen_socket, (sockaddr*)&addr_data, sizeof(addr_data));		// binb : �ڵ��� ����
	// ������ ó���� ���� ����, Ŭ���̾�Ʈ�� ���� ������ ����
	//listen(mh_listen_socket, 1);		// listen : �ڵ��� �߽����� -> ���ż���

	// �񵿱� accept
	//WSAAsyncSelect(mh_listen_socket, m_hWnd, 25001, FD_ACCEPT);
	// mh_listen_socket�� ����ڰ� ������ �õ�(FD_ACCEPT)���� ��
	// ���� ��ȭ ����(m_hWnd)�� 25001�� �޽����� �߻��ϵ��� �񵿱⸦ �����Ѵ�.
	// �񵿱� Ȥ�� �����带 ���� accept�� �ϸ� �ȴ�.

	// Ŭ���̾�Ʈ�� ������ �� �ֵ��� ���� �۾��� ����
	m_server_socket.StartListenService(ipconfig, thisPort, this, 25001, 25002);

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
/*
int CFirstWinSocketServerDlg::ReceiveData(SOCKET ah_socket, char* ap_data, int a_size) {
	int read_size, total_size = 0, retry_count = 0;
	CString str;
	// a_size ũ�⸸ŭ �� ���ŵɶ����� �ݺ���Ų��.
	while (total_size < a_size) {
		// ���� ũ�⸦ ����
		read_size = recv(ah_socket, ap_data + total_size, a_size - total_size, 0);
		if (read_size == SOCKET_ERROR || read_size == 0) {		// �б� ����
			Sleep(10);			// 10ms ���
			retry_count++;		// ��õ� Ƚ�� ����
			if (retry_count > 300) break;			// 300ȸ ��õ� �Ŀ��� �����ϸ� �۾��ߴ�
		}
		else {		// �б� �Ϸ�
			retry_count = 0;		// ��õ� Ƚ�� �ʱ�ȭ
			total_size += read_size;		// ������ �������� ũ�⸦ �ջ�
			
			//str.Format(L"������ ���� �� : %d", read_size);		// ���� ����Ʈũ�� ���
			//AddEventString(str);
			
		}
	}
	return total_size;		// ��ü ������ ����Ʈũ�� ����
}
*/

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
	//closesocket(mh_listen_socket);		// ���� ������ �����Ѵ�.

	// Ŭ���̾�Ʈ�� ������ ���¶�� ��ſ� ���ϵ� ����
	//if (mh_client_socket != INVALID_SOCKET) closesocket(mh_client_socket);

	// ������ Ŭ���̾�Ʈ�� �ִٸ� ���� ������ ��� ����
	//UserData* p = m_users;
	//for (int i = 0; i < MAX_USER_COUNT; i++, p++) if (p->h_socket != INVALID_SOCKET) closesocket(p->h_socket);

	//WSACleanup();		// ���� ���̺귯���� �׸� ����ϵ��� �����Ѵ�.
}

// #define _WINSOCK_DEPRECATED_NO_WARNINGS		framework.h��

void CFirstWinSocketServerDlg::OnLbnSelchangeEventList()
{
	// TODO: Add your control notification handler code here

}

/*
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
	CString str;
	str.Format(L"%s ���� ������ ������ �õ��ϰ� �ֽ��ϴ�.", temp_ip_address);
	AddEventString(str);

	UserData* p = m_users;
	int i;
	for (i = 0; i < MAX_USER_COUNT; i++, p++)
	{
		if (p->h_socket == INVALID_SOCKET) {
			AddEventString(L"Ŭ���̾�Ʈ ������ �����߽��ϴ�.");
			p->h_socket = h_client_socket;
			wcscpy_s(p->ip_address, 16, temp_ip_address);
			WSAAsyncSelect(h_client_socket, m_hWnd, 25002, FD_READ | FD_CLOSE);
			break;
		}
	}

	if (i == MAX_USER_COUNT) {
		AddEventString(L"�ִ� ������ ���� �����߽��ϴ�. ���̻� ������ �� �����ϴ�.");
		closesocket(h_client_socket);			// Ŭ���̾�Ʈ�� ����Ϸ��� ���� ������ �����Ѵ�.
	}

	
	//if (mh_client_socket != INVALID_SOCKET) {		// �������� ���
	//	AddEventString(L"�̹� ������ Ŭ���̾�Ʈ�� �־ ������ �ź��Ͽ����ϴ�.");
	//	closesocket(h_client_socket);		// Ŭ���̾�Ʈ�� ����Ϸ� ���� ������ ����
	//}
	//else {
	//	AddEventString(L"Ŭ���̾�Ʈ�� �����Ͽ����ϴ�.");
	//	// ���� ������ Ŭ���̾�Ʈ�� �ڵ� ���� ��� ������ �����ؼ� ������ ������Ŵ, �ش� �ڵ�� ���
	//	mh_client_socket = h_client_socket;
	//	// ���� ������ �����ϰ� �񵿱�� üũ�� �� mh_client_socket ���� üũ�ؾ��� ����2
	//	// 1. �����Ͱ� ���ŵ� ��� 2. Ŭ���̾�Ʈ�� ������ ������ ���
	//	// �ΰ��� ������ �񵿱�� �����Ͽ� ��Ȳ�� �߻��� ���� 25002�� �޽����� ��ȭ���ڿ� �߻��ϵ��� ����
	//	WSAAsyncSelect(mh_client_socket, m_hWnd, 25002, FD_READ | FD_CLOSE);		// ���ô� or�� ����Ͽ� �ѹ��� üũ�������. FD_READ | FD_CLOSE
	//}
	
	return 0;
}

// 25002�� �Լ� (������ �޽����� �����ϰų� Ŭ���̾�Ʈ�� �������ų�)
afx_msg LRESULT CFirstWinSocketServerDlg::OnSocketMessage(WPARAM wParam, LPARAM lParam)
{
	SOCKET h_socket = (SOCKET)wParam;		// ���� �����ڵ鰪�� ����
	// lParam �� ����16��Ʈ�� �� �޽���(25002)�� �߻���Ų �̺�Ʈ ������ ����Ǿ� ����
	if (LOWORD(lParam) == FD_READ) {		// ������ ���� ��

		WSAAsyncSelect(h_socket, m_hWnd, 25002, FD_CLOSE);

		char key, message_id;
		// ù ����Ʈ�� �о �������� Ű ���� ���Դ��� Ȯ���Ѵ�.
		recv(h_socket, &key, 1, 0);
		if (key == 27) {		// 27�� ��쿡�� ó��
			//Message ID�� �д´�.
			recv(h_socket, &message_id, 1, 0);

			unsigned short body_size;
			// ���� ������ �� 2byte�� ���� �о� Body �������� ũ�⸦ �˾Ƴ���.
			recv(h_socket, (char*)&body_size, 2, 0);
			// Body �����͸� �����ϱ� ���� �޸𸮸� �Ҵ�
			char* p_recv_data = new char[body_size];
			// ���ŵ� Body �����͸� �д´�.
			//int read_bytes = recv(mh_client_socket, p_recv_data, body_size, 0);
			int read_bytes = ReceiveData(h_socket, p_recv_data, body_size);			// ���� ������ũ��� ������ ������ũ�Ⱑ �ٸ� �� ������ �ݺ���
			
			//CString readData;
			//readData.Format(L"������ ���� ũ�� : %d", read_bytes);
			//AddEventString(readData);
			

			// message_id���� 1�̸� ä�������� ����, -> ����Ʈ �ڽ��� ���ڿ� �߰�
			if (message_id == 1) {
				// �޽��� ��ó�� Ȯ���ϱ����� �޽��� �տ� IP�� �ٿ��� ���
				UserData* p = m_users;
				// �ڽ��� �����ϰ� �ִ� Ŭ���̾�Ʈ �߿��� � Ŭ���̾�Ʈ�� �� �޽����� �����ؾ����� Ȯ���ϱ� ���� ����� ����� Ž��
				for (int i = 0; i < MAX_USER_COUNT; i++, p++)
				{
					// h_socket�� ����� ���ϰ� ��ġ�ϴ� ������ ���� �޽����� ���� Ŭ���̾�Ʈ��.
					if (p->h_socket == h_socket) break;
				}
				
				CString str;
				// ä�ñ� �տ� �ش� ������� IP�� ���
				str.Format(L"%s : %s", p->ip_address, (wchar_t*)p_recv_data);
				AddEventString(str);
			}
			// Body������ ���ſ� ����� �޸𸮸� ����
			delete[] p_recv_data;
			// �񵿱� �������� FD_READ�� �ٽ� ���Խ�Ų��.
			WSAAsyncSelect(h_socket, m_hWnd, 25002, FD_READ | FD_CLOSE);
		}
	}
	else if (LOWORD(lParam) == FD_CLOSE){		// ����� ����
		UserData* p = m_users;
		for (int i = 0; i < MAX_USER_COUNT; i++, p++)
		{
			if (p->h_socket == h_socket) {
				CString str;
				str.Format(L"%s���� ������ �����Ͽ����ϴ�.", p->ip_address);
				AddEventString(str);
				p->h_socket = INVALID_SOCKET;		// ������ ���������� ����
				break;
			}
		}
		closesocket(h_socket);		// Ŭ���̾�Ʈ�� ����ϴ� ���� ����
		
		//mh_client_socket = INVALID_SOCKET;		// ������ ���������� ���� (�ߺ����� ����)
		//AddEventString(L"Ŭ���̾�Ʈ�� ������ �����߽��ϴ�.");
		
	}
	return 0;
}
*/

void CFirstWinSocketServerDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}

LRESULT CFirstWinSocketServerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	// ���� ��ü�� �޽����� ó���� �� �ֵ��� �Լ��� ȣ��
	m_server_socket.MessageProc(message, wParam, lParam);

	return CDialogEx::WindowProc(message, wParam, lParam);
}

/*
	#include <WinSock2.h>
	#pragma comment(lib, "WS2_32.lib")

	WSADATA temp;
	WSAStartup(0x0202, &temp);		// ������

	WSACleanup();		// ����

	socket -> bind -> listen -> accept -> recv -> closesocket
*/