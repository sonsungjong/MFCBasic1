
// FirstWinSocketServerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "FirstWinSocketServer.h"
#include "FirstWinSocketServerDlg.h"
#include "afxdialogex.h"
// Socket 관련 함수를 사용하기 위해 헤더파일과 라이브러리를 포함시킨다.
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
	WSAStartup(0x0202, &temp);		// 소켓 라이브러리를 사용 가능 상태로 만든다. (0x0202 == 2.2)
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
	WSACleanup();		// 소켓 라이브러리를 그만 사용하도록 설정한다.
}

// #define _WINSOCK_DEPRECATED_NO_WARNINGS		framework.h에

void CFirstWinSocketServerDlg::OnLbnSelchangeEventList()
{
	// TODO: Add your control notification handler code here

}

/*
	#include <WinSock2.h>
	#pragma comment(lib, "WS2_32.lib")

	WSADATA temp;
	WSAStartup(0x0202, &temp);		// 사용시작

	WSACleanup();		// 해제
*/


void CFirstWinSocketServerDlg::OnBnClickedWaitRecvBtn()
{
	// 소켓을 네트워크 장치에 바인딩하기 위해 정보를 저장할 변수
	// IP 주소 체계, 프로그램 식별 번호(포트번호)
	sockaddr_in addr_data = {AF_INET, htons(1900), };		// 네트워크 카드정보를 셋팅
	// IP 주소 설정
	addr_data.sin_addr.s_addr = inet_addr("192.168.0.60");		// 핸드폰 구매를 위한 정보작성
	
	// IPPROTO_TCP
	SOCKET h_listen_socket = socket(AF_INET, SOCK_STREAM, 0);	// socket : 핸드폰구매

	// addr_data에 설정된 정보를 사용하여 소켓을 네트워크 시스템에 연결
	bind(h_listen_socket, (sockaddr*)&addr_data, sizeof(addr_data));		// binb : 핸드폰 개통
	// 접속을 처리할 단위 설정, 클라이언트로 부터 접속을 받음
	listen(h_listen_socket, 1);		// listen : 핸드폰 발신전용 -> 수신설정

	CString str;
	int addr_data_size = sizeof(addr_data), temp, read_bytes;
	// 클라이언트 소켓의 접속을 허락한다. --복제 소켓 생성

	SOCKET h_client_socket = accept(h_listen_socket, (sockaddr*)&addr_data, &addr_data_size);		// accept : 전화를 받는 행위 (대표전화 + 실제받을 전화1개)
	while (1) {
		read_bytes = recv(h_client_socket, (char*)&temp, 4, 0);		// 일정시간동안 데이터를 받아 temp변수에 넣음. (4byte)
		if (read_bytes == 4) {		// 받은값이 4byte 라면
			str.Format(L"%d", temp);		// 정숫값을 문자열로 변환한다.
			AddEventString(str);				// 리스트 박스에 출력한다.
			break;
		}
	}
	closesocket(h_client_socket);		// 클라이언트와 통신하던 소켓을 제거한다. 전화끊음
	closesocket(h_listen_socket);		// 리슨 소켓을 제거한다.
}

/*
	socket -> bind -> listen -> accept -> recv -> closesocket
*/