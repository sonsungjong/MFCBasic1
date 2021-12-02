#pragma once
#include "SocketUser.h"

// SocketServer command target

class SocketServer : public CSocket
{
protected:
	// 개개인 보관용 소켓 객체화
	SocketUser m_user;
public:
	SocketServer();
	virtual ~SocketServer();

	virtual void OnAccept(int nErrorCode);
};


