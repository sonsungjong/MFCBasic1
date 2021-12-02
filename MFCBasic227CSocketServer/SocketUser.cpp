// SocketUser.cpp : implementation file
//

#include "pch.h"
#include "MFCBasic227CSocketServer.h"
#include "SocketUser.h"
#include "MFCBasic227CSocketServerDlg.h"

// SocketUser

SocketUser::SocketUser(CObList* ap_user_list)
{
	mp_user_list = ap_user_list;				// 생성자로 넘어온 주소를 저장
}

SocketUser::~SocketUser()
{
}


// SocketUser member functions


void SocketUser::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	// Send() <-> Receive()
	DWORD temp_size;
	if (IOCtl(FIONREAD, &temp_size)) {						// temp_size의 크기 확인
		if (m_flag_header) {
			if (temp_size >= sizeof(unsigned int)) {
				Receive(&m_data_size, sizeof(unsigned int));
				m_flag_header ^= m_flag_header;
			}
		}else{
			if(temp_size >= m_data_size){
				char* p_string = new char[m_data_size + sizeof(unsigned int)];
				*(int*)p_string = m_data_size;
				Receive(p_string+sizeof(unsigned int), m_data_size);								// 한번에 전송이 안됬을 경우 예외처리

				((CMFCBasic227CSocketServerDlg*)AfxGetMainWnd())->AddEventString((TCHAR*)(p_string+sizeof(unsigned int)));			// 현재 대화상자의 주소 속에서 Edit1

				SocketUser* p = NULL;
				POSITION position = mp_user_list->GetHeadPosition();
				while (position != NULL) {
					p = (SocketUser*)mp_user_list->GetNext(position);
					p->Send(p_string, m_data_size + sizeof(unsigned int));
				}

				delete[] p_string;
				m_flag_header = !m_flag_header;
			}
		}
	}else {
		((CMFCBasic227CSocketServerDlg*)AfxGetMainWnd())->AddEventString(_T("수신에 문제 발생"));
	}

	CSocket::OnReceive(nErrorCode);
}


void SocketUser::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	ShutDown(2);				// 전송 강제종료
	Close();							// 접속해제

	SocketUser* p = NULL;
	POSITION position = mp_user_list->GetHeadPosition();
	POSITION check_position;
	while (position != NULL) {				// 모든 노드와 비교
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
