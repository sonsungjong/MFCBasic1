#pragma once

// SocketClient command target

class SocketClient : public CSocket
{
public:
	SocketClient();
	virtual ~SocketClient();
	virtual void OnReceive(int nErrorCode);
};


// ���� : 2�߼������� ����
// Ŭ���̾�Ʈ : ���� �ϳ��� ��