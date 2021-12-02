#pragma once

// SocketUser command target

class SocketUser : public CSocket
{
public:
	SocketUser();
	virtual ~SocketUser();

	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


