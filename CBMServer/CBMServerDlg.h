#pragma once

#include "WinSocketServer.h"

#define IP						L"127.0.0.1"
#define PORT					10005

class MyServerSocket : public WinSocketServer
{
public:
	// 오버라이딩
	virtual void AcceptUserProc(UserData* ap_user_data);				// 클라이언트 접속 시
	virtual int ProcessNetMessage();												// 수신 후 작업
	virtual void CloseUserProc(UserData* ap_user_data, int a_error_flag);				// 클라이언트 해제 후 작업
};

class CCBMServerDlg : public CDialogEx
{
private:
	MyServerSocket m_server_socket;				// 서버 소켓


protected:
	const wchar_t* ipconfig = IP;				// IP
	const int thisPort = PORT;					// PORT

public:
	CCBMServerDlg(CWnd* pParent = nullptr);

	void AddEventString(const wchar_t* ap_string);			// 리스트박스 출력
	void ProcessingSensorData(char* ap_data, unsigned short a_data_size);


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CBMSERVER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnDestroy();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
private:
	CListBox m_event_list;
};

