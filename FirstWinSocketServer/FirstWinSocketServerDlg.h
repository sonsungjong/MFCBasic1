// FirstWinSocketServerDlg.h : header file
//

#pragma once
#include "WinSocketServer.h"

//#define MAX_USER_COUNT			2000		// ������ ���� ������ �ִ� Ŭ���̾�Ʈ ��

class MyServerSocket : public WinSocketServer
{
// �������̵�
public:
	// ���ο� Ŭ���̾�Ʈ�� ���ӵǾ��� �� ȣ��
	virtual void AcceptUserProc(UserData* ap_user_data);
	// �޽��� ���� �� �۾��� ����
	virtual int ProcessNetMessage();
	// Ŭ���̾�Ʈ ���� ����
	virtual void CloseUserProc(UserData* ap_user_data, int a_error_flag);
};

/*
// 1���� Ŭ���̾�Ʈ ������ ������ ����ü
struct UserData {
	SOCKET h_socket;				// ���� Ŭ���̾�Ʈ�� ����� ���� �ڵ�
	wchar_t ip_address[16];		// ������ Ŭ���̾�Ʈ�� �ּ�
};
*/

// CFirstWinSocketServerDlg dialog
class CFirstWinSocketServerDlg : public CDialogEx
{
private:
	MyServerSocket m_server_socket;			// ������ ���� ��ü ����
protected:
	const wchar_t* ipconfig = L"192.168.12.21";		// �� IP
	const int thisPort = 1900;										// �ش� port
	/*
	SOCKET mh_listen_socket;		// Ŭ���̾�Ʈ ���� ó���� �� ����� ����
	UserData m_users[MAX_USER_COUNT];		// ������ ������ ��ü ����� ����
	*/
	// SOCKET mh_client_socket;		// �� ���� Ŭ���̾�Ʈ�� ������ ���
// Construction
public:
	CFirstWinSocketServerDlg(CWnd* pParent = nullptr);	// standard constructor

	// ����Ʈ �ڽ��� �̺�Ʈ �α� �߰�
	void AddEventString(const wchar_t* ap_string)
	{
		int index = m_event_list.InsertString(-1, ap_string);
		m_event_list.SetCurSel(index);
	}

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIRSTWINSOCKETSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_event_list;
	afx_msg void OnDestroy();
	afx_msg void OnLbnSelchangeEventList();
protected:
	afx_msg LRESULT OnAcceptProc(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSocketMessage(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedOk();
	int ReceiveData(SOCKET ah_socket, char* ap_data, int a_size);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
