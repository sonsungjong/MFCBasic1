#pragma once
#include "MFCServerUser.h"

// MFCServer command target

class MFCServer : public CSocket
{
protected:
	// �� ������ ����
	MFCServerUser m_user;

public:
	MFCServer();
	virtual ~MFCServer();
	virtual void OnAccept(int nErrorCode);
};


