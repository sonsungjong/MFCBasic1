#pragma once

// SocketClient command target

class SocketClient : public CSocket
{
protected:
	char m_flag_header = 1;
	unsigned int m_data_size;

public:
	SocketClient();
	virtual ~SocketClient();
	virtual void OnReceive(int nErrorCode);
};


// ���� : 2�߼������� ����
// Ŭ���̾�Ʈ : ���� �ϳ��� ��