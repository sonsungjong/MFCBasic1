#ifndef _WIN_SOCKET_SERVER_H_
#define _WIN_SOCKET_SERVER_H_

// Socket �Լ� ����� ���� ����� ���̺귯�� ����
#include <WinSock2.h>

#define MAX_USER_COUNT			2000			// ���� ������ �ִ� Ŭ���̾�Ʈ ��

// Ŭ���̾�Ʈ ������ ���� ������ ����ü
struct UserData {
	SOCKET h_socket;						// ���� Ŭ���̾�Ʈ�� ����� �����ڵ�
	TCHAR ip_address[16];				// ������ Ŭ���̾�Ʈ �ּ�
};

class WinSocketServer
{
protected:
	// �ý��� ����� ��ü ����
	UserData m_users[MAX_USER_COUNT];
	// Ŭ���̾�Ʈ ���ӿ� ����� Listen ����
	SOCKET mh_listen_socket;
	// �񵿱� �޽��� ��ȣ (����, �б�, ����)
	int m_accept_msg_id, m_read_close_msg_id;

	// ���� ó���� ����ǰ� �ִ� ���� ������ ����
	unsigned char m_key;						// ��ȿ Ŭ���̾�Ʈ ������ ���� key��
	unsigned char m_net_msg_id;				// �޽��� ID
	unsigned short m_net_body_size;		// Body ������ ũ��
	char* mp_net_body_data;					// Body ������ ����
	UserData* mp_net_user;					// �����͸� ������ Ŭ���̾�Ʈ�� ����

	UserData m_temp_user_data;				// ������������ ���� ��� (���� ����� ���� ��ó��)
	CWnd* mp_notify_wnd;

public:
	// �⺻ ������ (�⺻ key�� 27)
	WinSocketServer();
	// key���� �޾Ƽ� ������ �� �ִ� ������
	WinSocketServer(unsigned char a_key);
	// ��ü �ı���
	virtual ~WinSocketServer();

	// ��ü�� �ʱ�ȭ�ϱ� ���� �Լ�, �����ڿ��� ȣ��
	void InitObject(unsigned char a_key);
	// ������ �����ϴ� ����� ����� ���� �ּҸ� ��ȯ�ϴ� �Լ�
	inline UserData* GetUserData() {
		return m_users;
	}

	// Listen ���񽺸� ������ �� ����ϴ� �Լ�
	// ���񽺸� ������ IP�� port�� �񵿱�޽����� ���� ������ �ڵ�� �񵿱⿡ ����� �޽���ID�� �Ű������� ����
	// �񵿱� �޽����� ����� ID�� ������ 25001, �б�� ����� 25002 �� �⺻���� �����س���
	void StartListenService(const wchar_t* ap_ip_address, int a_port, CWnd* ap_notify_wnd, int a_accept_id = 25001, int a_read_close_id = 25002);
	// ������ ������ ��� Ŭ���̾�Ʈ ������ �����ϰ� Listen ���ϵ� �����ϴ� �Լ�
	void DestroyClientSockets();
	// Ŭ���̾�Ʈ�� 1���� ��Ʈ��ũ ������ �����͸� �ϳ� ����
	// ������ ���� : "Key, Message ID, Body size, BVody Data"
	void SendFrameData(SOCKET ah_socket, char a_msg_id, const void* ap_data, int a_size);
	// ������ ��� Ŭ���̾�Ʈ���� ��Ʈ��ũ ������ ����Ʈ�� �����Ѵ�.
	void BroadcastFrameData(char a_msg_id, const void* ap_data, int a_size);
	// ���ο� ����ڰ� �������� ��, �� �Լ��� ȣ���ϸ� ������� ������ ó��
	UserData* ProcessAccept();
	// ���� �ڵ��� ������ �ش� ���� �ڵ��� ����� m_users �迭�� �׸� �ּҸ� ��� �Լ�
	UserData* GetUserData(SOCKET ah_socket);
	// �ѹ��� �ޱ� ����� ũ���� ��Ʈ��ũ �޽����� ��õ��ϸ鼭 ���� �� �ֵ��� �ϴ� �Լ�
	// ��ȯ���� a_size�� ��ġ���� ������ �߰��� ������ �߻��� ��
	int ReceiveData(SOCKET ah_socket, char* ap_data, int a_size);
	// m_users �迭���� a_index ��ġ�� �ִ� �׸��� �ּҸ� ��� �Լ� (Ư�� ��ġ�� �ִ� �ּҸ� ã����)
	inline UserData* GetUserData(int a_index) {
		return m_users + a_index;
	}

	// ��Ʈ��ũ �޽������� ��� ������ ó���ϴ� �Լ�
	virtual int ProcessHeaderInfo(SOCKET ah_socket);
	// ��Ʈ��ũ�� �����Ͱ� ���ŵ� ���, header�� body �����͸� �о �۾��� ������ �� �ִ� �Լ�
	// FD_READ �̺�Ʈ�� ���� 25002 �޽����� �߻������� ���
	virtual int BeginNetworkProcess(SOCKET ah_socket);
	// FD_READ �̺�Ʈ�� ���� �߻��� 25002 �޽��� �۾��� �Ϸ�Ǿ��� �� ȣ��,
	// BeginNetworkProcess() ���� ���� �������� �����ϴ� �۾�
	virtual int EndNetworkProcess();
	// ���ο� ����� ����ó��
	// m_users�迭�� h_socket���� INVALID_SOCKET�� �׸� ���ο� ����� ������ ����
	virtual int AddNewUser(SOCKET ah_new_socket, const wchar_t* ap_ip_address);
	// FD_CLOSE�� ���� 25002 �޽����� �߻��Ͽ� ���� ������ ������ �� ���
	// Ư�� ����ڸ� �����ų �� ����ص� ��
	// �ι�° ���� ap_close_user�� ������ ������ ������� ������ �����
	// UserData ����ü ������ �����ؼ� �ش� ������ �ּҸ� �����ؾ� ������ ���� �� ����
	virtual void CloseSocket(SOCKET ah_socket, UserData* ap_close_user);
	

	// ��ӹ��� ������ �������ؼ� ���
	// ���ο� Ŭ���̾�Ʈ ���� �� �߰� �۾��� �ʿ��ϸ� AcceptUserProc()�� ���
	virtual void AcceptUserProc(UserData* ap_user_data) {}
	// ProcessNetMessage() : ���ŵ� �����͸� ��� ó���� ������ ������
	// ������ return 1, ���н� return 0
	// return 0�� �ϸ� FD_READ �缳�� �ȵ� (���� ���Ž� 0��ȯ)
	virtual int ProcessNetMessage() { return 1; }
	// CloseUserProc() : ���� ������ ȣ��, ������ �����Ǿ��� �� �߰��۾��� �������ϸ� ��
	// a_error_flag ���� 1�̸� ������ �߻��ؼ� ������ ���̰� 0�̸� �������� ������ ������Ų ��
	virtual void CloseUserProc(UserData* ap_user_data, int a_error_flag) {}


	void MessageProc(UINT message, WPARAM wParam, LPARAM lParam);
};

#endif