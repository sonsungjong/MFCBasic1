
// FirstWinSocketServerDlg.h : header file
//

#pragma once

// CFirstWinSocketServerDlg dialog
class CFirstWinSocketServerDlg : public CDialogEx
{
protected:
	const char* ipconfig = "192.168.0.60";		// �� IP
	SOCKET mh_listen_socket;		// Ŭ���̾�Ʈ ���� ó���� �� ����� ����
	SOCKET mh_client_socket;		// �� ���� Ŭ���̾�Ʈ�� ������ ���
// Construction
public:
	CFirstWinSocketServerDlg(CWnd* pParent = nullptr);	// standard constructor

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
};
