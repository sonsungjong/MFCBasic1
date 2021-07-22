
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
	WSAStartup(0x0202, &temp);			// 소켓 라이브러리 사용 가능 상태로 만들기

	mh_socket = INVALID_SOCKET;		// 소켓 핸들 초기화 (-1 or 0xFFFFFFFF)
	m_is_connected = 0;						// 접속 상태 초기화
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
	// 서버와 접속 상태라면 접속에 사용하던 소켓을 제거
	if (mh_socket != INVALID_SOCKET) closesocket(mh_socket);
	WSACleanup();		// 소켓 라이브러리를 중지
}


void CFirstWinSocketClientDlg::OnBnClickedSendBtn()
{
	// 서버와 연결된 상태이면서 소켓 사용이 가능하면 정수값을 전송
	if (m_is_connected == 2 && mh_socket != INVALID_SOCKET) {
		int num = GetDlgItemInt(IDC_NUM_EDIT);		// 입력한 정수값을 얻음
		// mh_socket 소켓을 사용하여 서버로 정수값을 보냄
		send(mh_socket, (char*)&num, sizeof(int), 0);
		// 전송 결과를 리스트 박스에 보여줌
		CString str;
		str.Format(L"서버로 정수값(%d)을 전송했습니다.", num);
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
	if (mh_socket == INVALID_SOCKET) {			// 소켓 생성 여부 체크
		sockaddr_in addr_data = { AF_INET, htons(1900), };
		addr_data.sin_addr.s_addr = inet_addr(ipconfig);			// 접속할 서버 IP

		mh_socket = socket(AF_INET, SOCK_STREAM, 0);		// 서버에 접속해서 정수값을 전송할 소켓 생성
		// 서버 접속에 사용하는 connect 함수가 서버에 문제가 있거나 네트워크에 문제가 있으면
		// 최대 28초간 '응답 없음' 상태가 될 수 있기 때문에 접속을 체크해주는 비동기 설정을 한다.
		// mh_socket 에 FD_CONNECT 이벤트가 발생하면 현재 대화 상자에 26001번 메시지를 발생시킴
		WSAAsyncSelect(mh_socket, m_hWnd, 26001, FD_CONNECT);
		// 서버에 접속을 시도
		connect(mh_socket, (sockaddr*)&addr_data, sizeof(addr_data));
		m_is_connected = 1;			// 접속 시도중으로 상태를 변경
		AddEventString(L"서버에 접속을 시도합니다.");
	}
	else {
		// 접속을 시도중이거나 접속이 된 상태라는 것을 보여준다
		if (m_is_connected == 2)	AddEventString(L"이미 접속 중 입니다");
		else AddEventString(L"서버에 접속을 시도하고 있습니다. 기다려주세요...");
	}
}

void CFirstWinSocketClientDlg::OnBnClickedDisconnectBtn()
{
	// 소켓이 만들어져 있을 때 소켓을 제거하는 작업
	if (mh_socket != INVALID_SOCKET) {
		m_is_connected = 0;		// 접속 해제 상태로 변경
		closesocket(mh_socket);		// 종료된 소켓 제거
		mh_socket = INVALID_SOCKET;		// 소켓 변수 초기화
		AddEventString(L"서버와 접속을 해제했습니다.");
	}
	else AddEventString(L"서버와 연결되어 있지 않습니다.");
}

// 26001
afx_msg LRESULT CFirstWinSocketClientDlg::OnConnected(WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(lParam)) {		// 상위비트에 오류값이 들어있음
		closesocket(mh_socket);			// 접속을 실패한 소켓 제거
		mh_socket = INVALID_SOCKET;		// 변수 초기화
		AddEventString(L"서버에 접속하지 못했습니다.");
		m_is_connected = 0;			// 접속 해제 상태로 변경
	}
	else {		// 접속 성공
		// mh_socket에서 체크해야할 사항은 2가지
		// 1. 데이터가 수신된 경우, 2. 서버가 접속을 해제한 경우
		// 두가지 사항을 비동기로 설정하여 기다리지 않고 발생하면 26002번 메시지를 발생시키도록 셋팅
		WSAAsyncSelect(mh_socket, m_hWnd, 26002, FD_READ | FD_CLOSE);		// mh_socket에 해당 메시지가 들어오면 m_hWnd창으로 26002메시지 보내기
		AddEventString(L"서버에 접속했습니다.");
		m_is_connected = 2;			// 접속 상태로 변경
	}

	return 1;
}

// 26002
afx_msg LRESULT CFirstWinSocketClientDlg::OnSocketMessage(WPARAM wParam, LPARAM lParam)
{
	if (LOWORD(lParam) == FD_READ) {		// 데이터 수신 시
		// NULL
	}
	else if (LOWORD(lParam) == FD_CLOSE) {		// FD_CLOSE 서버가 종료시킴
		closesocket(mh_socket);					// 종료된 소켓 제거
		mh_socket = INVALID_SOCKET;		// 소켓 변수 초기화
		AddEventString(L"서버에서 접속을 해제했습니다.");
		m_is_connected = 0;			// 접속 해제 상태로 변경
	}
	return 1;
}


void CFirstWinSocketClientDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}
