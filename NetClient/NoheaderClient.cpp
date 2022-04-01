#include "pch.h"
#include <WinSock2.h>
#include "NoheaderClient.h"
#include <WS2tcpip.h>						// InetPton
#pragma comment(lib, "WS2_32.lib")

NoheaderClient::NoheaderClient()
{
	InitObject();
}

NoheaderClient::~NoheaderClient()
{
	// 사용중인 소켓을 제거
	CloseSocket();
	// 수신용 메모리를 해제
	if (mp_net_data != nullptr) { delete[] mp_net_data; }
	WSACleanup();			// 소켓중지
}

// 초기화용 함수, 내부호출용
void NoheaderClient::InitObject()
{
	WSADATA temp;
	WSAStartup(0x0202, &temp);

	mh_socket = INVALID_SOCKET;
	m_is_connected = FALSE;
	m_connect_msg_id = CONNECTED;
	m_read_close_msg_id = DISCONNECTED;
	mp_notify_wnd = nullptr;
	m_nSoketIdx = -1;
}