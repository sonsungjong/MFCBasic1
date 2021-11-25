// MFCServer.cpp : implementation file
//

#include "pch.h"
#include "MFCBasic226CSocketServer.h"
#include "MFCServer.h"


// MFCServer

MFCServer::MFCServer()
{
}

MFCServer::~MFCServer()
{
}


// MFCServer member functions

// 클라이언트가 연결하면 작동하는 함수
void MFCServer::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	// Listen용 소켓에서 User개별용 소켓으로 넘겨줘야함
	Accept(m_user);

	CSocket::OnAccept(nErrorCode);
}
