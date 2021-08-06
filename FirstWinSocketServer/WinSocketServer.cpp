#include "pch.h"
#include "WinSocketServer.h"

// #define _WINSOCK_DEPRECATED_NO_WARNINGS �� framework.h�� �߰��ϱ�
#include <WS2tcpip.h>				// InetPton �Լ� ����� ���� ����
#pragma comment(lib, "WS2_32.lib")

// �⺻ ������
WinSocketServer::WinSocketServer()
{
	InitObject(27);				// key�� 27�� ����
}
// ���������� key�� �������� �ʰ� �ܺο��� �����Ϸ��� �����ڿ��� key���� �ް� ����
WinSocketServer::WinSocketServer(unsigned char a_key)
{
	InitObject(a_key);
}

// ��ü�� �ʱ�ȭ�ϴ� �Լ�, �����ڿ��� ȣ��
void WinSocketServer::InitObject(unsigned char a_key) {
	WSADATA temp;
	WSAStartup(0x0202, &temp);				// ���� ���̺귯���� ��밡�� ���·� ����

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

WinSocketServer::~WinSocketServer() {
	// ���ӵ� Ŭ���̾�Ʈ ���� ���� ����, ���� ���� ����
	DestroyClientSockets();

	// ������ ���ſ� ����ϴ� �޸� ����
	if (mp_net_body_data != NULL) delete[] mp_net_body_data;

	WSACleanup();			// ���� ���̺귯�� ��� ���� ����
}

// ������ ������ ��� Ŭ���̾�Ʈ ���� ���� �� Listen���� ����
void WinSocketServer::DestroyClientSockets()
{
	UserData* p = m_users;
	for (int i = 0; i < MAX_USER_COUNT; i++, p++)
	{
		if (p->h_socket != INVALID_SOCKET) {			// �Ҵ�� ������ �ִٸ�
			closesocket(p->h_socket);						// ������ ����
			p->h_socket = INVALID_SOCKET;			// ������ �ٽ� ����� �� �ֵ��� �ʱ�ȭ
		}
	}

	if (mh_listen_socket != INVALID_SOCKET) {		// ���� ������ ������� �ִٸ�
		closesocket(mh_listen_socket);					// ���� ������ �ݴ´�.
		mh_listen_socket = INVALID_SOCKET;				// ���� ������ �ʱ�ȭ
	}
}

// 1���� Ŭ���̾�Ʈ���� �����͸� ����
// ������ ���� : "Key, Message ID, Body size, Body Data"
void WinSocketServer::SendFrameData(SOCKET ah_socket, char a_msg_id, const void* ap_data, int a_size)
{
	// ������ ������ �������� �����ϱ� ���� �޸𸮸� �Ҵ�
	char* p_data = new char[a_size + 4];
	// ���� Ű ���� ����
	*p_data = m_key;
	// �޽��� ���̵� ����
	*(p_data + 1) = a_msg_id;
	// ������ ���� ������ ũ�⸦ ����
	*(unsigned short*)(p_data + 2) = a_size;
	// ������ ���� �����͸� ����
	memcpy(p_data + 4, ap_data, a_size);
	// ah_socket ���� �����͸� a_size +4 ũ�� ��ŭ �����Ѵ�.
	send(ah_socket, p_data, a_size + 4, 0);
	// ������ ���忡 ����� �޸𸮸� ����
	delete[] p_data;
}

// ������ ��� Ŭ���̾�Ʈ���� �����͸� ����
void WinSocketServer::BroadcastFrameData(char a_msg_id, const void* ap_data, int a_size)
{
	// ������ ������ �������� �����ϱ� ���� �޸� �Ҵ�
	char* p_data = new char[a_size + 4];
	// ���� Ű���� ����
	*p_data = m_key;
	// �޽��� ���̵� ����
	*(p_data + 1) = a_msg_id;
	// ������ ���� ������ ũ�� ����
	*(unsigned short*)(p_data + 2) = a_size;
	// ������ ���� �����͸� ����
	memcpy(p_data + 4, ap_data, a_size);

	UserData* p = m_users;
	// ���ӵ� ��� ����ڿ��� �����͸� ����
	for (int i = 0; i < MAX_USER_COUNT; i++, p++)
	{
		// ������ ���ǰ� �ִٸ� p->h_socket���� �����͸� a_size +4 ũ�� ��ŭ ����
		if (p->h_socket != INVALID_SOCKET) {
			send(p->h_socket, p_data, a_size + 4, 0);
		}
	}
	// ������ ���忡 ����� �޸� ����
	delete[] p_data;
}

// ���������Ҷ� Listen ���񽺸� ������ �� ����ϴ� �Լ�
void WinSocketServer::StartListenService(const wchar_t* ap_ip_address, int a_port, CWnd* ap_notify_wnd, int a_accept_id, int a_read_close_id)
{
	mp_notify_wnd = ap_notify_wnd;
	m_accept_msg_id = a_accept_id;
	m_read_close_msg_id = a_read_close_id;

	// AF_INET �ּ� ü�踦 ����ϴ� TCP����� ���� ����
	mh_listen_socket = socket(AF_INET, SOCK_STREAM, 0);

	// IP �ּ� ü��, ���α׷� �ĺ� ��ȣ(port)
	sockaddr_in addr_data = { AF_INET, htons(a_port), };
	// ap_ip_address �ּҸ� ����ϴ� ��Ʈ��ũ�� ����ϵ��� ����
	InetPton(AF_INET, ap_ip_address, &addr_data.sin_addr.s_addr);

	// addr_data�� ������ ������ ����Ͽ� ������ ������ũ �ý��ۿ� �����Ѵ�.
	bind(mh_listen_socket, (sockaddr*)&addr_data, sizeof(addr_data));
	// ������ ó���� ������ �����Ѵ�.
	// ������ ���� ó���� �ƴ϶� ����ó���̱� ������ ���ڰ� ũ�ٰ� ���������� ����
	listen(mh_listen_socket, 5);
	// mh_listen_socket �� ��ÿ��ڰ� ������ �õ�(FD_ACCEPT)���� ��
	// ���� ��ȭ���� (m_hWnd)�� 25001�� �޽����� �߻��ϵ��� �񵿱�� �����Ѵ�.
	WSAAsyncSelect(mh_listen_socket, mp_notify_wnd->m_hWnd, m_accept_msg_id, FD_ACCEPT);
}

// ���ο� ����ڰ� �������� ��, �� �Լ��� ȣ���ϸ� ������� ������ ó���Ѵ�.
UserData* WinSocketServer::ProcessAccept()
{
	// ������ �õ��� ����(Ŭ���̾�Ʈ�� ����� ����)�� �ּҸ� ������ ����
	sockaddr_in addr_data;
	// �ڽ��� ����� �ּ� ���� ������ ũ�⸦ ���
	int addr_data_size = sizeof(addr_data);

	// Ŭ���̾�Ʈ ������ ������ ����Ѵ�.
	// ������ ����ϸ� ���� ������ �����Ǿ� �� �ڵ� ���� ��ȯ�ȴ�(h_client_socket)
	// addr_data �������� ������ �õ��� ������ IP�� ������ ���·� ����ȴ�.
	SOCKET h_client_socket = accept(mh_listen_socket, (sockaddr*)&addr_data, &addr_data_size);

	wchar_t temp_ip_address[32];
	// addr_data ������ ���� ���·� ����Ǿ� �ִ� IP�� ���ڿ� ���·� �����ؼ� temp_ip_address�� ����.
	InetNtop(AF_INET, &addr_data.sin_addr, temp_ip_address, 32);
	int index = AddNewUser(h_client_socket, temp_ip_address);
	// ���� �迭 ��ü�� �� üũ���µ� �� ������ ���ٸ� �ִ� ������ ���� �ʰ��� ��
	// ������ �����ϰ� ������ ���
	if (index == MAX_USER_COUNT) {
		closesocket(h_client_socket);
		return NULL;			// ������ ���� �ʰ��Ͽ� ���� ����
	}
	return m_users + index;			// ���� ������ ������� ������ ��� �ּҸ� ��ȯ
}

// ���ο� ������� ������ ó���Ѵ�
// m_users �迭�� h_socket ���� INVALID_SOCKET�� �׸� ���ο� ����� ������ ����
int WinSocketServer::AddNewUser(SOCKET ah_new_socket, const wchar_t* ap_ip_address)
{
	UserData* p = m_users;
	// h_client_socket�� ���������̱� ������ �ش� �Լ��� ����Ǹ� �������.
	// ���� �ڽ��� �����ϰ� �ִ� Ŭ���̾�Ʈ ���� ������ �� ���� �ִ��� Ȯ���ؼ� �����Ѵ�
	for (int i = 0; i < MAX_USER_COUNT; i++, p++)
	{
		// �� �迭�� h_socket�� INVALID_SOCKET ���� ����Ǿ� �ִٸ� �ش� �迭�� ������ �ڵ��� ������� ���� ��.
		if (p->h_socket == INVALID_SOCKET) {
			// �迭�� ����ִ� ������ ������ ������ �ڵ��� ����
			p->h_socket = ah_new_socket;
			// ������ ������� IP�� �����Ѵ�.
			wcscpy_s(p->ip_address, 16, ap_ip_address);
			// h_client_socket�� FD_READ �Ǵ� FD_CLOSE �̺�Ʈ�� �߻��ϸ� ��ȭ���ڷ� 25002�� �޽����� �����ϵ��� �񵿱�� ����
			WSAAsyncSelect(ah_new_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_READ | FD_CLOSE);
			return i;
		}
	}
	return MAX_USER_COUNT;			// ����ִ� �׸��� ������
}

// ���� �ڵ��� ������ �ش� ���� �ڵ��� ����� m_users �迭�� �׸� �ּҸ� ��� �Լ�
UserData* WinSocketServer::GetUserData(SOCKET ah_socket)
{
	// �ڽ��� �����ϰ� �ִ� Ŭ���̾�Ʈ �� �̺�Ʈ�� �߻���Ų Ư�� Ŭ���̾�Ʈ�� Ȯ���ϱ� ���� �迭�� ��ȸ
	for (int i = 0; i < MAX_USER_COUNT; i++)
	{
		// ah_socket�� ���� ��ġ�ϴ� ������ ���� �̺�Ʈ�� �߻���Ų Ŭ���̾�Ʈ
		if (m_users[i].h_socket == ah_socket) return m_users + i;
	}
	return NULL;			// �˻� ���н�
}

// FD_CLOSE�� ���� 25002 �޽����� �߻��Ͽ� ������� ���� ������ ������ �� ���
// 25002 �޽��� ������ ����ϴ� ���� �ƴ϶� Ư�� ����ڸ� �����ų ������ ���
// �ι�° �ƱԸ�Ʈ ap_close_user�� ������ ������ ������� �����Ͱ� �����.
// UserData ����ü�� ���������� �����ؼ� �ش� ������ �ּҸ� �����ؾ� ������ ���� �� ����
void WinSocketServer::CloseSocket(SOCKET ah_socket, UserData* ap_close_user)
{
	// ah_socket�� �ش��ϴ� ����� ������ ã�´�.
	UserData* p_user = GetUserData(ah_socket);
	// ����� ������ ã�Ұ� �� ������ ������ �޸𸮰� ���޵Ǹ� ������ ����� ������ ap_close_user�� ����
	if (p_user != NULL) {
		if (ap_close_user != NULL) {
			memcpy(ap_close_user, p_user, sizeof(UserData));
			// �迭�� ����� ������ �ʱ�ȭ
			p_user->h_socket = INVALID_SOCKET;
		}
	}
	closesocket(ah_socket);			// ���� ����
}

// Ŭ���̾�Ʈ�� ������ �����͸� ������ �� ����ϴ� �Լ�
int WinSocketServer::ReceiveData(SOCKET ah_socket, char* ap_data, int a_size) {
	int read_size, total_size = 0, retry_count = 0;
	// a_size ũ��� ������������ ������ �ݺ�
	while (total_size < a_size) {
		// ���� ũ�⸸ŭ ����
		read_size = recv(ah_socket, ap_data + total_size, a_size - total_size, 0);
		if (read_size == SOCKET_ERROR || read_size == 0) {		// �б� ����
			Sleep(10);			// 10ms ���
			retry_count++;			// ��õ�Ƚ�� ����
			if (retry_count > 300) break;			// 300ȸ ��õ����� �����ϸ� �۾� �ߴ�
		}
		else {
			retry_count = 0;			// ��õ� Ƚ�� �ʱ�ȭ
			total_size += read_size;			// ���ŵ� �������� ũ�� �ջ�
		}
	}
	return total_size;			// ��ü ������ ����Ʈ ũ�� ��ȯ
}

// ��Ʈ��ũ �޽������� ��� ������ ó���ϴ� �Լ�
int WinSocketServer::ProcessHeaderInfo(SOCKET ah_socket) {
	unsigned char key;
	// ù ����Ʈ�� key���� ����
	recv(ah_socket, (char*)&key, 1, 0);
	// key ���� ������ key ���� ��ġ���� ��
	if (key == m_key) {
		recv(ah_socket, (char*)&m_net_msg_id, 1, 0);
		recv(ah_socket, (char*)&m_net_body_size, 2, 0);
		return 1;		// key�� ��ġ�� ��� (���� ���)
	}
	return 0;			// key�� ��ġ���� ���� ��� (���������� ���)
}

// ��Ʈ��ũ�� �����Ͱ� ���ŵǸ� ����� �а� body�����͸� �о� �۾��� ������ �� �ֵ��� �غ��ϴ� �Լ�
// FD_READ�� ���� 25002�� �߻��ϸ� ���
int WinSocketServer::BeginNetworkProcess(SOCKET ah_socket) {
	// �����б� �� ��õ� �� ���� FD_READ�� �����ϰ� �ٽ� �񵿱⸦ ����
	WSAAsyncSelect(ah_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_CLOSE);
	// �����͸� ������ Ŭ���̾�Ʈ�� ������ ã�Ƽ� mp_net_user�� ����
	mp_net_user = GetUserData(ah_socket);

	// ����� ���� �д´�.
	int state = ProcessHeaderInfo(ah_socket);
	// ��������̸� Body�� 0���� Ŭ�� Body ����
	if (state && m_net_body_size > 0) {
		// Body �����͸� �����ϱ� ���� �޸� �Ҵ�
		mp_net_body_data = new char[m_net_body_size];
		// Body �����͸� ����, ���ſ��� ����� state�� ����
		state = m_net_body_size == ReceiveData(ah_socket, mp_net_body_data, m_net_body_size);
	}
	return state;
}

// FD_READ �̺�Ʈ�� ���� �߻��� 25002 �޽��� �۾��� �Ϸ��ϸ� ȣ��
// BeginNetworkProcess() ���� ���� �������� �����ϴ� �۾� ����
int WinSocketServer::EndNetworkProcess()
{
	// �ٽ� ������ ���� ���¸� Ȯ���� �� �ֵ��� FD_READ �̺�Ʈ�� �缳��
	WSAAsyncSelect(mp_net_user->h_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_READ | FD_CLOSE);
	return 1;
}

// ���� ���� �񵿱� �޽����� ó���ϴ� �Լ�
void WinSocketServer::MessageProc(UINT message, WPARAM wParam, LPARAM lParam) {
	if (message == m_accept_msg_id) {			// ���ο� Ŭ���̾�Ʈ�� ������ �õ��ϴ� ���
		UserData* p_user = ProcessAccept();			// �⺻���� ���� ó��
		if (p_user != NULL) AcceptUserProc(p_user);			// �߰����� ����ó���� �� �� �ֵ��� �Լ� ȣ��
	}
	else if (message == m_read_close_msg_id) {
		if (LOWORD(lParam) == FD_READ) {		// �����Ͱ� ���ŵ�
			if (BeginNetworkProcess((SOCKET)wParam)) {			// ����� �д´�
				// ���������� �޽����� ó���ߴٸ� �������۾��� ȣ��(FD_READ �缳�� ����)
				if (1 == ProcessNetMessage()) {
					EndNetworkProcess();
				}
				// ������ ���ſ� ����ϴ� �޸� ����
				if (mp_net_body_data != NULL) {
					delete[] mp_net_body_data;
					mp_net_body_data = NULL;
				}
			}
			else {			// key���� ��ġ���� ����
				// ���� ������ ������ �����ϰ� ������ ����� ������ m_temp_user_data�� ����
				CloseSocket(mp_net_user->h_socket, &m_temp_user_data);
				// ������ ������ Ŭ���̾�Ʈ�� �߰����� �۾��� �� �� �ֵ��� �Լ� ȣ��
				CloseUserProc(&m_temp_user_data, 1);
			}
		}
		else {			// FD_CLOSE, ����� �����
			// ���� ������ ������ ���� �� ������ ����� ������ m_temp_user_data�� ����
			CloseSocket((SOCKET)wParam, &m_temp_user_data);
			// ������ ������ Ŭ���̾�Ʈ�� �߰����� �۾��� �� �� �ֵ��� �Լ� ȣ��
			CloseUserProc(&m_temp_user_data, 0);
		}
	}
}