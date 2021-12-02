// SocketClient.cpp : implementation file
//

#include "pch.h"
#include "MFCBasic227CSocketClient.h"
#include "SocketClient.h"
#include "MFCBasic227CSocketClientDlg.h"

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
	DWORD temp_size;
	if (IOCtl(FIONREAD, &temp_size)) {
		if (m_flag_header) {
			if (temp_size >= sizeof(unsigned int)) {
				Receive(&m_data_size, sizeof(unsigned int));
				m_flag_header ^= m_flag_header;
			}
		}
		else {
			if (temp_size >= m_data_size) {
				TCHAR* p_string = new TCHAR[m_data_size];
				Receive(p_string, m_data_size);

				((CMFCBasic227CSocketClientDlg*)AfxGetMainWnd())->AddEventString((TCHAR*)p_string);

				delete[] p_string;
				m_flag_header = !m_flag_header;
			}
		}
	}
	else {
		((CMFCBasic227CSocketClientDlg*)AfxGetMainWnd())->AddEventString(_T("수신 문제 발생"));
	}

	CSocket::OnReceive(nErrorCode);
}
