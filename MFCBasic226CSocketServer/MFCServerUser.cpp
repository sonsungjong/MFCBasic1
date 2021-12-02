// MFCServerUser.cpp : implementation file
//

#include "pch.h"
#include "MFCBasic226CSocketServer.h"
#include "MFCServerUser.h"


// MFCServerUser

MFCServerUser::MFCServerUser()
{
}

MFCServerUser::~MFCServerUser()
{
}


// MFCServerUser member functions


void MFCServerUser::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	// Send() <-> OnReceive()
	int data;
	Receive(&data, sizeof(int));				// Send를 받는 함수
	//AfxGetMainWnd();				// 현재 대화상자의 주소
	AfxGetMainWnd()->SetDlgItemInt(IDC_VALUE_EDIT, data);				// 현재 대화상자의 주소

	CSocket::OnReceive(nErrorCode);
}


void MFCServerUser::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	ShutDown(2);			// 데이터를 전송 또는 수신 중이라면 중단시키는 함수
	Close();						// 접속해제 후 정리하는 함수

	CSocket::OnClose(nErrorCode);
}
