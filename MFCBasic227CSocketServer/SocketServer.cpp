// SocketServer.cpp : implementation file
//

#include "pch.h"
#include "MFCBasic227CSocketServer.h"
#include "SocketServer.h"


// SocketServer

SocketServer::SocketServer()
{
}

// 객체파괴자에서 모두 delete
SocketServer::~SocketServer()
{
	SocketUser* p;
	POSITION position = m_user_list.GetHeadPosition();				// 연결리스트 가장 앞부분의 값을 얻어옴
	while (position != NULL) {
		p = (SocketUser*)m_user_list.GetNext(position);				// 위치는 현재노드의 소켓객체를 반환하고 다음노드로 이동
		delete p;								// 연결리스트 객체들 모두 삭제
	}
}


// SocketServer member functions

// 클라이언트 접속 시도
void SocketServer::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	SocketUser* p_user = new SocketUser(&m_user_list);					// 들어올때마다 동적할당
	m_user_list.AddTail(p_user);									// 연결리스트 끝부분에 추가

	Accept(*p_user);					// 역참조해서 객체의 값을 Accept

	// delete하면 안됨
	CSocket::OnAccept(nErrorCode);
}
