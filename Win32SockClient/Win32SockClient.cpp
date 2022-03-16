// Win32SockClient.cpp : Defines the entry point for the application.
//

#include "pch.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "framework.h"
#include "Win32SockClient.h"

// 소켓 함수를 사용하기 위한 헤더
#include <WinSock2.h>
#include <WS2tcpip.h>						// InetPton 함수 사용을 위해 추가
// 소켓 함수를 사용하기 위한 라이브러리
#pragma comment(lib, "WS2_32.lib")

// 서버와 통신을 하기위한 소켓 핸들
SOCKET gh_socket = INVALID_SOCKET;

// 서버가 전송한 데이터를 수신할 때 사용할 함수
int ReceiveData(char* ap_data, int a_size)
{
	int total_size = 0, read_size, retry_count = 0;
	// a_size 크기만큼 다 수신될 때까지 반복한다.
	while (total_size < a_size) {
		// 남은 크기만큼 수신을 시도한다.
		read_size = recv(gh_socket, ap_data + total_size, a_size - total_size, 0);
		if (read_size == SOCKET_ERROR || read_size == 0) {				// 읽기 실패시
			Sleep(10);
			retry_count++;
			if (retry_count > 300) { break; }				// 300회 재시도
		}
		else {
			retry_count = 0;
			total_size += read_size;						// 수신된 데이터의 크기를 합산
		}
	}
	return total_size;				// 수신된 바이트 크기를 반환
}

// 서버에 접속을 시도
void ConnectToServer(const TCHAR* ap_ip_address, int a_port, HWND ah_wnd)
{
	// 소켓 라이브러리 사용
	WSADATA temp;
	WSAStartup(0x0202, &temp);

	// AF_INET 체계로 TCP소켓 생성
	gh_socket = socket(AF_INET, SOCK_STREAM, 0);

	// IP 주소, 프로그램 포트 번호
	sockaddr_in addr_data = { AF_INET, htons(a_port), };

	// ap_ip_address 주소를 사용하는 네트워크를 사용하도록 설정
	InetPton(AF_INET, ap_ip_address, &addr_data.sin_addr);

	// 서버 접속(FD_CONNECT)을 비동기 방식으로 처리
	// FD_CONNECT가 발생하면 ah_wnd 윈도우로 26001 메시지를 발생시킨다.
	WSAAsyncSelect(gh_socket, ah_wnd, 26001, FD_CONNECT);

	// 서버에 접속을 시도한다
	// 비동기 모드에서는 connect 함수가 접속의 결과가 나올때까지 대기하지 않고 바로 빠져나온다.
	connect(gh_socket, (sockaddr*)&addr_data, sizeof(addr_data));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) {
		if (gh_socket != INVALID_SOCKET) { closesocket(gh_socket); }

		PostQuitMessage(0);				// 메시지큐에 WM_QUIT 메시지를 넣는다.
	}
	else if (uMsg == WM_CREATE) {
		// 서버 접속 시도
		ConnectToServer(_T("127.0.0.1"), 19000, hWnd);				// 비동기를 위해 윈도우핸들을 넘긴다.
	}
	else if (uMsg == 26001) {				// FD_CONNECT 에 대한 발생메시지
		if (WSAGETSELECTERROR(lParam)) {			// 접속 실패시
			closesocket(gh_socket);
			gh_socket = INVALID_SOCKET;
		}
		else {			// 접속 성공 시
			int temp_size = 200000, read_size = 4;
			setsockopt(gh_socket, SOL_SOCKET, SO_RCVBUF, (char*)&temp_size, 4);
			setsockopt(gh_socket, SOL_SOCKET, SO_SNDBUF, (char*)&temp_size, 4);
			// FD_READ나 FD_CLOSE 를 수신하면 hWnd 윈도우에 26002메시지를 발생시킨다
			WSAAsyncSelect(gh_socket, hWnd, 26002, FD_READ | FD_CLOSE);
		}
	}
	else if (uMsg == 26002) {
		if (WSAGETSELECTEVENT(lParam) == FD_READ) {				// 서버로부터 FD_READ를 받으면
			// 테스트용 수신
			int data_size = 100000;
			WSAAsyncSelect(gh_socket, hWnd, 26002, FD_CLOSE); 

			char* p_data = new char[data_size];
			int read_size = ReceiveData(p_data, data_size);

			HDC h_dc = GetDC(hWnd);
			TCHAR msg_str[128];
			
			int len = _stprintf_s(msg_str, 128, _T("데이터 수신 : %d / %d"), read_size, data_size);
			//MessageBox(hWnd, msg_str, _T("title"), MB_OK);
			TextOut(h_dc, 10, 10, msg_str, len);
			ReleaseDC(hWnd, h_dc);
			delete[] p_data;

			WSAAsyncSelect(gh_socket, hWnd, 26002, FD_READ | FD_CLOSE);
		}
		else {				// 서버가 연결을 끊어 서버로부터 FD_CLOSE 를 통보받으면 
			closesocket(gh_socket);
			gh_socket = INVALID_SOCKET;
		}
	}

	// 개발자가 처리하지 않은 메시지들을 처리한다.
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 윈도우 클래스 등록
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;				// 배경색 지정
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);				// 커서 지정
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);			// 아이콘 지정
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;				// 기본 메시지 처리함수 지정
	wc.lpszClassName = _T("SjSockClient");				// 클래스명 지정
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);				// 윈도우 클래스 등록

	// 윈도우 생성
	HWND hWnd = CreateWindow(_T("SjSockClient"), _T("Win32 Client Socket"),
		WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {				// WM_QUIT 메시지가 발생할때까지 반복
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

