#pragma once
#include "SocketUser.h"

// SocketServer command target

class SocketServer : public CSocket
{
protected:
	// ������ ������ ���� ��üȭ
	SocketUser m_user;
public:
	SocketServer();
	virtual ~SocketServer();

	virtual void OnAccept(int nErrorCode);
};


