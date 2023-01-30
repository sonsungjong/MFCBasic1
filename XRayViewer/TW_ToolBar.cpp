// TW_ToolBar.cpp : implementation file
#include "pch.h"
#include "XRayViewer.h"
#include "TW_ToolBar.h"

IMPLEMENT_DYNAMIC(TW_ToolBar, CWnd)

TW_ToolBar::TW_ToolBar()
{
	m_bk_color = RGB(39, 43, 47);
	m_border_color = RGB(59, 63, 67);
	m_in_border_color = RGB(109, 113, 117);
	m_push_btn_color = RGB(59, 63, 67);
	m_text_color = RGB(255, 255, 255);
}

TW_ToolBar::~TW_ToolBar()
{
}

void TW_ToolBar::CreateToolBar(int a_rect_id, CWnd* ap_parent, int a_ctrl_id)
{
	CRect r;

	// a_rect_id의 컨트롤 위치를 계산
	ap_parent->GetDlgItem(a_rect_id)->GetWindowRect(r);
	ap_parent->ScreenToClient(r);

	// 오른쪽으로 약간의 여백이 생기기 때문에 오른쪽으로 조금 더 크게 보정한다
	r.right += 2;
	// 생성
	Create(NULL, NULL, WS_CHILD | WS_VISIBLE, r, ap_parent, a_ctrl_id);
}

void TW_ToolBar::AddButton(const TCHAR* ap_name, int a_command_id, int a_bmp_up_id, int a_bmp_down_id)
{
	if (m_btn_count < MAX_BUTTON_COUNT) {
		int len = _tcslen(ap_name);
		m_btn_list[m_btn_count].name_len = len;				// NULL을 제외한 글자길이를 할당
		len++;					// len은 NULL을 포함한 크기로 변경
		m_btn_list[m_btn_count].p_name = new TCHAR[len];					// 이름을 저장할 메모리를 할당
		memcpy(m_btn_list[m_btn_count].p_name, ap_name, len * sizeof(TCHAR));				// 매개변수의 이름을 복사
		
		// 버튼이 눌렸을 때 사용할 메시지ID를 정의
		m_btn_list[m_btn_count].command_id = a_command_id;
		m_btn_list[m_btn_count].bmp_up_id = a_bmp_up_id;
		m_btn_list[m_btn_count].bmp_down_id = a_bmp_down_id;

		// 비트맵 리소스 아이디가 0이 아니라면
		if (m_btn_list[m_btn_count].bmp_up_id != 0) {
			// 리소스의 bmp를 읽어서 CBitmap 에 저장
			m_btn_list[m_btn_count].p_up_bitmap = new CBitmap;
			m_btn_list[m_btn_count].p_up_bitmap->LoadBitmap(a_bmp_up_id);

			m_btn_list[m_btn_count].p_down_bitmap = new CBitmap;
			m_btn_list[m_btn_count].p_down_bitmap->LoadBitmap(a_bmp_down_id);
		}
		else {
			m_btn_list[m_btn_count].p_up_bitmap = NULL;
			m_btn_list[m_btn_count].p_down_bitmap = NULL;
		}
		m_btn_count++;				// 등록된 버튼의 수를 증가시킨다
	}
}

void TW_ToolBar::UpdateButtonInfo()
{
	CClientDC dc(this);

	// 툴바에 등록된 버튼들 중 첫 번째를 가리킨다
	TipsCommandData* p_btn = m_btn_list;
	dc.SelectObject(&m_tool_font);				// 글꼴 선택
	int position = 5;
	int i = 0;

	for (i = 0; i < m_btn_count; i++, p_btn++) {
		// 처음 시작 위치
		p_btn->x = position;

		// 버튼 이름 크기를 계산하여 버튼 크기를 결정
		p_btn->width = dc.GetTextExtent(p_btn->p_name, p_btn->name_len).cx + 20;

		// 다음 버튼을 위해 위치값 변경
		position += p_btn->width;
	}
}

