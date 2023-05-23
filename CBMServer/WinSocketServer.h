#ifndef _WIN_SOCKET_SERVER_H_
#define _WIN_SOCKET_SERVER_H_

#include <WinSock2.h>

#define MAX_USER_COUNT				2000

struct UserData
{
	SOCKET h_socket;					// Ŭ���̾�Ʈ ���� ����
	TCHAR ip_address[16];			// Ŭ���̾�Ʈ ������
};

class WinSocketServer
{
public:
	// �⺻ ������
	WinSocketServer();
	WinSocketServer(unsigned char a_key);				// ����Ű 1byte
	virtual ~WinSocketServer();

	// �ʱ�ȭ �Լ�
	void InitObject(unsigned char a_key);
	inline UserData* GetUserData() { return m_users; }
	inline UserData* GetUserData(int a_index) { return m_users + a_index; }
	UserData* GetUserData(SOCKET ah_socket);					// �������� �����˻�

protected:
	UserData m_users[MAX_USER_COUNT];					// �ý��� ����� ��ü ����
	SOCKET mh_listen_socket;										// ���ӿ� ��������
	int m_accept_msg_id;											// ���� �޽��� ��ȣ
	int m_read_close_msg_id;										// ���� �� ���� �޽��� ��ȣ

	UserData* mp_net_user;					// �����͸� ������ Ŭ���̾�Ʈ ����
	UserData m_temp_user_data;				// ���� �������� ����
	CWnd* mp_notify_wnd;						// ����ó�� ������ ����

	// ���ŵ����� ����
	unsigned char m_key;				// 1byte (����Ű)
	unsigned char m_net_msg_id;				// 1byte (ID)
	unsigned short m_net_body_size;				// 2byte (Body ������)
	char* mp_net_body_data;							// (Body)

public:
	void StartListenService(const wchar_t* ap_ip_address, int a_port, CWnd* ap_notify_wnd, int a_accept_id = 25001, int a_read_close_id = 25002);			// ���� ����
	void DestroyClientSockets();			// ���� ����
	void SendFrameData(SOCKET ah_socket, char a_msg_id, const void* ap_data, int a_size);			// �۽�
	void BroadcastFrameData(char a_msg_id, const void* ap_data, int a_size);				// ��� Ŭ���̾�Ʈ���� �۽�
	UserData* ProcessAccept();					// ���� ���
	int ReceiveData(SOCKET ah_socket, char* ap_data, int a_size);				// ����
	
	void MessageProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual int ProcessHeaderInfo(SOCKET ah_socket);					// ��� ���� ó��
	virtual int BeginNetworkProcess(SOCKET ah_socket);				// ���� �� ����
	virtual int EndNetworkProcess();							// ���� �а� �� ó��
	virtual int AddNewUser(SOCKET ah_new_socket, const wchar_t* ap_ip_address);				// ���� ���
	virtual void CloseSocket(SOCKET ah_socket, UserData* ap_close_user);				// ����� ����

	// ������ ����
	virtual void AcceptUserProc(UserData* ap_user_data) {}				// ���� �� �߰��۾�
	virtual int ProcessNetMessage() { return 1; }					// ���� ������ ��ó��
	virtual void CloseUserProc(UserData* ap_user_data, int a_error_flag) {}					// ���� ������ a_error_flag == 0:����, 1:�����߻�
};

#endif