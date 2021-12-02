// SocketUser.cpp : implementation file
//

#include "pch.h"
#include "MFCBasic227CSocketServer.h"
#include "SocketUser.h"
#include "MFCBasic227CSocketServerDlg.h"

// SocketUser

SocketUser::SocketUser(CObList* ap_user_list)
{
	mp_user_list = ap_user_list;				// �����ڷ� �Ѿ�� �ּҸ� ����
}

SocketUser::~SocketUser()
{
}


// SocketUser member functions


void SocketUser::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	// Send() <-> Receive()
	unsigned int data_size;
	Receive(&data_size, sizeof(unsigned int));

	TCHAR* p_string = new TCHAR[data_size];
	Receive(p_string, data_size);								// �ѹ��� ������ �ȉ��� ��� ����ó��

	((CMFCBasic227CSocketServerDlg*)AfxGetMainWnd())->AddEventString(p_string);			// ���� ��ȭ������ �ּ� �ӿ��� Edit1

	delete[] p_string;
	CSocket::OnReceive(nErrorCode);
}


void SocketUser::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	ShutDown(2);				// ���� ��������
	Close();							// ��������

	SocketUser* p = NULL;
	POSITION position = mp_user_list->GetHeadPosition();
	POSITION check_position;
	while (position != NULL) {				// ��� ���� ��
		check_position = position;
		p = (SocketUser*)mp_user_list->GetNext(position);
		if (p == this) {
			mp_user_list->RemoveAt(check_position);
			break;
		}
	}
	if (p != NULL) {
		delete p;
	}
	CSocket::OnClose(nErrorCode);
}
