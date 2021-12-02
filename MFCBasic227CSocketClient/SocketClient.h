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


// 서버 : 2중소켓으로 구성
// 클라이언트 : 소켓 하나면 됨