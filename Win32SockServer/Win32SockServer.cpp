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
SOCKET gh_listen_socket = INVALID_SOCKET;					// ���ӿ�
// Ŭ���̾�Ʈ�� ����� �ϱ� ���� ���� �ڵ�
SOCKET gh_client_socket = INVALID_SOCKET;					// ��ſ�

// �׽�Ʈ�� �Ŵ��ڷ�
char* gp_test_data;

void StartListenService(const TCHAR* ap_ip_address, int a_port, HWND ah_wnd)
{
	// ����2.2 ����
	WSADATA temp;
	WSAStartup(0x0202, &temp);

	// AF_INET �ּ�ü���� TCP ���� ����
	gh_listen_socket = socket(AF_INET, SOCK_STREAM, 0);

	// ��Ʈ��ȣ
	sockaddr_in addr_data = { AF_INET, htons(a_port), };
	// IP�ּ� ����
	InetPton(AF_INET, ap_ip_address, &addr_data.sin_addr.s_addr);

	// IP�� PORT��ȣ�� ����Ͽ� ������ ��Ʈ��ũ �ý��ۿ� �����Ѵ�.
	bind(gh_listen_socket, (sockaddr*)&addr_data, sizeof(addr_data));
	// ���� ó�������� �����Ѵ�. (����ó��)
	listen(gh_listen_socket, 5);
	// ����ڰ� FD_ACCEPT�� �õ����� �� ����(����) ��ȭ���ڿ� 25001�� �޽����� �߻��ϵ��� �񵿱� ����
	WSAAsyncSelect(gh_listen_socket, ah_wnd, 25001, FD_ACCEPT);
	// ��� �ð� �� ��������� ���ϱ� ���ؼ� �񵿱�� ����
	// ���� 25001 �޽����� ������ �Ϳ� ���ؼ� ó���ϸ� ��
}

void ProcessAccept(HWND ah_wnd)
{
	// ������ �õ��� ����(Ŭ���̾�Ʈ�� ����� ����)�� �ּҸ� ������ ����
	sockaddr_in addr_data;
	// �ڽ��� ����� �ּ� ���� ������ ũ�⸦ ���
	int addr_data_size = sizeof(addr_data);

	// Ŭ���̾�Ʈ ������ ������ �㰡
	// ���� ������ �����Ǿ� �ڵ��� ���� ��ȯ�ȴ�. (h_socket�� ����)
	// addr_data �������� ���ӽõ��� ������ IP�� ������������ ����ȴ�.
	SOCKET h_socket = accept(gh_listen_socket, (sockaddr*)&addr_data, &addr_data_size);

	if (gh_client_socket == INVALID_SOCKET) {			// ������ �̷��� ������ (�Ѱ��� Ŭ���̾�Ʈ�� ���)
		gh_client_socket = h_socket;

		// Ŭ���̾�Ʈ�� �����ų� ������ ������ 25002 �޽����� �߻���Ŵ
		WSAAsyncSelect(gh_client_socket, ah_wnd, 25002, FD_READ | FD_CLOSE);

		// �׽�Ʈ�� ������
		int temp_size = 200000, read_size = 4;
		setsockopt(gh_client_socket, SOL_SOCKET, SO_SNDBUF, (char*)&temp_size, 4);
		setsockopt(gh_client_socket, SOL_SOCKET, SO_RCVBUF, (char*)&temp_size, 4);
		WSAAsyncSelect(gh_client_socket, ah_wnd, 25002, FD_READ | FD_CLOSE);
		*(int*)gp_test_data = 100000;
		send(gh_client_socket, gp_test_data, 100000, 0);					// ����Ʈ�� ũ�⸦ ����
	}
	else {			// �̹� �ٸ� Ŭ���̾�Ʈ�� �������̸�
		closesocket(h_socket);
	}
}

// ������ ū �����͸� �����Ҷ� ����ó��
int ReceiveData(SOCKET ah_socket, char* ap_data, int a_size)
{
	int total_size = 0, read_size, retry_count = 0;
	// a_size ũ�⸸ŭ ��� ���ŵɶ����� �ݺ��õ��Ѵ�.
	while (total_size < a_size)
	{
		// ���� ũ�⸸ŭ ������ �õ��Ѵ�.
		read_size = recv(ah_socket, ap_data + total_size, a_size - total_size, 0);
		if (read_size == SOCKET_ERROR || read_size == 0) {			// �б� ���н�
			Sleep(10);						// 0.01�� ���
			retry_count++;
			if (retry_count > 300) { break; }				// 300ȸ���� ��õ�
		}
		else {
			retry_count = 0;					// ��õ� Ƚ���� �ʱ�ȭ
			total_size += read_size;				// ���ŵ� �������� ũ�⸦ �ջ�
		}
	}
	return total_size;				// ��ü ������ ����Ʈ�� ����Ѵ�.
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) {					// WM_CLOSE ó�� �Ŀ� ������ �޽���
		// ����ϴ� ������ �ݴ´�.
		closesocket(gh_listen_socket);
		if (gh_client_socket != INVALID_SOCKET) { closesocket(gh_client_socket); }
		
		// �׽�Ʈ�� ����
		delete[] gp_test_data;
		
		// �ڽ��� �޽��� ť�� WM_QUIT �޽����� �ִ´�
		PostQuitMessage(0);
	}
	else if (uMsg == WM_CREATE) {
		gp_test_data = new char[100000];
		// ���� ���񽺸� �����Ѵ�.
		StartListenService(_T("127.0.0.1"), 19000, hWnd);
	}
	else if (uMsg == 25001) {			// FD_ACCEPT�� ���� �߻��޽���
		ProcessAccept(hWnd);
	}
	else if (uMsg == 25002) {			// FD_READ Ȥ�� FD_CLOSE�� ���� �߻��޽���
		if (WSAGETSELECTEVENT(lParam) == FD_READ) {			// FD_READ �� ��� (Ŭ���̾�Ʈ�� �޽����� ����)
			int data;
			//recv(gh_client_socket, (char*)&data, 4, 0);				// 4byte��ŭ �о data�� ����
			ReceiveData(gh_client_socket, (char*)&data, 4);
		}
		else {			// FD_CLOSE �� ��� (Ŭ���̾�Ʈ�� ������ ����)
			closesocket(gh_client_socket);
			gh_client_socket = INVALID_SOCKET;
		}
	}

	// �����ڰ� ó������ ���� �޽������� ó���Ѵ�
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ������ Ŭ���� ���
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

	// ������ ����
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