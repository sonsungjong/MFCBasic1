#include "pch.h"
#include "WinSocketServer.h"

// #define _WINSOCK_DEPRECATED_NO_WARNINGS �� framework.h�� �߰��ϱ�
#include <WS2tcpip.h>
#pragma comment(lib, "WS2_32.lib")

// �⺻ ������
WinSocketServer::WinSocketServer()
{
	InitObject(27);
}

WinSocketServer::WinSocketServer(unsigned char a_key)
{
	InitObject(a_key);
}

// �ʱ�ȭ �Լ�
void WinSocketServer::InitObject(unsigned char a_key)
{
	WSADATA temp;
	WSAStartup(0x0202, &temp);						// ���� ���̺귯�� �ε�

	for (int i = 0; i < MAX_USER_COUNT; i++)
	{
		m_users[i].h_socket = INVALID_SOCKET;
	}
	mh_listen_socket = INVALID_SOCKET;
	mp_notify_wnd = NULL;
	m_key = a_key;
	m_accept_msg_id = 25001;
	m_read_close_msg_id = 25002;
	mp_net_body_data = NULL;
	m_net_body_size = 0;
	mp_net_user = NULL;
}

WinSocketServer::~WinSocketServer()
{
	DestroyClientSockets();					// ���� Ŭ���̾�Ʈ ���� ���� ����, ���� ���� ����

	if (mp_net_body_data != NULL)				// ������ ���ſ� ����ϴ� �޸� ����
	{ delete[] mp_net_body_data; }

	WSACleanup();					// ���� ���̺귯�� ����
}

// ��� Ŭ���̾�Ʈ ���� ���� �� �������� ����
void WinSocketServer::DestroyClientSockets()
{
	UserData* p = m_users;
	for (int i = 0; i < MAX_USER_COUNT; i++, p++)
	{
		if (p->h_socket != INVALID_SOCKET)					// �Ҵ�� Ŭ���̾�Ʈ ������ ������
		{
			closesocket(p->h_socket);						// Ŭ���̾�Ʈ ���� ����
			p->h_socket = INVALID_SOCKET;					// Ŭ���̾�Ʈ ���� �ʱ�ȭ
		}
	}

	if (mh_listen_socket != INVALID_SOCKET)				// ���� ������ ������
	{
		closesocket(mh_listen_socket);				// �������� ����
		mh_listen_socket = INVALID_SOCKET;				// ���� ���� �ʱ�ȭ
	}
}

// 1���� Ŭ���̾�Ʈ���� ������ ����
void WinSocketServer::SendFrameData(SOCKET ah_socket, char a_msg_id, const void* ap_data, int a_size)
{
	char* p_data = new char[a_size + 4];					// ��� ������ 4 + �ٵ� ������ �Ҵ�

	*p_data = m_key;							// ����Ű�� ����
	*(p_data + 1) = a_msg_id;				// �ĺ��� ����
	*(unsigned short*)(p_data + 2) = a_size;				// �ٵ������ ����
	memcpy(p_data + 4, ap_data, a_size);					// �ٵ� ������ ����

	send(ah_socket, p_data, a_size + 4, 0);					// ��Ŷ ����
	delete[] p_data;
}

// ��� Ŭ���̾�Ʈ���� ����
void WinSocketServer::BroadcastFrameData(char a_msg_id, const void* ap_data, int a_size)
{
	char* p_data = new char[a_size + 4];				// ���������4 + �ٵ������ �Ҵ�

	*p_data = m_key;										// ����Ű ����
	*(p_data + 1) = a_msg_id;							// �ĺ��� ����
	*(unsigned short*)(p_data + 2) = a_size;				// ������ �ٵ������ ����
	memcpy(p_data + 4, ap_data, a_size);					// �ٵ� ���� ����

	// ��� ����ڿ��� ����
	UserData* p = m_users;
	for (int i = 0; i < MAX_USER_COUNT; i++, p++)
	{
		if (p->h_socket != INVALID_SOCKET)
		{ send(p->h_socket, p_data, a_size + 4, 0); }
	}
	delete[] p_data;
}

