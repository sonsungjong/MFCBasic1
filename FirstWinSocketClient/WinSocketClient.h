
#ifndef _WIN_SOCKET_CLIENT_H_
#define _WIN_SOCKET_CLIENT_H_
// Socket���� �Լ� ����� ���� ������ϰ� ���̺귯���� ����
#include <WinSock2.h>

class WinSocketClient
{
protected:
	SOCKET mh_socket;		// ����� ������ �ڵ�
	char m_is_connected;		// �������� ���� ���� (0:������, 1: ���� �õ� ��, 2: ����)
	
	int m_connect_msg_id;		// ������ �� ����� �޽���ID
	int m_read_close_msg_id;		// �����Ͱ� ���ŵǰų� ���� ����Ǿ����� ����� �޽���ID

	unsigned char m_key;					// key���� ������ ����
	unsigned char m_net_msg_id;			// �޽���ID
	unsigned short m_net_body_size;	// Body �������� ũ��
	char* mp_net_body_data;				// Body �������� ����
	CWnd* mp_notify_wnd;					// Socket �޽����� ���� ������ ��ü�� �ּ�

public:
	// �⺻ ������ (key == 0)
	WinSocketClient();
	// �ܺο��� �����ڸ� ���� key���� ������ �� �ֵ��� key���� �Է¹���
	WinSocketClient(unsigned char a_key);
	// ��ü �ı���
	virtual ~WinSocketClient();

	// �ش� ��ü�� �ʱ�ȭ�ϴ� �Լ�, ���������� ȣ��Ǵ� �Լ�
	void InitObject(unsigned char a_key);

	// ������ ���� ���¸� �˷��ִ� �Լ� (0: ������, 1: ����)
	int IsConnect() { return m_is_connected == 2; }
	// ������ Packet Frame���� ���ϴ� �����͸� �����ϴ� �Լ�
	void SendFrameData(char a_msg_id, const void* ap_data, int a_size);
	// ������ ������ �õ��ϴ� �Լ�, ������ ������ �����ǿ� ��Ʈ
	// ���� ���ӿ� ���� ����� �˷��� �޽��� ���̵�� �����Ͱ� ���ŵǾ��ų� ������ �����Ǿ��� ���� �޽��� ���̵� ����
	void ConnectToServer(const TCHAR* ap_ip_address, int a_port, CWnd* ap_notify_wnd, int a_connect_id = 26001, int a_read_close_id = 26002);
	// ����� ����ϴ� ������ �����ϴ� �Լ�
	void CloseSocket();
	// ������ ������ �����͸� ������ �� ����ϴ� �Լ�
	int ReceiveData(char* ap_data, int a_size);
	// ���ŵ� �����Ϳ��� ������ ����� �о ó���ϴ� �Լ� (1 : �������, 0: ���������)
	int ProcessHeaderInfo();
	// ���ŵ� �����͸� ������ ������ �д� �Լ� (����� �ٵ� ��� ����)
	int BeginNetworkProcess();
	// ���� �۾��� �Ϸ�Ǿ����� ȣ���ϴ� �Լ� (FD_READ �缳�� �� �޸� ����)
	void EndNetworkProcess();
	// ���� ���� �񵿱� �޽����� ó���ϴ� �Լ�
	void MessageProc(UINT message, WPARAM wParam, LPARAM lParam);
	// ������ ������ ����� ������ ȣ��Ǵ� �Լ�
	// ���� ����� ������ �� �߰� �۾��� �ϰ� �ʹٸ� ConnectedProcess()�Լ��� ������
	virtual void ConnectedProcess() {}
	// ProcessNetMessage()�Լ��� �������ؼ� ���ŵ� �����͸���� ó���� ������ �۾�
	// ���������� �۾��� ������ 1�� ��ȯ�ϰ� �����ϸ� 0�� ��ȯ
	// 0�� ��ȯ�Ǹ� FD_READ �缳���� ���� ����. (������ ���ŵǸ� 0�� ��ȯ)
	virtual int ProcessNetMessage() { return 1; }
	// ������ ������ ��쿡 ȣ��Ǵ� �Լ�. a_error_flag���� 1�̸� ������ �߻��ؼ� ����
	// 0�̸� �������� ������ ����
	// ������ �����Ǿ��� �� � �۾��� �ϰ� �ʹٸ� ClosedProcess()�Լ��� �������ؼ� �۾�
	virtual void ClosedProcess(int a_error_flag){}
};

#endif


