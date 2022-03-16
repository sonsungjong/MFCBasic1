// Win32SockServer.cpp : Defines the entry point for the application.
//

#include "pch.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "framework.h"
#include "Win32SockServer.h"

// 소켓 함수를 사용하기 위한 헤더파일
#include <WinSock2.h>
#include <WS2tcpip.h>			// InetPton 함수 사용을 위해
// 소켓 함수를 사용하기 위한 라이브러리 파일
#pragma comment(lib, "WS2_32.lib")

// 클라이언트의 접속을 처리하기 위한 소켓 핸들
SOCKET gh_listen_socket = INVALID_SOCKET;					// 접속용
// 클라이언트와 통신을 하기 위한 소켓 핸들
SOCKET gh_client_socket = INVALID_SOCKET;					// 통신용

// 테스트용 거대자료
char* gp_test_data;

void StartListenService(const TCHAR* ap_ip_address, int a_port, HWND ah_wnd)
{
	// 소켓2.2 시작
	WSADATA temp;
	WSAStartup(0x0202, &temp);

	// AF_INET 주소체계의 TCP 소켓 생성
	gh_listen_socket = socket(AF_INET, SOCK_STREAM, 0);

	// 포트번호
	sockaddr_in addr_data = { AF_INET, htons(a_port), };
	// IP주소 설정
	InetPton(AF_INET, ap_ip_address, &addr_data.sin_addr.s_addr);

	// IP와 PORT번호를 사용하여 소켓을 네트워크 시스템에 연결한다.
	bind(gh_listen_socket, (sockaddr*)&addr_data, sizeof(addr_data));
	// 접속 처리단위를 설정한다. (순차처리)
	listen(gh_listen_socket, 5);
	// 사용자가 FD_ACCEPT를 시도했을 때 현재(서버) 대화상자에 25001번 메시지가 발생하도록 비동기 설정
	WSAAsyncSelect(gh_listen_socket, ah_wnd, 25001, FD_ACCEPT);
	// 대기 시간 중 응답없음을 피하기 위해서 비동기로 설정
	// 이제 25001 메시지가 들어오는 것에 대해서 처리하면 됨
}

void ProcessAccept(HWND ah_wnd)
{
	// 접속을 시도한 소켓(클라이언트와 통신할 소켓)의 주소를 저장할 변수
	sockaddr_in addr_data;
	// 자신의 사용할 주소 저장 변수의 크기를 계산
	int addr_data_size = sizeof(addr_data);

	// 클라이언트 소켓의 접속을 허가
	// 복제 소켓이 생성되어 핸들의 값이 반환된다. (h_socket에 저장)
	// addr_data 변수에는 접속시도한 소켓의 IP가 정수형태으로 저장된다.
	SOCKET h_socket = accept(gh_listen_socket, (sockaddr*)&addr_data, &addr_data_size);

	if (gh_client_socket == INVALID_SOCKET) {			// 접속한 이력이 없으면 (한개의 클라이언트만 사용)
		gh_client_socket = h_socket;

		// 클라이언트가 보내거나 끊으면 서버는 25002 메시지를 발생시킴
		WSAAsyncSelect(gh_client_socket, ah_wnd, 25002, FD_READ | FD_CLOSE);

		// 테스트용 보내기
		int temp_size = 200000, read_size = 4;
		setsockopt(gh_client_socket, SOL_SOCKET, SO_SNDBUF, (char*)&temp_size, 4);
		setsockopt(gh_client_socket, SOL_SOCKET, SO_RCVBUF, (char*)&temp_size, 4);
		WSAAsyncSelect(gh_client_socket, ah_wnd, 25002, FD_READ | FD_CLOSE);
		*(int*)gp_test_data = 100000;
		send(gh_client_socket, gp_test_data, 100000, 0);					// 바이트의 크기를 전송
	}
	else {			// 이미 다른 클라이언트가 연결중이면
		closesocket(h_socket);
	}
}

// 서버가 큰 데이터를 수신할때 예외처리
int ReceiveData(SOCKET ah_socket, char* ap_data, int a_size)
{
	int total_size = 0, read_size, retry_count = 0;
	// a_size 크기만큼 모두 수신될때까지 반복시도한다.
	while (total_size < a_size)
	{
		// 남은 크기만큼 수신을 시도한다.
		read_size = recv(ah_socket, ap_data + total_size, a_size - total_size, 0);
		if (read_size == SOCKET_ERROR || read_size == 0) {			// 읽기 실패시
			Sleep(10);						// 0.01초 대기
			retry_count++;
			if (retry_count > 300) { break; }				// 300회까지 재시도
		}
		else {
			retry_count = 0;					// 재시도 횟수를 초기화
			total_size += read_size;				// 수신된 데이터의 크기를 합산
		}
	}
	return total_size;				// 전체 수신한 바이트를 출력한다.
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) {					// WM_CLOSE 처리 후에 들어오는 메시지
		// 사용하던 소켓을 닫는다.
		closesocket(gh_listen_socket);
		if (gh_client_socket != INVALID_SOCKET) { closesocket(gh_client_socket); }
		
		// 테스트용 삭제
		delete[] gp_test_data;
		
		// 자신의 메시지 큐에 WM_QUIT 메시지를 넣는다
		PostQuitMessage(0);
	}
	else if (uMsg == WM_CREATE) {
		gp_test_data = new char[100000];
		// 리슨 서비스를 시작한다.
		StartListenService(_T("127.0.0.1"), 19000, hWnd);
	}
	else if (uMsg == 25001) {			// FD_ACCEPT에 대한 발생메시지
		ProcessAccept(hWnd);
	}
	else if (uMsg == 25002) {			// FD_READ 혹은 FD_CLOSE에 대한 발생메시지
		if (WSAGETSELECTEVENT(lParam) == FD_READ) {			// FD_READ 일 경우 (클라이언트가 메시지를 보냄)
			int data;
			//recv(gh_client_socket, (char*)&data, 4, 0);				// 4byte만큼 읽어서 data에 저장
			ReceiveData(gh_client_socket, (char*)&data, 4);
		}
		else {			// FD_CLOSE 일 경우 (클라이언트가 접속을 해제)
			closesocket(gh_client_socket);
			gh_client_socket = INVALID_SOCKET;
		}
	}

	// 개발자가 처리하지 않은 메시지들을 처리한다
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 윈도우 클래스 등록
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = _T("SjSockServer");
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);

	// 윈도우 생성
	HWND hWnd = CreateWindow(_T("SjSockServer"), _T("Win32 Socket Server"),
		WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}