// ���� Listen ����
void WinSocketServer::StartListenService(const wchar_t* ap_ip_address, int a_port, CWnd* ap_notify_wnd, int a_accept_id, int a_read_close_id)
{
	mp_notify_wnd = ap_notify_wnd;					// ���� ȭ�� ����
	m_accept_msg_id = a_accept_id;					// ���� ID
	m_read_close_msg_id = a_read_close_id;			// �б� �Ǵ� ���� ID

	mh_listen_socket = socket(AF_INET, SOCK_STREAM, 0);				// TCP ���� ����

	sockaddr_in addr_data = { AF_INET, htons(a_port), };				// IPü��, PORT �Ҵ�
	InetPton(AF_INET, ap_ip_address, &addr_data.sin_addr.s_addr);				// ap_ip_address �ּҸ� ����ϴ� ��Ʈ��ũ�� ����ϵ��� ����

	bind(mh_listen_socket, (sockaddr*)&addr_data, sizeof(addr_data));				// ������ ��Ʈ��ũ �ý��ۿ� �����Ѵ�

	listen(mh_listen_socket, 5);				// ������ �����Ѵ�

	WSAAsyncSelect(mh_listen_socket, mp_notify_wnd->m_hWnd, m_accept_msg_id, FD_ACCEPT);			// ���� �õ���, ȭ�鿡 25001 �޽����� �߻��ϰ� �񵿱� ����
}

// ����ڰ� �����ϸ�, �� �Լ��� ���� ����ó���� ���ش�
UserData* WinSocketServer::ProcessAccept()
{
	sockaddr_in addr_data;
	int addr_data_size = sizeof(addr_data);

	SOCKET h_client_socket = accept(mh_listen_socket, (sockaddr*)&addr_data, &addr_data_size);			// ���� ���

	wchar_t temp_ip_address[32];
	InetNtop(AF_INET, &addr_data.sin_addr, temp_ip_address, 32);				// ���� addr_data �� ���ڿ��� temp_ip_address �� ����
	int index = AddNewUser(h_client_socket, temp_ip_address);

	if (index == MAX_USER_COUNT)					// �����ڼ� �ʰ�
	{
		closesocket(h_client_socket);
		return NULL;
	}
	return m_users + index;				// ���� ������ ������� ������ ���� �ּ� ��ȯ
}

// ���ο� ����� ���� ó��
int WinSocketServer::AddNewUser(SOCKET ah_new_socket, const wchar_t* ap_ip_address)
{
	UserData* p = m_users;
	for (int i = 0; i < MAX_USER_COUNT; i++, p++)				// INVALID_SOCKET �� ���� ã�� ��ȸ
	{
		if (p->h_socket == INVALID_SOCKET)
		{
			p->h_socket = ah_new_socket;
			wcscpy_s(p->ip_address, 16, ap_ip_address);
			WSAAsyncSelect(ah_new_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_READ | FD_CLOSE);
			return i;
		}
	}
	return MAX_USER_COUNT;				// �����ڼ��� �̹� �ִ�
}

// ���� �ڵ��� ���� �ش� ������ ���� ã��
UserData* WinSocketServer::GetUserData(SOCKET ah_socket)
{
	for (int i = 0; i < MAX_USER_COUNT; i++)
	{
		if (m_users[i].h_socket == ah_socket)
		{ return m_users + i; }
	}
	return NULL;			// ������ NULL
}

// 25002 �޽��� �߻� �Ǵ� ����� ���
void WinSocketServer::CloseSocket(SOCKET ah_socket, UserData* ap_close_user)
{
	UserData* p_user = GetUserData(ah_socket);

	// ã�Ƽ� ������ ���� ����
	if (p_user != NULL)
	{
		if (ap_close_user != NULL)
		{
			memcpy(ap_close_user, p_user, sizeof(UserData));
			p_user->h_socket = INVALID_SOCKET;
		}
	}
	closesocket(ah_socket);					// �ش� ���� ����
}

