// Win32SockClient.cpp : Defines the entry point for the application.
//

#include "pch.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "framework.h"
#include "Win32SockClient.h"

// ���� �Լ��� ����ϱ� ���� ���
#include <WinSock2.h>
#include <WS2tcpip.h>						// InetPton �Լ� ����� ���� �߰�
// ���� �Լ��� ����ϱ� ���� ���̺귯��
#pragma comment(lib, "WS2_32.lib")

// ������ ����� �ϱ����� ���� �ڵ�
SOCKET gh_socket = INVALID_SOCKET;

// ������ ������ �����͸� ������ �� ����� �Լ�
int ReceiveData(char* ap_data, int a_size)
{
	int total_size = 0, read_size, retry_count = 0;
	// a_size ũ�⸸ŭ �� ���ŵ� ������ �ݺ��Ѵ�.
	while (total_size < a_size) {
		// ���� ũ�⸸ŭ ������ �õ��Ѵ�.
		read_size = recv(gh_socket, ap_data + total_size, a_size - total_size, 0);
		if (read_size == SOCKET_ERROR || read_size == 0) {				// �б� ���н�
			Sleep(10);
			retry_count++;
			if (retry_count > 300) { break; }				// 300ȸ ��õ�
		}
		else {
			retry_count = 0;
			total_size += read_size;						// ���ŵ� �������� ũ�⸦ �ջ�
		}
	}
	return total_size;				// ���ŵ� ����Ʈ ũ�⸦ ��ȯ
}

// ������ ������ �õ�
void ConnectToServer(const TCHAR* ap_ip_address, int a_port, HWND ah_wnd)
{
	// ���� ���̺귯�� ���
	WSADATA temp;
	WSAStartup(0x0202, &temp);

	// AF_INET ü��� TCP���� ����
	gh_socket = socket(AF_INET, SOCK_STREAM, 0);

	// IP �ּ�, ���α׷� ��Ʈ ��ȣ
	sockaddr_in addr_data = { AF_INET, htons(a_port), };

	// ap_ip_address �ּҸ� ����ϴ� ��Ʈ��ũ�� ����ϵ��� ����
	InetPton(AF_INET, ap_ip_address, &addr_data.sin_addr);

	// ���� ����(FD_CONNECT)�� �񵿱� ������� ó��
	// FD_CONNECT�� �߻��ϸ� ah_wnd ������� 26001 �޽����� �߻���Ų��.
	WSAAsyncSelect(gh_socket, ah_wnd, 26001, FD_CONNECT);

	// ������ ������ �õ��Ѵ�
	// �񵿱� ��忡���� connect �Լ��� ������ ����� ���ö����� ������� �ʰ� �ٷ� �������´�.
	connect(gh_socket, (sockaddr*)&addr_data, sizeof(addr_data));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) {
		if (gh_socket != INVALID_SOCKET) { closesocket(gh_socket); }

		PostQuitMessage(0);				// �޽���ť�� WM_QUIT �޽����� �ִ´�.
	}
	else if (uMsg == WM_CREATE) {
		// ���� ���� �õ�
		ConnectToServer(_T("127.0.0.1"), 19000, hWnd);				// �񵿱⸦ ���� �������ڵ��� �ѱ��.
	}
	else if (uMsg == 26001) {				// FD_CONNECT �� ���� �߻��޽���
		if (WSAGETSELECTERROR(lParam)) {			// ���� ���н�
			closesocket(gh_socket);
			gh_socket = INVALID_SOCKET;
		}
		else {			// ���� ���� ��
			int temp_size = 200000, read_size = 4;
			setsockopt(gh_socket, SOL_SOCKET, SO_RCVBUF, (char*)&temp_size, 4);
			setsockopt(gh_socket, SOL_SOCKET, SO_SNDBUF, (char*)&temp_size, 4);
			// FD_READ�� FD_CLOSE �� �����ϸ� hWnd �����쿡 26002�޽����� �߻���Ų��
			WSAAsyncSelect(gh_socket, hWnd, 26002, FD_READ | FD_CLOSE);
		}
	}
	else if (uMsg == 26002) {
		if (WSAGETSELECTEVENT(lParam) == FD_READ) {				// �����κ��� FD_READ�� ������
			// �׽�Ʈ�� ����
			int data_size = 100000;
			WSAAsyncSelect(gh_socket, hWnd, 26002, FD_CLOSE); 

			char* p_data = new char[data_size];
			int read_size = ReceiveData(p_data, data_size);

			HDC h_dc = GetDC(hWnd);
			TCHAR msg_str[128];
			
			int len = _stprintf_s(msg_str, 128, _T("������ ���� : %d / %d"), read_size, data_size);
			//MessageBox(hWnd, msg_str, _T("title"), MB_OK);
			TextOut(h_dc, 10, 10, msg_str, len);
			ReleaseDC(hWnd, h_dc);
			delete[] p_data;

			WSAAsyncSelect(gh_socket, hWnd, 26002, FD_READ | FD_CLOSE);
		}
		else {				// ������ ������ ���� �����κ��� FD_CLOSE �� �뺸������ 
			closesocket(gh_socket);
			gh_socket = INVALID_SOCKET;
		}
	}

	// �����ڰ� ó������ ���� �޽������� ó���Ѵ�.
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ������ Ŭ���� ���
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;				// ���� ����
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);				// Ŀ�� ����
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);			// ������ ����
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;				// �⺻ �޽��� ó���Լ� ����
	wc.lpszClassName = _T("SjSockClient");				// Ŭ������ ����
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);				// ������ Ŭ���� ���

	// ������ ����
	HWND hWnd = CreateWindow(_T("SjSockClient"), _T("Win32 Client Socket"),
		WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {				// WM_QUIT �޽����� �߻��Ҷ����� �ݺ�
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

