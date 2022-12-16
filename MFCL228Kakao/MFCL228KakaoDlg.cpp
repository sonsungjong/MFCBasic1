
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

	// 캡처된 이미지가 출력될 영역을 얻는다
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
	KillTimer(1);
	KillTimer(2);
	DeleteMonObject();
	ResetChatRoomData();
}

void CMFCL228KakaoDlg::AddEventString(const TCHAR* ap_string)
{
	// 300개 이상의 문자열이 추가되지 않도록 300개가 넘으면 가장 오래된 항목부터 지운다
	while (m_event_list.GetCount() > 300) { m_event_list.DeleteString(0); }

	SYSTEMTIME cur_time;
	TCHAR event_buffer[1024];
	GetLocalTime(&cur_time);				// 현재 시간을 얻는다
	// 문자열의 앞에 현재 시간을 출력해서 문자열을 재구성한다
	_stprintf_s(event_buffer, 1024, _T("[%04d-%02d-%02d %02d:%02d:%02d] %s"),
		cur_time.wYear, cur_time.wMonth, cur_time.wDay, cur_time.wHour, cur_time.wMinute, cur_time.wSecond, ap_string);

	// 재구성된 문자열을 콤보 박스에 추가
	int index = m_event_list.InsertString(-1, event_buffer);
	// 추가된 위치를 선택
	m_event_list.SetCurSel(index);
}

// 동적 할당된 메모리나 핸들을 제거
void CMFCL228KakaoDlg::DeleteMonObject()
{
	// DC 삭제
	if (mh_mem_dc != NULL) {
		::DeleteDC(mh_mem_dc);
		mh_mem_dc = NULL;
	}
	
	// Bitmap 삭제
	if (mh_mem_bitmap != NULL) {
		::DeleteObject(mh_mem_bitmap);
		mh_mem_bitmap = NULL;
	}

	// 현재 이미지 패턴 삭제
	if (mp_cur_data != NULL) {
		delete[] mp_cur_data;
		mp_cur_data = NULL;
	}

	// 이전 이미지 패턴 삭제
	if (mp_backup_data != NULL) {
		delete[] mp_backup_data;
		mp_backup_data = NULL;
	}
}

// 감시 시작
void CMFCL228KakaoDlg::OnBnClickedStartMonitorBtn()
{
	// TODO: Add your control notification handler code here
if (!m_start_flag) {
	int index = m_room_list.GetCurSel();
	if (LB_ERR == index) {
		AddEventString(_T("감시를 시작하려면 사용할 채팅 방을 반드시 선택해야 합니다!"));
		return;
	}

	// 선택된 항목에 저장된 채팅 방의 정보를 기억한다 (실수로 다른 방을 클릭해도 변경없도록 이전 것 기억)
	mp_selected_room = (ChatRoomData*)m_room_list.GetItemDataPtr(index);
	m_start_flag = 1;			// 모니터링 시작
	AddEventString(_T("5초마다 영역을 체크해서 변화가 있으면 이미지를 전송합니다."));
	// 현재 윈도우의 DC를 얻는다
	HDC hdc = ::GetDC(m_hWnd);
	// hdc와 호환되는 메모리 DC 생성
	mh_mem_dc = ::CreateCompatibleDC(hdc);
	// 화면 캡처와 출력에 사용될 비트맵 생성 (크기는 m_target_rect와 동일하게 설정함)
	mh_mem_bitmap = ::CreateCompatibleBitmap(hdc, m_target_rect.Width(), m_target_rect.Height());
	// 메모리 DC에 비트맵을 연결
	::SelectObject(mh_mem_dc, mh_mem_bitmap);
	// 이미지 패턴의 전체 크기를 계산 (32bit 색상이기 때문에 x4)
	m_image_data_size = m_target_rect.Width() * m_target_rect.Height() *4;			// 한 점 : 4byte
	// 현재 이미지 패턴을 저장할 메모리 할당
	mp_cur_data = new unsigned char[m_image_data_size];
	// 이전 이미지 패턴을 저장할 메모리 할당
	mp_backup_data = new unsigned char[m_image_data_size];
	// 이전 메모리는 처음에 값이 없을 수 있기 때문에 초기화
	memset(mp_backup_data, 0, m_image_data_size);
	// 메모리 DC를 만들기 위한 할당 DC를 해제
	::ReleaseDC(m_hWnd, hdc);

	// 5초 간격으로 화면 감시
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
		AddEventString(_T("감시 작업을 중단합니다."));
		DeleteMonObject();			// 감시에 사용된 정보들 제거
	}
}


