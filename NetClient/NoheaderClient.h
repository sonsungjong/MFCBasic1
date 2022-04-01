#ifndef _NOHEADER_CLIENT_H_
#define _NOHEADER_CLIENT_H_

#define MAX_SIZE				32767

#define RECV_DATA				WM_APP + 2100
#define CONNECTED				WM_APP + 2101
#define DISCONNECTED			WM_APP + 2102

class NoheaderClient
{
protected:
	SOCKET mh_socket;					// ����� ���� ����
	BOOL m_is_connected;					// �������� ���� ����
	int m_connect_msg_id, m_read_close_msg_id;

	int m_nSoketIdx;			// ���� �ε��� ����
	unsigned char m_net_msg_id;						// �޽��� ID
	unsigned short m_net_size;					// ������ ũ��
	char* mp_net_data;						// ������ ����
	CWnd* mp_notify_wnd;					// ���� �޽����� ���� �������� �ּ�

public:
	NoheaderClient();
	virtual ~NoheaderClient();

	// �ʱ�ȭ, ����ȣ���Լ�
	void InitObject();
	int IsConnect() { return m_is_connected == 2; }
	// ������ ����
	void SendFrameData(char a_msg_id, const void* ap_data, int a_size);
	// connect�õ�, IP�� PORT, ���� ��� �ȳ��� ���� �ߵ��ϴ� �޽���ID, ���� �Ǵ� ���������� �ߵ��ϴ� �޽���ID
	void ConnectToServer(const TCHAR* ap_ip_address, int a_port, CWnd* ap_notify_wnd, int a_connect_id, int a_read_close_id);
	// ����ϴ� ��������
	void CloseSocket();
	// ������ �޽����� ����
	int RecvData(char* ap_data, int a_size);
	// ���ŵ� �����͸� �����Ӵ����� �б�
	int BeginNetworkProcess();
	// ������ �񵿱� �޽����� ó���ϴ� �Լ�
	
	
	// ���Ӱ���� ���� ȣ���Լ� (���Ӱ���� ���� ���۾��� ���� �������� �� ����)
	virtual void ConnectedProcess() {}
	// ������ ���Ž� ó���Լ� (���Ű���� ���� ���۾��� ���� �������� �� ����), 1:����, 0: ����
	virtual int ProcessNetMessage() { return 1; }
	// ���� ������ ó���Լ� (���� ���������� ���۾��� ���� �������� �� ����), 1 : ��ü�����߻�, 0: �������� ����
	virtual void ClosedProcess(int a_error_flag){}
};

#endif