// Win32SockServer.cpp : Defines the entry point for the application.
//

#include "pch.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "framework.h"
#include "Win32SockServer.h"

// ���� �Լ��� ����ϱ� ���� �������
#include <WinSock2.h>
#include <WS2tcpip.h>			// InetPton �Լ� ����� ����
// ���� �Լ��� ����ϱ� ���� ���̺귯�� ����
#pragma comment(lib, "WS2_32.lib")

// Ŭ���̾�Ʈ�� ������ ó���ϱ� ���� ���� �ڵ�
SOCKET gh_listen_socket = INVALID_SOCKET;
// Ŭ���̾�Ʈ�� ����� �ϱ� ���� ���� �ڵ�
SOCKET gh_client_socket = INVALID_SOCKET;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) {					// WM_CLOSE ó�� �Ŀ� ������ �޽���
		// ����ϴ� ������ �ݴ´�.
		closesocket(gh_listen_socket);
		if (gh_client_socket != INVALID_SOCKET) { closesocket(gh_client_socket); }
		// �ڽ��� �޽��� ť�� WM_QUIT �޽����� �ִ´�
		PostQuitMessage(0);
	}
	else if (uMsg == WM_CREATE) {
		// ���� ���񽺸� �����Ѵ�.
		//StartListenService(_T("127.0.0.1"), 19000, hWnd);
	}
	else if (uMsg == 25001) {			// ���ο� Ŭ���̾�Ʈ�� ����
		//ProcessAccept(hWnd);
	}
	else if (uMsg == 25002) {			// ������ ���� �Ǵ� Ŭ���̾�Ʈ ���� ����
		if (WSAGETSELECTEVENT(lParam) == FD_READ) {			// ������ ����

		}
		else {			// Ŭ���̾�Ʈ ���� ����
			closesocket(gh_client_socket);
			gh_client_socket = INVALID_SOCKET;
		}
	}

	// �����ڰ� ó������ ���� �޽������� ó���Ѵ�
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, )