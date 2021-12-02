#pragma once

// SocketUser command target

class SocketUser : public CSocket
{
protected:
	CObList* mp_user_list;					// ���������� ���Ḯ��Ʈ �ּҸ� �����ڷ� �޾Ƽ� �����ϴ� Ŭ���̾�Ʈ�� �����ϱ�
	char m_flag_header = 1;				// ����� ó���� ��Ȳ���� �˷��ִ� �÷���
	unsigned int m_data_size;

public:
	SocketUser(CObList* ap_user_list);
	virtual ~SocketUser();

	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


