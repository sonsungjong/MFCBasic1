// SocketServer.cpp : implementation file
//

#include "pch.h"
#include "MFCBasic227CSocketServer.h"
#include "SocketServer.h"


// SocketServer

SocketServer::SocketServer()
{
}

SocketServer::~SocketServer()
{
}


// SocketServer member functions

// 클라이언트 접속 시도
void SocketServer::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	Accept(m_user);

	CSocket::OnAccept(nErrorCode);
}
