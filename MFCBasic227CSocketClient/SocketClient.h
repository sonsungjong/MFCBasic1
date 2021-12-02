#pragma once

// SocketClient command target

class SocketClient : public CSocket
{
public:
	SocketClient();
	virtual ~SocketClient();
	virtual void OnReceive(int nErrorCode);
};


// 서버 : 2중소켓으로 구성
// 클라이언트 : 소켓 하나면 됨