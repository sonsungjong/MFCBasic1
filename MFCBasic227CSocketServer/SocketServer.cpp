// SocketServer.cpp : implementation file
//

#include "pch.h"
#include "MFCBasic227CSocketServer.h"
#include "SocketServer.h"


// SocketServer

SocketServer::SocketServer()
{
}

// ��ü�ı��ڿ��� ��� delete
SocketServer::~SocketServer()
{
	SocketUser* p;
	POSITION position = m_user_list.GetHeadPosition();				// ���Ḯ��Ʈ ���� �պκ��� ���� ����
	while (position != NULL) {
		p = (SocketUser*)m_user_list.GetNext(position);				// ��ġ�� �������� ���ϰ�ü�� ��ȯ�ϰ� �������� �̵�
		delete p;								// ���Ḯ��Ʈ ��ü�� ��� ����
	}
}


// SocketServer member functions

// Ŭ���̾�Ʈ ���� �õ�
void SocketServer::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	SocketUser* p_user = new SocketUser(&m_user_list);					// ���ö����� �����Ҵ�
	m_user_list.AddTail(p_user);									// ���Ḯ��Ʈ ���κп� �߰�

	Accept(*p_user);					// �������ؼ� ��ü�� ���� Accept

	// delete�ϸ� �ȵ�
	CSocket::OnAccept(nErrorCode);
}
