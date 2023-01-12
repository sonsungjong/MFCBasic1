// TipsButton.cpp : implementation file
//

#include "pch.h"
#include "MFCL233ButtonCtrlMake.h"
#include "TipsButton.h"


// TipsButton

IMPLEMENT_DYNAMIC(TipsButton, CWnd)

TipsButton::TipsButton()
{
	mh_mem_dc = NULL;
	mh_mem_bmp = NULL;
	mh_font = NULL;

	// 포커스 색상
	m_focus_btn_color = RGB(69, 73, 77);
	m_focus_border_color = RGB(109, 113, 117);
	// 비포커스 색상
	m_btn_color = RGB(39, 43, 47);
	m_border_color = RGB(59, 63, 67);
	// 내부테두리 색상
	m_in_border_color = RGB(157, 171, 196);
	// 폰트 색상
	m_text_color = RGB(232, 248, 248);

	m_is_clicked = 0;
	m_push_flag = 0;
}

TipsButton::~TipsButton()
{
}


BEGIN_MESSAGE_MAP(TipsButton, CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// TipsButton message handlers

int TipsButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	GetClientRect(m_rect);					// 현재 윈도우 좌표

	HDC hdc = ::GetDC(m_hWnd);
	mh_mem_dc = ::CreateCompatibleDC(hdc);					// 메모리DC 생성
	mh_mem_bmp = ::CreateCompatibleBitmap(hdc, m_rect.Width(), m_rect.Height());				// 메모리 bitmap 생성
	::ReleaseDC(m_hWnd, hdc);				// DC와 bitmap을 만들고 반납

	// 글꼴
	mh_font = ::CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("굴림"));

	::SelectObject(mh_mem_dc, mh_mem_bmp);						// dc에 비트맵 연결
	::SelectObject(mh_mem_dc, mh_font);								// dc에 글꼴 연결

	// 펜과 브러시 색상을 변경하여 기본 객체에 연결
	::SelectObject(mh_mem_dc, ::GetStockObject(DC_BRUSH));
	::SelectObject(mh_mem_dc, ::GetStockObject(DC_PEN));
	::SetBkMode(mh_mem_dc, TRANSPARENT);				// 텍스트 배경 투명하게

	// 일반 상태의 버튼을 메모리 DC로 그린다
	DrawButtonImage(0);
	return 0;
}


void TipsButton::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
	// 그리기에 사용한 객체들 제거
	if (mh_mem_dc != NULL) { ::DeleteDC(mh_mem_dc); }
	if (mh_mem_bmp != NULL) { ::DeleteObject(mh_mem_bmp); }
	if (mh_font != NULL) { ::DeleteObject(mh_font); }
}

// 메모리DC에 그려져있는 비트맵만 갱신되도록
void TipsButton::OnPaint()
{
	CPaintDC dc(this);

	// mh_mem_bmp 를 화면에 출력 (카피)
	::BitBlt(dc.m_hDC, 0, 0, m_rect.Width(), m_rect.Height(), mh_mem_dc, 0, 0, SRCCOPY);
}


void TipsButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked == 0) {					// 마우스가 안클릭된 상태일때만
		m_is_clicked = 1;						// 클릭 상태로 설정
		m_push_flag = 1;						// 눌러진 상태로 변경
		// 버튼의 현재상태 기준으로 mh_mem_bmp에 그린다
		DrawButtonImage(m_push_flag);
		// 화면에 출력
		Invalidate(FALSE);
		// 마우스가 버튼 영역을 벗어나도 마우스 메시지를 계속 받을 수 있게 SetCapture()
		SetCapture();
	}
	CWnd::OnLButtonDown(nFlags, point);
}


void TipsButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked) {						// 마우스가 클릭된 상태일 때
		m_is_clicked = 0;				// 클릭 상태 해제
		ReleaseCapture();						// SetCapture() 해제
		if (m_push_flag == 1) {
			m_push_flag = 0;					// 눌림 상태 해제
			// 버튼을 비트맵에 그린다
			DrawButtonImage(m_push_flag);
			// 화면에 출력한다
			Invalidate(FALSE);
			// 부모 윈도우에 클릭됬다는 것을 메시지로 알림
			GetParent()->PostMessage(LM_BTN_CLICKED, (WPARAM)GetDlgCtrlID(), (LPARAM)this);					// 부모 윈도우에 LM_BTN_CLICKED 메시지 발생
		}
	}
	CWnd::OnLButtonUp(nFlags, point);
}


void TipsButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked)						// 마우스가 클릭된 상태에만
	{
		// 현재 상태 백업 후
		char old_flag = m_push_flag;
		// 마우스가 버튼 안쪽에 있는지 바깥쪽에 있는지 비교하여 현재 상태 변경
		if (m_rect.PtInRect(point)) { m_push_flag = 1; }
		else { m_push_flag = 0; }

		// 클릭 상태에서 백업한 상태와 변경된 상태가 다르면 버튼을 새로 그리고 화면출력
		if (old_flag != m_push_flag)				// 버튼 안쪽에서 클릭한 채로 움직이는 상황에 대해선 갱신이 안되게끔 한다
		{
			DrawButtonImage(m_push_flag);
			Invalidate(FALSE);
		}
	}
	CWnd::OnMouseMove(nFlags, point);
}

// 탭 키로 인해 포커스가 가해졌을 때
void TipsButton::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	// TODO: Add your message handler code here
	DrawButtonImage(m_push_flag);
	Invalidate(FALSE);
}


void TipsButton::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	// TODO: Add your message handler code here
	DrawButtonImage(m_push_flag);
	Invalidate(FALSE);
}

int TipsButton::CreateButton(CWnd* ap_parent, const TCHAR* ap_title, int a_ctrl_id, int a_guide_rect)
{
	CRect r;
	int result = 0;

	CWnd* p_wnd = ap_parent->GetDlgItem(a_guide_rect);
	if (p_wnd != NULL) {
		p_wnd->GetWindowRect(r);
		ap_parent->ScreenToClient(r);

		result = CreateButton(ap_parent, ap_title, a_ctrl_id, r);
	}
	return result;
}

int TipsButton::CreateButton(CWnd* ap_parent, const TCHAR* ap_title, int a_ctrl_id, CRect a_rect)
{
	// 버튼이 사용할 문자열 저장
	m_title_str = ap_title;
	// 주어진 정보를 가지고 버튼 기능을 구현할 윈도우를 생성 (성공하면 1, 실패하면 0)
	BOOL result = Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP, a_rect, ap_parent, a_ctrl_id);

    return result;
}

void TipsButton::DrawButtonImage(char a_push_flag)
{
	if (::GetFocus() == m_hWnd) {				// 포커스 상태일 때
		::SetDCBrushColor(mh_mem_dc, m_focus_btn_color);
		::SetDCPenColor(mh_mem_dc, m_focus_border_color);
	}
	else {
		::SetDCBrushColor(mh_mem_dc, m_btn_color);
		::SetDCPenColor(mh_mem_dc, m_border_color);
	}

	// 사각형을 그린다
	::Rectangle(mh_mem_dc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);

	CRect r;
	if (!a_push_flag)
	{
		// 버튼이 안눌려있으면
		// Brush 사용 안함
		HGDIOBJ h_old_brush = ::SelectObject(mh_mem_dc, ::GetStockObject(NULL_BRUSH));
		::SetDCPenColor(mh_mem_dc, m_in_border_color);				// Pen 색상
		// 버튼 내부 색상
		::Rectangle(mh_mem_dc, m_rect.left + 1, m_rect.top + 1, m_rect.right - 1, m_rect.bottom - 1);
		::SelectObject(mh_mem_dc, h_old_brush);			// 기본 Brush 복구
		r = m_rect;
	}
	else {
		// 버튼이 눌러졌다면 버튼의 텍스트를 살짝 아래로 이동시켜 눌리는 느낌이 나게한다
		r = m_rect + CPoint(1, 1);
	}
	// 텍스트 색상을 지정해서 버튼에 문자열 출력
	::SetTextColor(mh_mem_dc, m_text_color);
	::DrawText(mh_mem_dc, m_title_str, m_title_str.GetLength(), r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void TipsButton::ChangeColor(COLORREF a_focus_btn_color, COLORREF a_focus_border_color, COLORREF a_btn_color, COLORREF a_border_color, COLORREF a_in_border_color, COLORREF a_text_color)
{
	m_focus_btn_color = a_focus_btn_color;
	m_focus_border_color = a_focus_border_color;
	m_btn_color = a_btn_color;
	m_border_color = a_border_color;
	m_in_border_color = a_in_border_color;
	m_text_color = a_text_color;
}
