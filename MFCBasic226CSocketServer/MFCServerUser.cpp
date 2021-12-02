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
	Receive(&data, sizeof(int));				// Send�� �޴� �Լ�
	//AfxGetMainWnd();				// ���� ��ȭ������ �ּ�
	AfxGetMainWnd()->SetDlgItemInt(IDC_VALUE_EDIT, data);				// ���� ��ȭ������ �ּ�

	CSocket::OnReceive(nErrorCode);
}


void MFCServerUser::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	ShutDown(2);			// �����͸� ���� �Ǵ� ���� ���̶�� �ߴܽ�Ű�� �Լ�
	Close();						// �������� �� �����ϴ� �Լ�

	CSocket::OnClose(nErrorCode);
}
