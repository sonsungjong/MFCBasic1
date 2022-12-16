
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
	DDX_Control(pDX, IDC_EVENT_LIST, m_event_list);
}

BEGIN_MESSAGE_MAP(CMFCL228KakaoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL228KakaoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL228KakaoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_FIND_ROOM_BTN, &CMFCL228KakaoDlg::OnBnClickedFindRoomBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCL228KakaoDlg::OnBnClickedSendBtn)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_START_MONITOR_BTN, &CMFCL228KakaoDlg::OnBnClickedStartMonitorBtn)
	ON_BN_CLICKED(IDC_STOP_MONITOR_BTN, &CMFCL228KakaoDlg::OnBnClickedStopMonitorBtn)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCL228KakaoDlg message handlers

BOOL CMFCL228KakaoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// ĸó�� �̹����� ��µ� ������ ��´�
	GetDlgItem(IDC_DISPLAY_RECT)->GetWindowRect(m_target_rect);
	ScreenToClient(m_target_rect);

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

	while (h_room_wnd = ::FindWindowEx(NULL, h_room_wnd, _T("#32770"), NULL)) {				// ��ȭ���ڸ� ã�´�
		h_edit_wnd = ::FindWindowEx(h_room_wnd, NULL, _T("RichEdit50W"), NULL);					// RichEdit ��Ʈ���� ���� �ִ� �� ã�´�
		if (NULL != h_edit_wnd) {
			long long len = ::SendMessage(h_room_wnd, WM_GETTEXTLENGTH, 0, 0);
			if (len > 0) {
				TCHAR* p_name = new TCHAR[len + 1];
				::SendMessage(h_room_wnd, WM_GETTEXT, len + 1, (LPARAM)p_name);
				m_room_list.InsertString(index, p_name);
				delete[] p_name;
			}
			else {
				m_room_list.InsertString(index, _T(""));				// â ������ ����
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
		// EnterŰ�� ���� �Ͱ� ���� �޽����� ��ġ ����Ʈ ��Ʈ�ѿ� ����
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
	KillTimer(1);
	KillTimer(2);
	DeleteMonObject();
	ResetChatRoomData();
}

void CMFCL228KakaoDlg::AddEventString(const TCHAR* ap_string)
{
	// 300�� �̻��� ���ڿ��� �߰����� �ʵ��� 300���� ������ ���� ������ �׸���� �����
	while (m_event_list.GetCount() > 300) { m_event_list.DeleteString(0); }

	SYSTEMTIME cur_time;
	TCHAR event_buffer[1024];
	GetLocalTime(&cur_time);				// ���� �ð��� ��´�
	// ���ڿ��� �տ� ���� �ð��� ����ؼ� ���ڿ��� �籸���Ѵ�
	_stprintf_s(event_buffer, 1024, _T("[%04d-%02d-%02d %02d:%02d:%02d] %s"),
		cur_time.wYear, cur_time.wMonth, cur_time.wDay, cur_time.wHour, cur_time.wMinute, cur_time.wSecond, ap_string);

	// �籸���� ���ڿ��� �޺� �ڽ��� �߰�
	int index = m_event_list.InsertString(-1, event_buffer);
	// �߰��� ��ġ�� ����
	m_event_list.SetCurSel(index);
}

// ���� �Ҵ�� �޸𸮳� �ڵ��� ����
void CMFCL228KakaoDlg::DeleteMonObject()
{
	// DC ����
	if (mh_mem_dc != NULL) {
		::DeleteDC(mh_mem_dc);
		mh_mem_dc = NULL;
	}
	
	// Bitmap ����
	if (mh_mem_bitmap != NULL) {
		::DeleteObject(mh_mem_bitmap);
		mh_mem_bitmap = NULL;
	}

	// ���� �̹��� ���� ����
	if (mp_cur_data != NULL) {
		delete[] mp_cur_data;
		mp_cur_data = NULL;
	}

	// ���� �̹��� ���� ����
	if (mp_backup_data != NULL) {
		delete[] mp_backup_data;
		mp_backup_data = NULL;
	}
}

// ���� ����
void CMFCL228KakaoDlg::OnBnClickedStartMonitorBtn()
{
	// TODO: Add your control notification handler code here
if (!m_start_flag) {
	int index = m_room_list.GetCurSel();
	if (LB_ERR == index) {
		AddEventString(_T("���ø� �����Ϸ��� ����� ä�� ���� �ݵ�� �����ؾ� �մϴ�!"));
		return;
	}

	// ���õ� �׸� ����� ä�� ���� ������ ����Ѵ� (�Ǽ��� �ٸ� ���� Ŭ���ص� ��������� ���� �� ���)
	mp_selected_room = (ChatRoomData*)m_room_list.GetItemDataPtr(index);
	m_start_flag = 1;			// ����͸� ����
	AddEventString(_T("5�ʸ��� ������ üũ�ؼ� ��ȭ�� ������ �̹����� �����մϴ�."));
	// ���� �������� DC�� ��´�
	HDC hdc = ::GetDC(m_hWnd);
	// hdc�� ȣȯ�Ǵ� �޸� DC ����
	mh_mem_dc = ::CreateCompatibleDC(hdc);
	// ȭ�� ĸó�� ��¿� ���� ��Ʈ�� ���� (ũ��� m_target_rect�� �����ϰ� ������)
	mh_mem_bitmap = ::CreateCompatibleBitmap(hdc, m_target_rect.Width(), m_target_rect.Height());
	// �޸� DC�� ��Ʈ���� ����
	::SelectObject(mh_mem_dc, mh_mem_bitmap);
	// �̹��� ������ ��ü ũ�⸦ ��� (32bit �����̱� ������ x4)
	m_image_data_size = m_target_rect.Width() * m_target_rect.Height() *4;			// �� �� : 4byte
	// ���� �̹��� ������ ������ �޸� �Ҵ�
	mp_cur_data = new unsigned char[m_image_data_size];
	// ���� �̹��� ������ ������ �޸� �Ҵ�
	mp_backup_data = new unsigned char[m_image_data_size];
	// ���� �޸𸮴� ó���� ���� ���� �� �ֱ� ������ �ʱ�ȭ
	memset(mp_backup_data, 0, m_image_data_size);
	// �޸� DC�� ����� ���� �Ҵ� DC�� ����
	::ReleaseDC(m_hWnd, hdc);

	// 5�� �������� ȭ�� ����
	SetTimer(1, 5000, NULL);
}
}


void CMFCL228KakaoDlg::OnBnClickedStopMonitorBtn()
{
	// TODO: Add your control notification handler code here
	if (m_start_flag) {
		KillTimer(1);
		KillTimer(2);
		m_start_flag = 0;
		AddEventString(_T("���� �۾��� �ߴ��մϴ�."));
		DeleteMonObject();			// ���ÿ� ���� ������ ����
	}
}


void CMFCL228KakaoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {				// 5�� Ÿ�̸�
		// ȭ�� ��ü�� ����� �� �ִ� DC ��´�
		HDC hdc = ::GetWindowDC(NULL);
		// ��ü ȭ�鿡�� (100, 100) ��ġ �� m_target_rect.Width(), m_target_rect.Height() ũ�⸸ŭ
		// �̹����� mh_mem_bitmap�� �����Ѵ�
		::BitBlt(mh_mem_dc, 0, 0, m_target_rect.Width(), m_target_rect.Height(),
			hdc, 100, 100, SRCCOPY);

		// ĸó�� ���� ���� DC ����
		::ReleaseDC(NULL, hdc);

		// ĸó �̹������� �̹��������� mp_cur_data �� ����
		::GetBitmapBits(mh_mem_bitmap, m_image_data_size, mp_cur_data);
		// �̹��� ���ϰ� ���ؼ� �������� �Ǻ�
		if (memcmp(mp_backup_data, mp_cur_data, m_image_data_size)) {				// �̹��� ������ �޶��� ��� (�޸� �����)
			// ���� �̹����� ���� �̹����� ����
			memcpy(mp_backup_data, mp_cur_data, m_image_data_size);

			// Ŭ���̾�Ʈ ���� ��¿� DC�� ����
			CClientDC dc(this);
			// ���� �̹����� ȭ�鿡 ���
			::BitBlt(dc.m_hDC, m_target_rect.left, m_target_rect.top, m_target_rect.Width(), m_target_rect.Height(),
				mh_mem_dc, 0, 0, SRCCOPY);

			OpenClipboard();				// Ŭ�����带 ����
			EmptyClipboard();				// Ŭ�����忡 ����� ���� ������ ����
			SetClipboardData(CF_BITMAP, mh_mem_bitmap);				// ĸó �̹����� Ŭ�����忡�� �Ѱ��ش�
			CloseClipboard();				// Ŭ�����带 �ݴ´�

			// ĸó�� ���� ��Ʈ���� Ŭ�����尡 ������ ĸó�� ���� ���ο� ��Ʈ���� ����
			mh_mem_bitmap = ::CreateCompatibleBitmap(dc.m_hDC, m_target_rect.Width(), m_target_rect.Height());
			// ���� ������ ��Ʈ���� �޸� DC�� ����
			::SelectObject(mh_mem_dc, mh_mem_bitmap);
			// ������ ī����� ����Ʈ ��Ʈ�ѿ� �ٿ��ֱ��ϸ� ����Ǵ� �޽����� Spy++�� ã�Ƴ�
			// �� �޽����� �����ϸ� 'Ŭ������ �̹��� ����' ��ȭ ���ڰ� ��µȴ�
			::SendMessage(mp_selected_room->h_edit_wnd, 0x07E9, 0x0000E125, 0x00);
			// 0.5�ʰ� Ÿ�̸� �ߴ�
			KillTimer(1);
			SetTimer(2, 500, NULL);					// ��ȸ�� Ÿ�̸�, ���ο��� SetTimer(1, 5000, NULL) ���
		}
	}
	else if (nIDEvent == 2) {
		KillTimer(2);				// ��ȸ�� Ÿ�̸�
		HWND h_find_wnd = NULL;

		// īī������ 'Ŭ������ �̹��� ����' ��ȭ ���ڸ� ã�´�
		while (h_find_wnd = ::FindWindowEx(NULL, h_find_wnd, _T("#32770"), NULL)) {
			// ��ȭ ���� �Ӽ��� ��
			if ((::GetWindowLong(h_find_wnd, GWL_STYLE) == 0x00010000) || (::GetWindowLong(h_find_wnd, GWL_STYLE) == 0x9608004C)){
				// �ش� ��ȭ ������ �θ� ä�� ���������� ��
				if (mp_selected_room->h_room_wnd == ::GetParent(h_find_wnd)) {
					// ����Ű�� �ش� ������� �����Ͽ� �̹����� ä�� �濡 �߰��ǵ��� �Ѵ�
					::PostMessage(h_find_wnd, WM_KEYDOWN, 0x0000000D, 0x001C0001);				// 0x0000000D == ����Ű
					::PostMessage(h_find_wnd, WM_KEYUP, 0x0000000D, 0xC01C0001);
					break;
				}
			}
		}
		AddEventString(_T("�̹��������� ����Ǿ� ī������ �����մϴ�."));
		SetTimer(1, 5000, NULL);				// 5�ʸ��� ȭ�� ���� �����
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}
}
