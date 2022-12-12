
// MFCL228KakaoDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL228Kakao.h"
#include "MFCL228KakaoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL228KakaoDlg dialog



CMFCL228KakaoDlg::CMFCL228KakaoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL228KAKAO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL228KakaoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ROOM_LIST, m_room_list);
}

BEGIN_MESSAGE_MAP(CMFCL228KakaoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL228KakaoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL228KakaoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_FIND_ROOM_BTN, &CMFCL228KakaoDlg::OnBnClickedFindRoomBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCL228KakaoDlg::OnBnClickedSendBtn)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCL228KakaoDlg message handlers

BOOL CMFCL228KakaoDlg::OnInitDialog()
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

void CMFCL228KakaoDlg::OnPaint()
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
HCURSOR CMFCL228KakaoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL228KakaoDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL228KakaoDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCL228KakaoDlg::OnBnClickedFindRoomBtn()
{
	// TODO: Add your control notification handler code here
	ResetChatRoomData();

	int index = 0;
	HWND h_room_wnd = NULL;
	HWND h_edit_wnd;

	while (h_room_wnd = ::FindWindowEx(NULL, h_room_wnd, _T("#32770"), NULL)) {				// 대화상자를 찾는다
		h_edit_wnd = ::FindWindowEx(h_room_wnd, NULL, _T("RichEdit50W"), NULL);					// RichEdit 컨트롤을 갖고 있는 지 찾는다
		if (NULL != h_edit_wnd) {
			long long len = ::SendMessage(h_room_wnd, WM_GETTEXTLENGTH, 0, 0);
			if (len > 0) {
				TCHAR* p_name = new TCHAR[len + 1];
				::SendMessage(h_room_wnd, WM_GETTEXT, len + 1, (LPARAM)p_name);
				m_room_list.InsertString(index, p_name);
				delete[] p_name;
			}
			else {
				m_room_list.InsertString(index, _T(""));				// 창 제목이 없음
			}
			ChatRoomData* p_data = new ChatRoomData;
			p_data->h_room_wnd = h_room_wnd;
			p_data->h_edit_wnd = h_edit_wnd;
			m_room_list.SetItemDataPtr(index++, p_data);
		}
	}
}


void CMFCL228KakaoDlg::OnBnClickedSendBtn()
{
	// TODO: Add your control notification handler code here
	int index = m_room_list.GetCurSel();
	if (index != LB_ERR) {
		ChatRoomData* p_data = (ChatRoomData*)m_room_list.GetItemDataPtr(index);
		CString str;
		GetDlgItemText(IDC_CHAT_EDIT, str);
		::SendMessage(p_data->h_edit_wnd, WM_SETTEXT, 0, (LPARAM)(const TCHAR*)str);
		Sleep(200);
		// Enter키를 누른 것과 같은 메시지를 리치 에디트 컨트롤에 전송
		::PostMessage(p_data->h_edit_wnd, WM_KEYDOWN, 0x0000000D, 0x001C0001);
		::PostMessage(p_data->h_edit_wnd, WM_KEYUP, 0x0000000D, 0xC01C0001);
	}
}

void CMFCL228KakaoDlg::ResetChatRoomData()
{
	ChatRoomData* p_data;
	int count = m_room_list.GetCount();
	for (int i = 0; i < count; i++) {
		p_data = (ChatRoomData*)m_room_list.GetItemDataPtr(i);
		delete p_data;
	}
	m_room_list.ResetContent();
}

void CMFCL228KakaoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	ResetChatRoomData();
}
