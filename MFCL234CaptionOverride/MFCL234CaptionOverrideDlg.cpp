
// MFCL234CaptionOverrideDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL234CaptionOverride.h"
#include "MFCL234CaptionOverrideDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL234CaptionOverrideDlg dialog



CMFCL234CaptionOverrideDlg::CMFCL234CaptionOverrideDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL234CAPTIONOVERRIDE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}



void CMFCL234CaptionOverrideDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL234CaptionOverrideDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL234CaptionOverrideDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL234CaptionOverrideDlg::OnBnClickedCancel)
	ON_WM_NCACTIVATE()
	ON_WM_NCPAINT()
END_MESSAGE_MAP()


// CMFCL234CaptionOverrideDlg message handlers

BOOL CMFCL234CaptionOverrideDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// 글꼴
	m_font.CreateFont(12, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("굴림"));
	MakeWindowCaptionRect();						// 캡션 영역 계산

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL234CaptionOverrideDlg::OnPaint()
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
HCURSOR CMFCL234CaptionOverrideDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL234CaptionOverrideDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL234CaptionOverrideDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

// Non-Client 활성화/비활성화 여부
BOOL CMFCL234CaptionOverrideDlg::OnNcActivate(BOOL bActive)
{
	// TODO: Add your message handler code here and/or call default
	if (!IsWindowEnabled()) { bActive = FALSE; }

	// 해당 메시지가 여러번 들어오기 때문에 백업변수로 점검
	if (bActive == m_is_active) { return TRUE; }

	DWORD win_style = GetStyle();
	if (win_style & WS_VISIBLE) { ::SetWindowLong(m_hWnd, GWL_STYLE, (win_style & ~WS_VISIBLE)); }
	AfxGetThreadState()->m_lastSentMsg.wParam = bActive;

	Default();

	if (win_style & WS_VISIBLE) { ::SetWindowLong(m_hWnd, GWL_STYLE, win_style); }
	m_is_active = bActive;								// 상태 변경
	SendMessage(WM_NCPAINT);						// 캡션을 다시 그릴 수 있도록 갱신발생

	return TRUE;
	//return CDialogEx::OnNcActivate(bActive);
}

// Non-Client 캡션, 테두리
void CMFCL234CaptionOverrideDlg::OnNcPaint()
{
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnNcPaint() for painting messages
	// CDialogEx::OnNcPaint();

	// wParam 과 lParam 강제사용
	const MSG* p_msg = GetCurrentMessage();

	// 실제 갱신되여야하는 영역정보가 wParam으로 전송됨 (단, h_rgn == 1 일 경우 전체 갱신을 의미)
	HRGN h_rgn = (HRGN)p_msg->wParam;
	CRect win_rect;
	GetWindowRect(&win_rect);

	// 캡션 영역이 현재 윈도우의 스크린 좌표에 맞게 위치조정
	CRect win_caption_rect = m_caption_rect + win_rect.TopLeft();

	// 부분 그리기이면서 캡션 영역이 그려지는 경우가 아닐때는 기본처리루틴 수행
	if ((DWORD)h_rgn > 1 && !::RectInRegion(h_rgn, win_caption_rect)) {
		Default();
		return;
	}

	// 캡션영역을 위한 영역객체 생성
	HRGN h_rgn_caption = ::CreateRectRgnIndirect(win_caption_rect);
	HRGN h_rgn_new = ::CreateRectRgnIndirect(win_caption_rect);

	if ((DWORD)h_rgn > 1) {
		::CombineRgn(h_rgn_new, h_rgn, h_rgn_caption, RGN_DIFF);
	}
	else {
		HRGN h_rgn_all = ::CreateRectRgnIndirect(&win_rect);
		CombineRgn(h_rgn_new, h_rgn_all, h_rgn_caption, RGN_DIFF);
		DeleteObject(h_rgn_all);
	}

	MSG* p_last_msg = &AfxGetThreadState()->m_lastSentMsg;
	WPARAM save_rgn = p_last_msg->wParam;
	p_last_msg->wParam = (WPARAM)h_rgn_new;
	Default();

	DeleteObject(h_rgn_caption);
	DeleteObject(h_rgn_new);
	p_last_msg->wParam = save_rgn;

	// TODO : 여기부터 캡션 재정의를 하자
	CWindowDC dc(this);
	CRect caption_rect = m_caption_rect;
	CString str;

	GetWindowText(str);
	dc.SelectObject(&m_font);

	if (m_is_active == TRUE) {
		// 윈도우가 활성화 상태
		dc.FillSolidRect(caption_rect, RGB(185, 208, 232));
		dc.SetTextColor(RGB(0, 128, 200));
	}
	else {
		// 윈도우가 비활성화 상태
		dc.FillSolidRect(caption_rect, RGB(215, 227, 241));
		dc.SetTextColor(RGB(155, 177, 191));
	}

	caption_rect.left += 10;
	dc.DrawText(str, caption_rect, DT_SINGLELINE | DT_VCENTER);
}

void CMFCL234CaptionOverrideDlg::MakeWindowCaptionRect()
{
	// 현재 윈도우 좌표를 얻음
	GetWindowRect(m_caption_rect);

	int frame_size_cx, frame_size_cy;
	// WS_THICKFRAME 속성 여부에 따라 캡션굵기 계산
	if (GetStyle() & WS_THICKFRAME)
	{
		frame_size_cx = GetSystemMetrics(SM_CXSIZEFRAME);
		frame_size_cy = GetSystemMetrics(SM_CYSIZEFRAME);
	}
	else 
	{
		frame_size_cx = GetSystemMetrics(SM_CXFIXEDFRAME);
		frame_size_cy = GetSystemMetrics(SM_CYFIXEDFRAME);
	}

	// 스크린 좌표를 좌상단 좌표가 되도록 보정
	m_caption_rect -= CPoint(m_caption_rect.left, m_caption_rect.top);

	// 순수 캡션 영역만 구하기
	m_caption_rect.left += frame_size_cx;
	m_caption_rect.right -= frame_size_cx;
	m_caption_rect.top += frame_size_cy;
	m_caption_rect.bottom = m_caption_rect.top + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER) +3;
}

