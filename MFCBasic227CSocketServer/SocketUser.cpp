// SocketUser.cpp : implementation file
//

#include "pch.h"
#include "MFCBasic227CSocketServer.h"
#include "SocketUser.h"


// SocketUser

SocketUser::SocketUser()
{
}

SocketUser::~SocketUser()
{
}


// SocketUser member functions


void SocketUser::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	// Send() <-> Receive()
	int data;
	Receive(&data, sizeof(int));
	AfxGetMainWnd()->SetDlgItemInt(IDC_EDIT1, data);			// 현재 대화상자의 주소 속에서 Edit1

	data = 1;
	Send(&data, sizeof(int));

	CSocket::OnReceive(nErrorCode);
}


void SocketUser::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	ShutDown(2);				// 전송 강제종료
	Close();							// 접속해제

	CSocket::OnClose(nErrorCode);
}
