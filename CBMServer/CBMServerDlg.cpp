#include "pch.h"
#include "framework.h"
#include "CBMServer.h"
#include "CBMServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCBMServerDlg::CCBMServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CBMSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCBMServerDlg::AddEventString(const wchar_t* ap_string)
{
	int index = m_event_list.InsertString(-1, ap_string);				// 마지막 행에 추가
	m_event_list.SetCurSel(index);											// 행 선택
}

void CCBMServerDlg::ProcessingSensorData(char* ap_data, unsigned short a_data_size)
{
}

void CCBMServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENT_LIST, m_event_list);
}

BEGIN_MESSAGE_MAP(CCBMServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCBMServerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCBMServerDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL CCBMServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CreateDirectory(L".\\data", NULL);				// 폴더 만들기

	// 서브클래싱 - 표 데이터


	// 서버 소켓 시작(리슨)
	m_server_socket.StartListenService(ipconfig, thisPort, this, 25001, 25002);

	// 그래프 출력


	return TRUE;
}

void CCBMServerDlg::OnPaint()
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

HCURSOR CCBMServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCBMServerDlg::OnBnClickedOk(){}

void CCBMServerDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CCBMServerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


LRESULT CCBMServerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	// 소켓이 메시지를 처리할 수 있게 함수 호출
	m_server_socket.MessageProc(message, wParam, lParam);

	return CDialogEx::WindowProc(message, wParam, lParam);
}



// 클라이언트 접속 시
void MyServerSocket::AcceptUserProc(UserData* ap_user_data)
{
	CString str;
	str.Format(L"%s 에서 서버에 접속했습니다.", ap_user_data->ip_address);
	((CCBMServerDlg*)mp_notify_wnd)->AddEventString(str);
}

// 수신 후 작업
int MyServerSocket::ProcessNetMessage()
{
	if (m_net_msg_id == 1)				// 식별자가 1이면
	{
		((CCBMServerDlg*)mp_notify_wnd)->ProcessingSensorData(mp_net_body_data, m_net_body_size);
	}
	return 1;
}

// 클라이언트 접속 해제 시
void MyServerSocket::CloseUserProc(UserData* ap_user_data, int a_error_flag)
{
	if (a_error_flag == 0)				// 정상 해제
	{
		CString str;
		str.Format(L"%s에서 접속을 해제했습니다.", ap_user_data->ip_address);
		((CCBMServerDlg*)mp_notify_wnd)->AddEventString(str);
	}
}