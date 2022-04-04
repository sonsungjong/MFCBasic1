#include "pch.h"
#include "WinSocketClient.h"

// #define _WINSOCK_DEPRECATED_NO_WARNINGS		�� framework.h �� �߰��ؾ��մϴ�!!
#include <WS2tcpip.h>			// InetPton �Լ� ����� ���� �߰��� (�����ڵ带 �Ϲ������� ��ȯ�ϴ� �Լ�)
#pragma comment(lib, "WS2_32.lib")

// �⺻ ������
WinSocketClient::WinSocketClient()
{
	InitObject('\0');		// key = NUL
}

// ���������� key�� ���������ʰ� �ܺο��� key�� �Է¹޾� �����ϴ� ������
WinSocketClient::WinSocketClient(unsigned char a_key)
{
	InitObject(a_key);
}

// ��ü �ı���
WinSocketClient::~WinSocketClient()
{
	// ����ϴ� ������ ����
	CloseSocket();
	// ������ ���ſ� ����ϴ� �޸𸮸� ����
	if (mp_net_body_data != NULL) {
		delete[] mp_net_body_data;
	}

	WSACleanup();		// ���� ���̺귯�� ��� ���� ���·� ����
}

// ��ü�� �ʱ�ȭ�ϴ� �Լ� (���������� ȣ��Ǵ� �Լ�)
void WinSocketClient::InitObject(unsigned char a_key)
{
	WSADATA temp;
	WSAStartup(0x0202, &temp);			// ���� ���̺귯���� ��� ���� ���·� ����

	mh_socket = INVALID_SOCKET;
	m_is_connected = 0;
	m_connect_msg_id = 26001;
	m_read_close_msg_id = 26002;
	mp_notify_wnd = NULL;

	m_key = a_key;
	mp_net_body_data = NULL;
	m_net_body_size = 0;
}

// ������ Packet Frame���� ���ϴ� �����͸� �����ϴ� �Լ�
void WinSocketClient::SendFrameData(char a_msg_id, const void* ap_data, int a_size)		// a_msg_id ���̵�� ap_data �ּҿ� a_size ������� ����
{
	// ������ ������ �������� �����ϱ� ���� �޸𸮸� �Ҵ� (+4byte�� ����޽����� ������)
	char* p_data = new char[a_size + 4];
	// ���� Ű ���� ����
	*p_data = m_key;
	// �޽��� ���̵� ����
	*(p_data + 1) = a_msg_id;
	// ������ ���� ������ ũ�⸦ ����
	*(unsigned short*)(p_data + 2) = a_size;
	// ������ ���� ������ ũ�⸦ ����
	memcpy(p_data + 4, ap_data, a_size);
	// mh_socket���� �����͸� a_size+4 ũ�⸸ŭ ����
	send(mh_socket, p_data, a_size + 4, 0);
	// ������ ���忡 ����� �޸𸮸� ����
	delete[] p_data;
}

// ������ ������ �õ��ϴ� �Լ�. ������ ������ ip�� port
// �׸��� ���� ����� �˷��� �޽��� ���̵�� �����Ͱ� ���ŵǾ��ų� ������ �����Ǿ��� ���� �޽��� ���̵� ����
void WinSocketClient::ConnectToServer(const TCHAR* ap_ip_address, int a_port, CWnd* ap_notify_wnd, int a_connect_id, int a_read_close_id)
{
	if (mh_socket == INVALID_SOCKET) {
		// ����� �޽��� ���̵� ����
		m_connect_msg_id = a_connect_id;
		m_read_close_msg_id = a_read_close_id;
		// �޽����� ������ �������� �ּ� ����
		mp_notify_wnd = ap_notify_wnd;

		// AF_INET �ּ� ü�踦 ����ϴ� TCP ����� ���� ����
		mh_socket = socket(AF_INET, SOCK_STREAM, 0);

		// IP �ּ� ü��, ���α׷� �ĺ� ��ȣ(��Ʈ ��ȣ)
		sockaddr_in addr_data = { AF_INET, htons(a_port), };
		// ap_ip_address �ּҸ� ����ϴ� ��Ʈ��ũ�� ����ϵ��� ����
		InetPton(AF_INET, ap_ip_address, &addr_data.sin_addr.s_addr);
		// ���� ������ �񵿱� ������� ó��
		// ���� ���� ����� ���� ah_notify_wnd ������� a_connect_id(26001) �޽����� ����
		WSAAsyncSelect(mh_socket, ap_notify_wnd->m_hWnd, a_connect_id, FD_CONNECT);
		// ������ ������ ����ǰ� ������ ����
		m_is_connected = 1;
		// ������ ������ �õ�
		// �񵿱� ��忡�� connect �Լ��� ���� ����� ���ö����� ������� �ʰ� �ٷ� ��������
		connect(mh_socket, (sockaddr*)&addr_data, sizeof(addr_data));
	}
}

// ��ſ� ����ϴ� ������ �����ϴ� �Լ�
void WinSocketClient::CloseSocket()
{
	if (mh_socket != INVALID_SOCKET) {
		closesocket(mh_socket);			// ������ �ݴ´�
		mh_socket = INVALID_SOCKET;		// �ٽ� ����� �� �ֵ��� �ʱ�ȭ
		m_is_connected = 0;				// ���� �ȵ����� ����
	}
}

