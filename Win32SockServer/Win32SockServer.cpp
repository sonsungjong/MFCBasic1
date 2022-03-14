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
SOCKET gh_listen_socket = INVALID_SOCKET;
// 클라이언트와 통신을 하기 위한 소켓 핸들
SOCKET gh_client_socket = INVALID_SOCKET;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) {					// WM_CLOSE 처리 후에 들어오는 메시지
		// 사용하던 소켓을 닫는다.
		closesocket(gh_listen_socket);
		if (gh_client_socket != INVALID_SOCKET) { closesocket(gh_client_socket); }
		// 자신의 메시지 큐에 WM_QUIT 메시지를 넣는다
		PostQuitMessage(0);
	}
	else if (uMsg == WM_CREATE) {
		// 리슨 서비스를 시작한다.
		//StartListenService(_T("127.0.0.1"), 19000, hWnd);
	}
	else if (uMsg == 25001) {			// 새로운 클라이언트가 접속
		//ProcessAccept(hWnd);
	}
	else if (uMsg == 25002) {			// 데이터 수신 또는 클라이언트 접속 해제
		if (WSAGETSELECTEVENT(lParam) == FD_READ) {			// 데이터 수신

		}
		else {			// 클라이언트 접속 해제
			closesocket(gh_client_socket);
			gh_client_socket = INVALID_SOCKET;
		}
	}

	// 개발자가 처리하지 않은 메시지들을 처리한다
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, )