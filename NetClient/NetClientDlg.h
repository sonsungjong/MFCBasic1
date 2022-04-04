
// NetClientDlg.h : header file
//

#ifndef _NET_CLIENT_DLG_H_
#define _NET_CLIENT_DLG_H_

#define PORT 10005
#define IP		_T("127.0.0.1")
//#include "NoheaderClient.h"

class MyClient : public NoheaderClient
{
public:
	virtual void ConnectedProcess();
	virtual int ProcessNetMessage();
	virtual void ClosedProcess(int a_error_flag);
};

// CNetClientDlg dialog
class CNetClientDlg : public CDialogEx
{
protected:
	MyClient mc;			// ¼ÒÄÏ °´Ã¼

// Construction
public:
	CNetClientDlg(CWnd* pParent = nullptr);	// standard constructor
	void AddEventString(const TCHAR* ap_string);
	void ConnectedProcess();
	int ProcessNetMessage();
	void ClosedProcess(int a_error_flag);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NETCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CListBox m_event_list;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
	afx_msg void OnBnClickedConnectBtn();
	afx_msg void OnBnClickedDisconnectBtn();
	afx_msg void OnBnClickedSendBtn();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnRecvData(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDisconnectSocket(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnConnectSocket(WPARAM wParam, LPARAM lParam);
};

#endif