void TW_ToolBar::CheckButtonInToolBar(CPoint point)
{
	// 툴바에 등록된 버튼들 중 첫 번째를 가리킨다
	TipsCommandData* p_btn = m_btn_list;
	CRect r;
	int i = 0;
	int old_index = m_select_index;

	// 마우스의 현재 위치를 사용해서 툴바의 어떤 버튼 영역에 위치했는지 체크
	for (i = 0; i < m_btn_count; i++, p_btn++) {
		// 현재 버튼의 위치 정보를 구성
		r.SetRect(p_btn->x + 3, 3, p_btn->x + p_btn->width - 3, m_rect.bottom - 3);

		// 마우스가 버튼 위에 위치한 경우
		if (r.PtInRect(point)) {
			// 해당 버튼을 선택된 버튼으로 설정
			m_select_index = i;
			break;
		}
	}

	// 만약 i 값이 m_btn_count와 동일하면 마우스가 툴바 버튼 위에 없다는 뜻
	if (i == m_btn_count) { m_select_index = -1; }

	// 툴바의 선택 상태가 변경되면
	if (old_index != m_select_index) {
		CClientDC dc(this);
		dc.SelectStockObject(DC_PEN);					// 색상만 변경해서 사용하는 Pen
		dc.SelectStockObject(NULL_BRUSH);			// 브러시 없음

		if (old_index != -1) {
			// 이전에 선택된 버튼의 상태를 지움
			p_btn = m_btn_list + old_index;
			dc.SetDCPenColor(m_bk_color);
			dc.Rectangle(p_btn->x + 3, 3, p_btn->x + p_btn->width - 3, m_rect.bottom - 3);
			dc.Rectangle(p_btn->x + 4, 4, p_btn->x + p_btn->width - 4, m_rect.bottom - 4);
		}

		if (m_select_index != -1) {
			// 새로 선택된 버튼에 그린다
			p_btn = m_btn_list + m_select_index;
			dc.SetDCPenColor(m_border_color);				// Pen 색상 변경
			dc.Rectangle(p_btn->x + 3, 3, p_btn->x + p_btn->width - 3, m_rect.bottom - 3);

			dc.SetDCPenColor(m_in_border_color);			// Pen 색상 변경
			dc.Rectangle(p_btn->x + 4, 4, p_btn->x + p_btn->width - 4, m_rect.bottom - 4);
		}
	}
}

void TW_ToolBar::DrawPushButton(TipsCommandData* ap_btn)
{
	CClientDC dc(this);

	dc.SelectObject(&m_tool_font);				// 글꼴 선택
	dc.SetBkMode(TRANSPARENT);				// 문자열 배경 투명처리

	dc.SelectStockObject(DC_BRUSH);			// 색상만 변경해서 사용하는 Brush
	dc.SelectStockObject(DC_PEN);				// 색상만 변경해서 사용하는 Pen

	dc.SetDCBrushColor(m_push_btn_color);				// 배경색 (브러시)
	dc.SetDCPenColor(m_in_border_color);				// 테두리 색 (펜)

	dc.Rectangle(m_select_rect);			// 버튼을 그린다

	CRect r = m_select_rect;
	r.bottom -= 4;				// 위치 보정

	// 이미지를 잘 불러왔다면
	if (ap_btn->p_down_bitmap != NULL) {
		// 메모리DC에 bitmap을 연결하고 그린다
		m_mem_dc.SelectObject(ap_btn->p_down_bitmap);
		dc.BitBlt(ap_btn->x + ap_btn->width / 2 - 16 + 1, 11, 32, 32, &m_mem_dc, 0, 0, SRCCOPY);
	}

	// 문자열 흰색으로 출력
	dc.SetTextColor(m_text_color);
	dc.DrawText(ap_btn->p_name, r + CPoint(1, 1), DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
}

void TW_ToolBar::DrawPopButton(TipsCommandData* ap_btn)
{
	CClientDC dc(this);

	dc.SelectObject(&m_tool_font);				// 글꼴 선택
	dc.SetBkMode(TRANSPARENT);				// 글자배경 투명처리

	dc.SelectStockObject(DC_BRUSH);				// 색상만 변경해서 사용하는 Brush
	dc.SelectStockObject(DC_PEN);					// 색상만 변경해서 사용하는 Pen

	dc.SetDCBrushColor(m_bk_color);
	dc.SetDCPenColor(m_in_border_color);

	dc.Rectangle(m_select_rect);

	CRect r = m_select_rect;
	r.bottom -= 4;
	if (ap_btn->p_up_bitmap != NULL) {
		m_mem_dc.SelectObject(ap_btn->p_up_bitmap);
		dc.BitBlt(ap_btn->x + ap_btn->width / 2 - 16, 10, 32, 32, &m_mem_dc, 0, 0, SRCCOPY);
	}

	// 흰색으로 문자열 출력
	dc.SetTextColor(m_text_color);
	dc.DrawText(ap_btn->p_name, r, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
}


BEGIN_MESSAGE_MAP(TW_ToolBar, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// TW_ToolBar message handlers




void TW_ToolBar::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CWnd::OnPaint() for painting messages
}


int TW_ToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}


void TW_ToolBar::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
}


void TW_ToolBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonDown(nFlags, point);
}


void TW_ToolBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnLButtonUp(nFlags, point);
}


void TW_ToolBar::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CWnd::OnMouseMove(nFlags, point);
}