// �޽��� ����
int WinSocketServer::ReceiveData(SOCKET ah_socket, char* ap_data, int a_size)
{
	int read_size = 0, total_size = 0, retry_count = 0;

	// a_size�� ũ�Ⱑ ������������ ����
	while (total_size < a_size)
	{
		read_size = recv(ah_socket, ap_data + total_size, a_size - total_size, 0);

		if (read_size == SOCKET_ERROR || read_size == 0)					// �б� ����
		{
			Sleep(10);
			retry_count++;
			if(retry_count > 300)						// ��õ� 300ȸ���� ���������� �۾� �ߴ�
			{ break; }
		}
		else 
		{
			retry_count = 0;
			total_size += read_size;						// ���� ������ �ջ�
		}
	}
	return total_size;				// ������ ����Ʈũ�� ��ȯ
}

// ��� ������ ó��
int WinSocketServer::ProcessHeaderInfo(SOCKET ah_socket)
{
	unsigned char key;

	recv(ah_socket, (char*)&key, 1, 0);				// ���Ź��� ����Ű�� �д´�

	if (key == m_key)				// ������ ����Ű�� ��ġ�� ���
	{
		recv(ah_socket, (char*)&m_net_msg_id, 1, 0);				// �ĺ��� ����
		recv(ah_socket, (char*)&m_net_body_size, 2, 0);			// �ٵ� ������ ����
		return 1;
	}
	return 0;				// ����Ű�� ��ġ���� ���� ���
}

// FD_READ�� 25002 �޽����� �߻��ϸ� ����
int WinSocketServer::BeginNetworkProcess(SOCKET ah_socket)
{
	WSAAsyncSelect(ah_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_CLOSE);				// �����б�� ��õ��� ���� FD_READ�� �����ϰ� �ٽ� �񵿱� ����
	
	mp_net_user = GetUserData(ah_socket);					// �޽����� ���� Ŭ���̾�Ʈ ���� ����

	int state = ProcessHeaderInfo(ah_socket);				// ����� �д´�

	if (state != 0 && m_net_body_size > 0)				// ��� ���ſ� �����ϰ� �ٵ� ũ�Ⱑ 0 �̻��� �� ����
	{
		mp_net_body_data = new char[m_net_body_size];
		state = m_net_body_size == ReceiveData(ah_socket, mp_net_body_data, m_net_body_size);
	}
	return state;					// ��������
}

// FD_READ�� 25002 �߻� �� ������ BeginNetworkProcess() �� ��ó��
int WinSocketServer::EndNetworkProcess()
{
	WSAAsyncSelect(mp_net_user->h_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_READ | FD_CLOSE);
	return 1;
}

// ���� �񵿱� �޽����� ó��
void WinSocketServer::MessageProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == m_accept_msg_id)				// ���� �õ���
	{
		UserData* p_user = ProcessAccept();
		if(p_user != NULL)
		{ AcceptUserProc(p_user); }
	}
	else if (message == m_read_close_msg_id)
	{
		if (LOWORD(lParam) == FD_READ)
		{
			if (BeginNetworkProcess((SOCKET)wParam))			// ����� �д´�
			{
				if (ProcessNetMessage() == 1)				// �޽��� ���Ž�
				{
					EndNetworkProcess();
				}

				if (mp_net_body_data != NULL)				// ���ſ� ���� �޸� ����
				{
					delete[] mp_net_body_data;
					mp_net_body_data = NULL;
				}
			}
			else								// ��� �б� ���� (����Ű ����ġ)
			{
				CloseSocket(mp_net_user->h_socket, &m_temp_user_data);		// ���� �����ϰ� m_temp_user_data�� ���� ����
				CloseUserProc(&m_temp_user_data, 1);				// ������ Ŭ���̾�Ʈ�� ���� �߰��۾�(������ 1)
			}
		}
		else					// FD_CLOSE
		{
			CloseSocket((SOCKET)wParam, &m_temp_user_data);				// ���� ���� �� m_temp_user_data�� ������ ����
			CloseUserProc(&m_temp_user_data, 0);				// ���� ������ Ŭ���̾�Ʈ�� ���� �߰��۾�(���� 0)
		}
	}
}

