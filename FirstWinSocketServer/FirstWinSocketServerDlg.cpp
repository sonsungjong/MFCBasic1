
// FirstWinSocketServerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "FirstWinSocketServer.h"
#include "FirstWinSocketServerDlg.h"
#include "afxdialogex.h"
// Socket 관련 함수를 사용하기 위해 헤더파일과 라이브러리를 포함시킨다.
/*
#include <WinSock2.h>
#include <WS2tcpip.h>		// InetPton 함수 사용을 위해 추가
#pragma comment(lib, "WS2_32.lib")
*/

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 클라이언트 접속 시 호출되는 함수
void MyServerSocket::AcceptUserProc(UserData* ap_user_data)
{
	CString str;
	str.Format(L"%s 에서 서버에 접속했습니다.", ap_user_data->ip_address);
	((CFirstWinSocketServerDlg*)mp_notify_wnd)->AddEventString(str);
}
// 수신된 데이터를 처리하는 함수
int MyServerSocket::ProcessNetMessage()
{
	// m_net_msg_id값이 1이면 채팅 정보이므로 리스트 박스에 문자열 출력
	if (m_net_msg_id == 1) {
		CString str;
		// 채팅글 앞에 해당 사용자의 IP를 추가함
		str.Format(L"%s : %s", mp_net_user->ip_address, (wchar_t*)mp_net_body_data);
		// 문자열을 리스트 박스에 출력
		((CFirstWinSocketServerDlg*)mp_notify_wnd)->AddEventString(str);
	}
	return 1;
}
// 클라이언트 접속이 해제된 경우에 호출되는 함수
void MyServerSocket::CloseUserProc(UserData* ap_user_data, int a_error_flag)
{
	if (a_error_flag == 0) {			// 에러가 없을때 0
		CString str;
		str.Format(L"%s에서 접속을 해제했습니다.", ap_user_data->ip_address);
		((CFirstWinSocketServerDlg*)mp_notify_wnd)->AddEventString(str);
	}
}

// CFirstWinSocketServerDlg dialog
CFirstWinSocketServerDlg::CFirstWinSocketServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FIRSTWINSOCKETSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//WSADATA temp;
	//WSAStartup(0x0202, &temp);		// 소켓 라이브러리를 사용 가능 상태로 만든다. (0x0202 == 2.2)

	// mh_client_socket = INVALID_SOCKET;		// -1, 0xFFFFFFFF, ~0		하나의 클라이언트 전용
	//for (int i = 0; i < MAX_USER_COUNT; i++) m_users[i].h_socket = INVALID_SOCKET;		// 전체 초기화
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
	// 소켓을 네트워크 장치에 바인딩하기 위해 정보를 저장할 변수
	// IP 주소 체계, 프로그램 식별 번호(포트번호)
	//sockaddr_in addr_data = { AF_INET, htons(1900), };		// 네트워크 카드정보를 셋팅
	// IP 주소 설정
	//addr_data.sin_addr.s_addr = inet_addr(ipconfig);		// 핸드폰 구매를 위한 정보작성

	// IPPROTO_TCP
	//mh_listen_socket = socket(AF_INET, SOCK_STREAM, 0);	// socket : 핸드폰구매

	// addr_data에 설정된 정보를 사용하여 소켓을 네트워크 시스템에 연결
	//bind(mh_listen_socket, (sockaddr*)&addr_data, sizeof(addr_data));		// binb : 핸드폰 개통
	// 접속을 처리할 단위 설정, 클라이언트로 부터 접속을 받음
	//listen(mh_listen_socket, 1);		// listen : 핸드폰 발신전용 -> 수신설정

	// 비동기 accept
	//WSAAsyncSelect(mh_listen_socket, m_hWnd, 25001, FD_ACCEPT);
	// mh_listen_socket에 사용자가 접속을 시도(FD_ACCEPT)했을 때
	// 현재 대화 상자(m_hWnd)에 25001번 메시지가 발생하도록 비동기를 설정한다.
	// 비동기 혹은 쓰레드를 통해 accept를 하면 된다.

	// 클라이언트가 접속할 수 있도록 리슨 작업을 실행
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
	// a_size 크기만큼 다 수신될때까지 반복시킨다.
	while (total_size < a_size) {
		// 남은 크기를 수신
		read_size = recv(ah_socket, ap_data + total_size, a_size - total_size, 0);
		if (read_size == SOCKET_ERROR || read_size == 0) {		// 읽기 실패
			Sleep(10);			// 10ms 대기
			retry_count++;		// 재시도 횟수 증가
			if (retry_count > 300) break;			// 300회 재시도 후에도 실패하면 작업중단
		}
		else {		// 읽기 완료
			retry_count = 0;		// 재시도 횟수 초기화
			total_size += read_size;		// 수신한 데이터의 크기를 합산
			
			//str.Format(L"데이터 수신 중 : %d", read_size);		// 수신 바이트크기 출력
			//AddEventString(str);
			
		}
	}
	return total_size;		// 전체 수신한 바이트크기 리턴
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
	//closesocket(mh_listen_socket);		// 리슨 소켓을 제거한다.

	// 클라이언트가 접속한 상태라면 통신용 소켓도 제거
	//if (mh_client_socket != INVALID_SOCKET) closesocket(mh_client_socket);

	// 접속한 클라이언트가 있다면 관련 소켓을 모두 제거
	//UserData* p = m_users;
	//for (int i = 0; i < MAX_USER_COUNT; i++, p++) if (p->h_socket != INVALID_SOCKET) closesocket(p->h_socket);

	//WSACleanup();		// 소켓 라이브러리를 그만 사용하도록 설정한다.
}

