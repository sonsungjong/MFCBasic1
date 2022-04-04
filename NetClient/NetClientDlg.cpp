
// NetClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "NetClient.h"
#include "NoheaderClient.h"
#include "NetClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNetClientDlg dialog



CNetClientDlg::CNetClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NETCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENT_LIST, m_event_list);
}

BEGIN_MESSAGE_MAP(CNetClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CNetClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CNetClientDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_MESSAGE(RECV_DATA, &CNetClientDlg::OnRecvData)
	ON_MESSAGE(CONNECTED, &CNetClientDlg::OnConnectSocket)
	ON_MESSAGE(DISCONNECTED, &CNetClientDlg::OnDisconnectSocket)
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CNetClientDlg::OnBnClickedConnectBtn)
	ON_BN_CLICKED(IDC_DISCONNECT_BTN, &CNetClientDlg::OnBnClickedDisconnectBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CNetClientDlg::OnBnClickedSendBtn)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CNetClientDlg message handlers

BOOL CNetClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNetClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNetClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNetClientDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CNetClientDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();
}


void CNetClientDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	::PostQuitMessage(0);

	CDialogEx::OnClose();
}

// 재정의 : 접속 결과에 따른 처리
void MyClient::ConnectedProcess()
{
	if (m_is_connected) { ((CNetClientDlg*)mp_notify_wnd)->AddEventString(_T("서버 접속 성공")); }
	else { ((CNetClientDlg*)mp_notify_wnd)->AddEventString(_T("서버 접속 실패")); }
}
// 재정의 : 수신된 데이터를 처리
int MyClient::ProcessNetMessage()
{
	return 1;		// 1은 정상수행, 0은 비정상종료
}
// 재정의 : 접속 해제에 따른 처리
void MyClient::ClosedProcess(int a_error_flag)
{
	if (!a_error_flag) { ((CNetClientDlg*)mp_notify_wnd)->AddEventString(_T("서버에서 접속을 해제했습니다.")); }
}

void CNetClientDlg::AddEventString(const TCHAR* ap_string)
{
	int index = m_event_list.InsertString(-1, ap_string);
	m_event_list.SetCurSel(index);
}


void CNetClientDlg::OnBnClickedConnectBtn()
{
	// TODO: Add your control notification handler code here
}


void CNetClientDlg::OnBnClickedDisconnectBtn()
{
	// TODO: Add your control notification handler code here

}


void CNetClientDlg::OnBnClickedSendBtn()
{
	// TODO: Add your control notification handler code here

}


void CNetClientDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}

LRESULT CNetClientDlg::OnRecvData(WPARAM wParam, LPARAM lParam)
{

}

LRESULT CNetClientDlg::OnDisconnectSocket(WPARAM wParam, LPARAM lParam)
{

}

LRESULT CNetClientDlg::OnConnectSocket(WPARAM wParam, LPARAM lParam)
{

}