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
	CRect rect;

	// Picture Control 위치를 계산
	ap_parent->GetDlgItem(a_rect_id)->GetWindowRect(rect);
	// 클라이언트 다이얼로그 기준으로 좌표를 잡음
	ap_parent->ScreenToClient(rect);

	// 오른쪽으로 약간의 여백이 생기기 때문에 오른쪽으로 조금 더 크게 보정한다
	rect.right += 2;
	// 생성
	Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rect, ap_parent, a_ctrl_id);
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
int TW_ToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CClientDC dc(this);
	// 버튼용 메모리DC
	m_mem_dc.CreateCompatibleDC(&dc);

	// 사각형 좌표를 얻는다
	GetClientRect(m_rect);
	// 폰트를 정한다
	m_tool_font.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));

	UpdateButtonInfo();					// 등록된 버튼들의 위치 정보 구성
	return 0;
}




void TW_ToolBar::OnPaint()
{
	CPaintDC dc(this); 

	dc.SelectStockObject(DC_BRUSH);				// 사용자 지정 브러시
	dc.SetDCBrushColor(m_bk_color);
	
	dc.SelectStockObject(DC_PEN);					// 사용자 지정 펜
	dc.SetDCPenColor(m_bk_color);

	dc.Rectangle(m_rect);				// 영역에 사각형을 그린다

	dc.SelectStockObject(NULL_BRUSH);				// 브러시 사용안함
	dc.SetDCPenColor(m_border_color);				// 펜 색 변경

	// 안쪽 사각형 (내부 테두리 추가)
	dc.Rectangle(m_rect.left + 1, m_rect.top + 1, m_rect.right - 1, m_rect.bottom - 1);

	CRect rect;
	TipsCommandData* p_btn = m_btn_list;				// 첫번째 버튼의 주소를 대입

	dc.SelectObject(&m_tool_font);				// 폰트 변경
	dc.SetBkMode(TRANSPARENT);				// 폰트 배경 투명처리

	for (int i = 0; i < m_btn_count; i++, p_btn++) {
		rect.SetRect(p_btn->x, 3, p_btn->x + p_btn->width, m_rect.bottom - 8);				// left,top,right,bottom
		if (p_btn->p_up_bitmap != NULL) {					// 이미지가 로드된 상태면
			m_mem_dc.SelectObject(p_btn->p_up_bitmap);				// 메모리DC에 연결
			dc.BitBlt(p_btn->x + p_btn->width / 2 - 16, 10, 32, 32, &m_mem_dc, 0, 0, SRCCOPY);			// 화면 출력
		}

		// 문자열을 버튼 위치에 출력
		dc.SetTextColor(m_text_color);
		dc.DrawText(p_btn->p_name, rect, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
	}
}


void TW_ToolBar::OnDestroy()
{

	// TODO: Add your message handler code here
	// 버튼 이름을 저장한 메모리해제
	for (int i = 0; i < m_btn_count; i++) {
		delete[] m_btn_list[i].p_name;

		if (m_btn_list[i].p_up_bitmap != NULL) {
			m_btn_list[i].p_up_bitmap->DeleteObject();				// 비트맵 제거
			delete m_btn_list[i].p_up_bitmap;

			m_btn_list[i].p_down_bitmap->DeleteObject();
			delete m_btn_list[i].p_down_bitmap;
		}
	}
	m_tool_font.DeleteObject();			// 폰트 제거
	m_mem_dc.DeleteDC();					// 메모리DC 제거

	CWnd::OnDestroy();
}


void TW_ToolBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_clicked_flag && m_select_index != -1) {
		// 클릭된 상태가 아니라면 시작 가능
		m_clicked_flag = 1;				// 클릭 상태로 변경
		TipsCommandData* p_btn = m_btn_list + m_select_index;			// 선택 버튼 정보

		// 선택한 버튼의 영역을 계산
		m_select_rect.SetRect(p_btn->x + 4, 4, p_btn->x + p_btn->width - 4, m_rect.bottom - 4);
		// 눌러진 모습으로 교체
		DrawPushButton(p_btn);
		// 마우스가 영역을 벗어나도 작동할 수 있게
		SetCapture();
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void TW_ToolBar::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_clicked_flag) {
		// 마우스가 클릭이 안되어 있으면
		CheckButtonInToolBar(point);				// 버튼의 위치만
	}
	else {
		// 클릭 상태면
		if (m_select_rect.PtInRect(point)) {
			if (m_clicked_flag == 2) {
				m_clicked_flag = 1;				// 영역 밖에 있다가 영역 안으로 들어오면 클릭플래그 변경
				DrawPushButton(m_btn_list + m_select_index);			// 눌러진 모습으로 교체
			}
		}
		else {
			if (m_clicked_flag == 1) {
				m_clicked_flag = 2;				// 클릭 후 버튼 영역을 벗어났을 경우
				DrawPopButton(m_btn_list + m_select_index);					// 버튼을 기본 모습으로 교체
			}
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}

void TW_ToolBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_clicked_flag) {
		// 클릭되었다가 띄었을 경우
		m_clicked_flag = 0;
		ReleaseCapture();

		TipsCommandData* p_btn = m_btn_list + m_select_index;				// 선택한 버튼의 정보
		DrawPopButton(p_btn);					// 기본 버튼의 모습으로 교체

		if (m_select_rect.PtInRect(point)) {
			// 버튼 영역 내에서 마우스를 띄었을 때만
			// 버튼을 눌렀다는 메시지를 부모 윈도우에 WM_COMMAND로 보낸다
			GetParent()->PostMessage(WM_COMMAND, MAKEWPARAM(p_btn->command_id, 0), 0);
		}
	}

	CWnd::OnLButtonUp(nFlags, point);
}