// #define _WINSOCK_DEPRECATED_NO_WARNINGS		framework.h에

void CFirstWinSocketServerDlg::OnLbnSelchangeEventList()
{
	// TODO: Add your control notification handler code here

}

/*
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
	CString str;
	str.Format(L"%s 에서 서버에 접속을 시도하고 있습니다.", temp_ip_address);
	AddEventString(str);

	UserData* p = m_users;
	int i;
	for (i = 0; i < MAX_USER_COUNT; i++, p++)
	{
		if (p->h_socket == INVALID_SOCKET) {
			AddEventString(L"클라이언트 접속을 승인했습니다.");
			p->h_socket = h_client_socket;
			wcscpy_s(p->ip_address, 16, temp_ip_address);
			WSAAsyncSelect(h_client_socket, m_hWnd, 25002, FD_READ | FD_CLOSE);
			break;
		}
	}

	if (i == MAX_USER_COUNT) {
		AddEventString(L"최대 접속자 수에 도달했습니다. 더이상 접속할 수 없습니다.");
		closesocket(h_client_socket);			// 클라이언트와 통신하려고 만든 소켓을 제거한다.
	}

	
	//if (mh_client_socket != INVALID_SOCKET) {		// 접속중일 경우
	//	AddEventString(L"이미 접속한 클라이언트가 있어서 접속을 거부하였습니다.");
	//	closesocket(h_client_socket);		// 클라이언트와 통신하려 만든 소켓을 제거
	//}
	//else {
	//	AddEventString(L"클라이언트가 접속하였습니다.");
	//	// 현재 접속한 클라이언트의 핸들 값을 멤버 변수에 보관해서 접속을 유지시킴, 해당 핸들로 통신
	//	mh_client_socket = h_client_socket;
	//	// 무한 루프를 제거하고 비동기로 체크할 때 mh_client_socket 에서 체크해야할 사항2
	//	// 1. 데이터가 수신된 경우 2. 클라이언트가 접속을 해제한 경우
	//	// 두가지 사항을 비동기로 설정하여 상황이 발생할 때만 25002번 메시지가 대화상자에 발생하도록 셋팅
	//	WSAAsyncSelect(mh_client_socket, m_hWnd, 25002, FD_READ | FD_CLOSE);		// 감시는 or를 사용하여 한번에 체크해줘야함. FD_READ | FD_CLOSE
	//}
	
	return 0;
}

// 25002번 함수 (서버가 메시지를 수신하거나 클라이언트가 끊어지거나)
afx_msg LRESULT CFirstWinSocketServerDlg::OnSocketMessage(WPARAM wParam, LPARAM lParam)
{
	SOCKET h_socket = (SOCKET)wParam;		// 받은 소켓핸들값을 저장
	// lParam 의 하위16비트에 이 메시지(25002)를 발생시킨 이벤트 종류가 저장되어 있음
	if (LOWORD(lParam) == FD_READ) {		// 데이터 수신 시

		WSAAsyncSelect(h_socket, m_hWnd, 25002, FD_CLOSE);

		char key, message_id;
		// 첫 바이트를 읽어서 정상적인 키 값이 들어왔는지 확인한다.
		recv(h_socket, &key, 1, 0);
		if (key == 27) {		// 27인 경우에만 처리
			//Message ID를 읽는다.
			recv(h_socket, &message_id, 1, 0);

			unsigned short body_size;
			// 수신 데이터 중 2byte를 먼저 읽어 Body 데이터의 크기를 알아낸다.
			recv(h_socket, (char*)&body_size, 2, 0);
			// Body 데이터를 수신하기 위해 메모리를 할당
			char* p_recv_data = new char[body_size];
			// 수신된 Body 데이터를 읽는다.
			//int read_bytes = recv(mh_client_socket, p_recv_data, body_size, 0);
			int read_bytes = ReceiveData(h_socket, p_recv_data, body_size);			// 읽은 데이터크기와 수신한 데이터크기가 다를 수 있으니 반복문
			
			//CString readData;
			//readData.Format(L"데이터 수신 크기 : %d", read_bytes);
			//AddEventString(readData);
			

			// message_id값이 1이면 채팅정보로 정의, -> 리스트 박스에 문자열 추가
			if (message_id == 1) {
				// 메시지 출처를 확인하기위해 메시지 앞에 IP를 붙여서 출력
				UserData* p = m_users;
				// 자신이 관리하고 있는 클라이언트 중에서 어떤 클라이언트가 이 메시지를 전송해쓴ㄴ지 확인하기 위해 사용자 목록을 탐색
				for (int i = 0; i < MAX_USER_COUNT; i++, p++)
				{
					// h_socket에 저장된 소켓과 일치하는 소켓이 현재 메시지를 보낸 클라이언트다.
					if (p->h_socket == h_socket) break;
				}
				
				CString str;
				// 채팅글 앞에 해당 사용자의 IP를 출력
				str.Format(L"%s : %s", p->ip_address, (wchar_t*)p_recv_data);
				AddEventString(str);
			}
			// Body데이터 수신에 사용한 메모리를 해제
			delete[] p_recv_data;
			// 비동기 설정에서 FD_READ를 다시 포함시킨다.
			WSAAsyncSelect(h_socket, m_hWnd, 25002, FD_READ | FD_CLOSE);
		}
	}
	else if (LOWORD(lParam) == FD_CLOSE){		// 상대편 종료
		UserData* p = m_users;
		for (int i = 0; i < MAX_USER_COUNT; i++, p++)
		{
			if (p->h_socket == h_socket) {
				CString str;
				str.Format(L"%s에서 접속을 해제하였습니다.", p->ip_address);
				AddEventString(str);
				p->h_socket = INVALID_SOCKET;		// 소켓을 사용안함으로 셋팅
				break;
			}
		}
		closesocket(h_socket);		// 클라이언트와 통신하던 소켓 제거
		
		//mh_client_socket = INVALID_SOCKET;		// 소켓을 사용안함으로 설정 (중복제거 방지)
		//AddEventString(L"클라이언트가 접속을 해제했습니다.");
		
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
	// 소켓 객체가 메시지를 처리할 수 있도록 함수를 호출
	m_server_socket.MessageProc(message, wParam, lParam);

	return CDialogEx::WindowProc(message, wParam, lParam);
}

/*
	#include <WinSock2.h>
	#pragma comment(lib, "WS2_32.lib")

	WSADATA temp;
	WSAStartup(0x0202, &temp);		// 사용시작

	WSACleanup();		// 해제

	socket -> bind -> listen -> accept -> recv -> closesocket
*/