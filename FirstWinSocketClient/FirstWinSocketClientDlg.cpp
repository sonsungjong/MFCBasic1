
// FirstWinSocketClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "FirstWinSocketClient.h"
#include "FirstWinSocketClientDlg.h"
#include "afxdialogex.h"

// 소켓 라이브러리와 헤더파일 추가
/*
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")
*/
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 서버에 접속한 결과가 나오면 호출되는 함수
void MyClientSocket::ConnectedProcess() {
	if (m_is_connected) ((CFirstWinSocketClientDlg*)mp_notify_wnd)->AddEventString(L"서버에 접속했습니다.");
	else ((CFirstWinSocketClientDlg*)mp_notify_wnd)->AddEventString(L"서버에 접속하지 못했습니다.");
}

// 수신된 데이터를 어떻게 처리할 것인지 정의하는 함수
int MyClientSocket::ProcessNetMessage()
{
	// 여기에 수신된 데이터를 처리
	// m_net_msg_id == 1이면 채팅정보. 리스트 박스에 문자열 추가처리
	if (m_net_msg_id == 1) {
		// 수신된 문자열을 리스트 박스에 출력
		((CFirstWinSocketClientDlg*)mp_notify_wnd)->AddEventString((TCHAR*)mp_net_body_data);
	}

	return 1;
}

// 접속이 해제된 경우에 호출되는 함수
void MyClientSocket::ClosedProcess(int a_error_flag) {
	if (!a_error_flag) ((CFirstWinSocketClientDlg*)mp_notify_wnd)->AddEventString(L"서버에서 접속을 해제했습니다.");
}

// CFirstWinSocketClientDlg dialog



CFirstWinSocketClientDlg::CFirstWinSocketClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FIRSTWINSOCKETCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//WSADATA temp;
	//WSAStartup(0x0202, &temp);			// 소켓 라이브러리 사용 가능 상태로 만들기

	//mh_socket = INVALID_SOCKET;		// 소켓 핸들 초기화 (-1 or 0xFFFFFFFF)
	//m_is_connected = 0;						// 접속 상태 초기화
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
	// 서버와 접속 상태라면 접속에 사용하던 소켓을 제거
	//if (mh_socket != INVALID_SOCKET) closesocket(mh_socket);
	//WSACleanup();		// 소켓 라이브러리를 중지
}


void CFirstWinSocketClientDlg::OnBnClickedSendBtn()
{
	// 서버와 연결된 상태이면서 소켓 사용이 가능하면 정수값을 전송
	if(m_client_socket.IsConnect()) {
		CString str;
		// EditControl에서 문자열을 얻는다.
		GetDlgItemText(IDC_CHAT_EDIT, str);
		int len = str.GetLength();
		// 서버로 채팅 문자열을 전송한다.
		if (len > 0) {				// 공백문자면 전송안함
			// 서버로 전송
			m_client_socket.SendFrameData(1, (const wchar_t*)str, (len + 1) * 2);
			// 입력한 문자열을 제거
			SetDlgItemText(IDC_CHAT_EDIT, _T(""));
			// 전송 결과를 리스트 박스에 보여줌
			AddEventString(L"서버로 ("+str+L")을 전송했습니다.");
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
	if (!m_client_socket.IsConnect()) {			// 소켓 생성 여부 체크
		//  지정한 ip와 port를 사용해서 서버에 접속 시도
		m_client_socket.ConnectToServer(IP, PORT, this, 26001, 26002);
		AddEventString(L"서버에 접속을 시도합니다.");
	}
	else {
		// 접속을 시도중이거나 접속이 된 상태라는 것을 보여준다
		AddEventString(L"서버에 접속을 시도하고 있거나 접속된 상태입니다.");
	}
}

void CFirstWinSocketClientDlg::OnBnClickedDisconnectBtn()
{
	// 소켓이 만들어져 있을 때 소켓을 제거하는 작업
	if (m_client_socket.IsConnect()) {
		m_client_socket.CloseSocket();
		AddEventString(L"서버와 접속을 해제했습니다.");
	}
	else AddEventString(L"서버와 연결되어 있지 않습니다.");
}

/*
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
*/

void CFirstWinSocketClientDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	// 전송
	OnBnClickedSendBtn();

	//CDialogEx::OnOK();
}


void CFirstWinSocketClientDlg::OnBnClickedBigdataBtn()
{
	// TODO: Add your control notification handler code here
	if (m_client_socket.IsConnect()) {
		int send_data_size = 35 * 1024;				// 초과한 데이터를 전송 35kb
		char* p_send_data = new char[send_data_size];
		m_client_socket.SendFrameData(2, p_send_data, send_data_size);		// 서버로 문자열 전송
		delete[] p_send_data;		// 테스트에 사용한 메모리 해제
	}
}

// 메시지 발생 시 호출되는 함수
LRESULT CFirstWinSocketClientDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	// 소켓 객체가 메시지를 처리할 수 있도록 함수를 호출(26001, 26002)
	m_client_socket.MessageProc(message, wParam, lParam);

	return CDialogEx::WindowProc(message, wParam, lParam);
}