void CMFCL228KakaoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {				// 5초 타이머
		// 화면 전체를 사용할 수 있는 DC 얻는다
		HDC hdc = ::GetWindowDC(NULL);
		// 전체 화면에서 (100, 100) 위치 중 m_target_rect.Width(), m_target_rect.Height() 크기만큼
		// 이미지를 mh_mem_bitmap에 복사한다
		::BitBlt(mh_mem_dc, 0, 0, m_target_rect.Width(), m_target_rect.Height(),
			hdc, 100, 100, SRCCOPY);

		// 캡처를 위해 얻은 DC 해제
		::ReleaseDC(NULL, hdc);

		// 캡처 이미지에서 이미지패턴을 mp_cur_data 에 복사
		::GetBitmapBits(mh_mem_bitmap, m_image_data_size, mp_cur_data);
		// 이미지 패턴과 비교해서 동일한지 판별
		if (memcmp(mp_backup_data, mp_cur_data, m_image_data_size)) {				// 이미지 패턴이 달라진 경우 (메모리 컴페어)
			// 현재 이미지를 이전 이미지에 복사
			memcpy(mp_backup_data, mp_cur_data, m_image_data_size);

			// 클라이언트 영역 출력용 DC를 생성
			CClientDC dc(this);
			// 현재 이미지를 화면에 출력
			::BitBlt(dc.m_hDC, m_target_rect.left, m_target_rect.top, m_target_rect.Width(), m_target_rect.Height(),
				mh_mem_dc, 0, 0, SRCCOPY);

			OpenClipboard();				// 클립보드를 연다
			EmptyClipboard();				// 클립보드에 저장된 기존 정보를 제거
			SetClipboardData(CF_BITMAP, mh_mem_bitmap);				// 캡처 이미지를 클립보드에게 넘겨준다
			CloseClipboard();				// 클립보드를 닫는다

			// 캡처에 사용된 비트맵은 클립보드가 갖고가서 캡처를 위해 새로운 비트맵을 생성
			mh_mem_bitmap = ::CreateCompatibleBitmap(dc.m_hDC, m_target_rect.Width(), m_target_rect.Height());
			// 새로 생성한 비트맵을 메모리 DC에 연결
			::SelectObject(mh_mem_dc, mh_mem_bitmap);
			// 선택한 카톡방의 에디트 컨트롤에 붙여넣기하면 수행되는 메시지를 Spy++로 찾아냄
			// 이 메시지를 전송하면 '클립보드 이미지 전송' 대화 상자가 출력된다
			::SendMessage(mp_selected_room->h_edit_wnd, 0x07E9, 0x0000E125, 0x00);
			// 0.5초간 타이머 중단
			KillTimer(1);
			SetTimer(2, 500, NULL);					// 일회용 타이머, 내부에서 SetTimer(1, 5000, NULL) 사용
		}
	}
	else if (nIDEvent == 2) {
		KillTimer(2);				// 일회용 타이머
		HWND h_find_wnd = NULL;

		// 카카오톡의 '클립보드 이미지 전송' 대화 상자를 찾는다
		while (h_find_wnd = ::FindWindowEx(NULL, h_find_wnd, _T("#32770"), NULL)) {
			// 대화 상자 속성을 비교
			if ((::GetWindowLong(h_find_wnd, GWL_STYLE) == 0x00010000) || (::GetWindowLong(h_find_wnd, GWL_STYLE) == 0x9608004C)){
				// 해당 대화 상자의 부모가 채팅 윈도우인지 비교
				if (mp_selected_room->h_room_wnd == ::GetParent(h_find_wnd)) {
					// 엔터키를 해당 윈도우로 전달하여 이미지가 채팅 방에 추가되도록 한다
					::PostMessage(h_find_wnd, WM_KEYDOWN, 0x0000000D, 0x001C0001);				// 0x0000000D == 엔터키
					::PostMessage(h_find_wnd, WM_KEYUP, 0x0000000D, 0xC01C0001);
					break;
				}
			}
		}
		AddEventString(_T("이미지패턴이 변경되어 카톡으로 전송합니다."));
		SetTimer(1, 5000, NULL);				// 5초마다 화면 감시 재시작
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}
}
