#pragma once
#include "MFCServerUser.h"

// MFCServer command target

class MFCServer : public CSocket
{
protected:
	// 각 유저용 소켓
	MFCServerUser m_user;

public:
	MFCServer();
	virtual ~MFCServer();
	virtual void OnAccept(int nErrorCode);
};