// ������ ������ �����͸� ������ �� ����ϴ� �Լ�
int WinSocketClient::ReceiveData(char* ap_data, int a_size)
{
	int read_size, total_size = 0, retry_count = 0;
	// a_size ũ�⸸ŭ �� ���ŵ� ������ �ݺ�
	while (total_size < a_size) {
		// ���� ũ�⸸ŭ ������ �õ�
		read_size = recv(mh_socket, ap_data + total_size, a_size - total_size, 0);
		if (read_size == SOCKET_ERROR || read_size == 0) {		// �б� ����
			Sleep(10);		// 10ms ���
			retry_count++;		// ��õ� Ƚ�� ����
			if (retry_count > 300) break;			// 300ȸ ��õ��� �Ѿ�� �۾� �ߴ�
		}
		else {		// �б� �Ϸ�
			retry_count = 0;			// ��õ� Ƚ�� �ʱ�ȭ
			total_size += read_size;		// ���ŵ� �������� ũ�⸦ �ջ�
		}
	}
	return total_size;			// ������ ��ü ����Ʈ�� ����
}

// ������ ������ �� ������ ����� �о ó���ϴ� �Լ�
// 1: �������, 0: ���������
int WinSocketClient::ProcessHeaderInfo()
{
	unsigned char key;
	// ù ����Ʈ�� �ִ� key���� ����
	recv(mh_socket, (char*)&key, 1, 0);
	// key���� ������ key���� ��ġ���� ��
	if (key == m_key) {
		recv(mh_socket, (char*)&m_net_msg_id, 1, 0);
		recv(mh_socket, (char*)&m_net_body_size, 2, 0);
		return 1;		// key��ġ�ϸ� ����1
	}
	return 0;		// key�� �ٸ��� ����0
}

// ���ŵ� �����͸� ������ ������ �д� �Լ� (����� �ٵ� ��� ����)
int WinSocketClient::BeginNetworkProcess()
{
	// �����б� �� ��õ��б⸦ ���� FD_READ �̺�Ʈ�� �����ϰ� �ٽ� �񵿱⸦ ���� (�ߺ����� ����)
	WSAAsyncSelect(mh_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_CLOSE);

	// ���� ����� �д´�.
	int state = ProcessHeaderInfo();
	// ��������̰� Body�� ũ�Ⱑ 0���� ũ�ٸ� Body �����͵� �߰��� ����
	if (state && m_net_body_size > 0) {
		// Body ������ ���� �޸𸮸� �Ҵ�
		mp_net_body_data = new char[m_net_body_size];
		// Body �����͸� ����. ���� ����� state������ ����
		state = m_net_body_size == ReceiveData(mp_net_body_data, m_net_body_size);
	}
	return state;		// ���� ���¸� ����
}

// ���� �۾��� �Ϸ�Ǿ��� �� ȣ��Ǵ� �Լ� (FD_READ �缳�� �� �޸� ����)
void WinSocketClient::EndNetworkProcess()
{
	// �ٽ� ������ ���� ���¸� Ȯ���� �� �ֵ��� FD_READ �̺�Ʈ�� �缳��
	WSAAsyncSelect(mh_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_READ | FD_CLOSE);
}

// ���� ���� �񵿱� �޽����� ó���ϴ� �Լ�
void WinSocketClient::MessageProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == m_connect_msg_id) {		// ���� ���� ����� ���� ���
		if (WSAGETSELECTERROR(lParam)) CloseSocket();
		else {
			m_is_connected = 2;		// ���� ���·� ����
			// ���� ���Ͽ� �����Ͱ� ���ŵǰų� ���������Ǿ����� �޽��� �߻��ϵ��� �񵿱� ����
			WSAAsyncSelect(mh_socket, mp_notify_wnd->m_hWnd, m_read_close_msg_id, FD_READ | FD_CLOSE);
		}
		// �� Ŭ������ ����ϴ� ����� �߰��� �ؾ��� ���� �ִٸ� ó���ϰ� ���ش�.
		ConnectedProcess();
	}
	else if (message == m_read_close_msg_id) {
		if (WSAGETSELECTEVENT(lParam) == FD_READ) {		// ������ ����
			if (BeginNetworkProcess()) {			// ����� ����
				// ���������� �޽����� ó���ߴٸ� ������ �۾�(FD_READ �缳�� ����)�� ȣ���Ѵ�.
				if (ProcessNetMessage()) EndNetworkProcess();

				// ������ ���ſ� ����ϴ� �޸𸮸� ����
				if (mp_net_body_data != NULL) {
					delete[] mp_net_body_data;
					mp_net_body_data = NULL;
				}
			}
			else {			// Key���� ��ġ���� �ʾƼ� �������� ������ ���´�.
				CloseSocket();		// ������ ����
				ClosedProcess(1);		// �߰����� �۾��� �� �� �ִ� �Լ� (������ ���� ����)
			}
		}
		else {		// FD_CLOSE ������ ������ ������
			CloseSocket();			// ���� ����
			ClosedProcess(0);		// �߰����� �۾��� �� �� �ִ� �Լ� (���� ����)
		}
	}
}