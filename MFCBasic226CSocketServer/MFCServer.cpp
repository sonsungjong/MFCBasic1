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

// Ŭ���̾�Ʈ�� �����ϸ� �۵��ϴ� �Լ�
void MFCServer::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	// Listen�� ���Ͽ��� User������ �������� �Ѱ������
	Accept(m_user);

	CSocket::OnAccept(nErrorCode);
}
