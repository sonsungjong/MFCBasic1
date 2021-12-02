// SocketClient.cpp : implementation file
//

#include "pch.h"
#include "MFCBasic227CSocketClient.h"
#include "SocketClient.h"


// SocketClient

SocketClient::SocketClient()
{
}

SocketClient::~SocketClient()
{
}


// SocketClient member functions


void SocketClient::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	// 서버가 주는 데이터 받아오기
	int data;
	Receive(&data, sizeof(int));
	AfxGetMainWnd()->SetDlgItemInt(IDC_EDIT1, data);

	CSocket::OnReceive(nErrorCode);
}
