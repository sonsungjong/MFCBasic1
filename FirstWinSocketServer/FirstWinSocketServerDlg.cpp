
// FirstWinSocketServerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "FirstWinSocketServer.h"
#include "FirstWinSocketServerDlg.h"
#include "afxdialogex.h"
// Socket 관련 함수를 사용하기 위해 헤더파일과 라이브러리를 포함시킨다.
#include <WinSock2.h>
#include <WS2tcpip.h>		// InetPton 함수 사용을 위해 추가
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
	WSAStartup(0x0202, &temp);		// 소켓 라이브러리를 사용 가능 상태로 만든다. (0x0202 == 2.2)

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
	// 소켓을 네트워크 장치에 바인딩하기 위해 정보를 저장할 변수
	// IP 주소 체계, 프로그램 식별 번호(포트번호)
	sockaddr_in addr_data = { AF_INET, htons(1900), };		// 네트워크 카드정보를 셋팅
	// IP 주소 설정
	addr_data.sin_addr.s_addr = inet_addr(ipconfig);		// 핸드폰 구매를 위한 정보작성

	// IPPROTO_TCP
	mh_listen_socket = socket(AF_INET, SOCK_STREAM, 0);	// socket : 핸드폰구매

	// addr_data에 설정된 정보를 사용하여 소켓을 네트워크 시스템에 연결
	bind(mh_listen_socket, (sockaddr*)&addr_data, sizeof(addr_data));		// binb : 핸드폰 개통
	// 접속을 처리할 단위 설정, 클라이언트로 부터 접속을 받음
	listen(mh_listen_socket, 1);		// listen : 핸드폰 발신전용 -> 수신설정

	// 비동기 accept
	WSAAsyncSelect(mh_listen_socket, m_hWnd, 25001, FD_ACCEPT);
	// mh_listen_socket에 사용자가 접속을 시도(FD_ACCEPT)했을 때
	// 현재 대화 상자(m_hWnd)에 25001번 메시지가 발생하도록 비동기를 설정한다.
	// 비동기 혹은 쓰레드를 통해 accept를 하면 된다.

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
	closesocket(mh_listen_socket);		// 리슨 소켓을 제거한다.

	// 클라이언트가 접속한 상태라면 통신용 소켓도 제거
	if (mh_client_socket != INVALID_SOCKET)
		closesocket(mh_client_socket);

	WSACleanup();		// 소켓 라이브러리를 그만 사용하도록 설정한다.
}

// #define _WINSOCK_DEPRECATED_NO_WARNINGS		framework.h에

void CFirstWinSocketServerDlg::OnLbnSelchangeEventList()
{
	// TODO: Add your control notification handler code here

}

// 25001번 함수
afx_msg LRESULT CFirstWinSocketServerDlg::OnAcceptProc(WPARAM wParam, LPARAM lParam)
{
	// 접속한 클라이언트의 정보를 저장할 구조체를 초기화
	sockaddr_in addr_data = { 0, };
	// 구조체 크기 저장
	int data_size = sizeof(addr_data);
	// 클라이언트 소켓의 접속을 허락 (복제 소켓 생성)
	SOCKET h_client_socket = accept(mh_listen_socket, (sockaddr*)&addr_data, &data_size);

	wchar_t temp_ip_address[32];
	// addr_data 변수에 정수 형태로 저장되있는 IP 주소를 문자열 형태로 변경해서 temp_ip_address 에 저장
	InetNtop(AF_INET, &addr_data.sin_addr, temp_ip_address, 32);		// 클라이언트의 IP보관
	AddEventString(temp_ip_address + CString(L" 에서 서버에 접속을 시도하고 있습니다."));

	CString str;
	if (mh_client_socket != INVALID_SOCKET) {		// 접속중일 경우
		AddEventString(L"이미 접속한 클라이언트가 있어서 접속을 거부하였습니다.");
		closesocket(h_client_socket);		// 클라이언트와 통신하려 만든 소켓을 제거
	}
	else {
		AddEventString(L"클라이언트가 접속하였습니다.");
		// 현재 접속한 클라이언트의 핸들 값을 멤버 변수에 보관해서 접속을 유지시킴, 해당 핸들로 통신
		mh_client_socket = h_client_socket;
		// 무한 루프를 제거하고 비동기로 체크할 때 mh_client_socket 에서 체크해야할 사항2
		// 1. 데이터가 수신된 경우 2. 클라이언트가 접속을 해제한 경우
		// 두가지 사항을 비동기로 설정하여 상황이 발생할 때만 25002번 메시지가 대화상자에 발생하도록 셋팅
		WSAAsyncSelect(mh_client_socket, m_hWnd, 25002, FD_READ | FD_CLOSE);		// 감시는 or를 사용하여 한번에 체크해줘야함. FD_READ | FD_CLOSE

	}
	return 0;
}

// 25002번 함수 (서버가 메시지를 수신하거나 클라이언트가 끊어지거나)
afx_msg LRESULT CFirstWinSocketServerDlg::OnSocketMessage(WPARAM wParam, LPARAM lParam)
{
	// lParam 의 하위비트에 이 메시지(25002)를 발생시킨 이벤트 종류가 저장되어 있음
	if (LOWORD(lParam) == FD_READ) {		// 데이터 수신 시
		unsigned short body_size;
		recv(mh_client_socket, (char*)&body_size, 2, 0);			// 수신받은 데이터에서 2byte값을 얻는다.

		char* p_recv_data = new char[body_size];
		recv(mh_client_socket, p_recv_data, body_size, 0);		// 수신받은 body_size 바이트값을 얻는다.

		AddEventString((wchar_t*)p_recv_data);		// 리스트 박스에 출력
		delete[] p_recv_data;
	}
	else if (LOWORD(lParam) == FD_CLOSE){		// 상대편 종료
		closesocket(mh_client_socket);		// 클라이언트와 통신하던 소켓 제거
		mh_client_socket = INVALID_SOCKET;		// 소켓을 사용안함으로 설정 (중복제거 방지)
		AddEventString(L"클라이언트가 접속을 해제했습니다.");
	}

	return 0;
}

/*
	#include <WinSock2.h>
	#pragma comment(lib, "WS2_32.lib")

	WSADATA temp;
	WSAStartup(0x0202, &temp);		// 사용시작

	WSACleanup();		// 해제

	socket -> bind -> listen -> accept -> recv -> closesocket
*/

void CFirstWinSocketServerDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}
