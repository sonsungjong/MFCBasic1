#pragma once

// MFCServerUser command target

class MFCServerUser : public CSocket
{
public:
	MFCServerUser();
	virtual ~MFCServerUser();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


