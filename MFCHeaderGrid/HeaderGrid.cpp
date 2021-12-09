// HeaderGrid.cpp : implementation file
//

#include "pch.h"
#include "MFCHeaderGrid.h"
#include "HeaderGrid.h"


// HeaderGrid

IMPLEMENT_DYNAMIC(HeaderGrid, CWnd)

HeaderGrid::HeaderGrid()
{
}

HeaderGrid::~HeaderGrid()
{
}


BEGIN_MESSAGE_MAP(HeaderGrid, CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// HeaderGrid message handlers

int HeaderGrid::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	mh_resize_we_cursor = ::LoadCursor(NULL, IDC_SIZEWE);
	 
	// 윈도우 영역 얻어오기
	GetClientRect(m_rect);

	mh_font = ::CreateFont(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
		DEFAULT_PITCH | FF_SWISS, _T("굴림"));

	// 깜빡임을 없애기 위해 CImage (메모리DC) 사용
	m_draw_image.Create(m_rect.Width(), m_rect.Height(), 32);
	mh_draw_dc = m_draw_image.GetDC();

	::SelectObject(mh_draw_dc, ::GetStockObject(DC_BRUSH));
	::SelectObject(mh_draw_dc, ::GetStockObject(DC_PEN));
	::SelectObject(mh_draw_dc, mh_font);							// 글폰트 설정
	::SetBkMode(mh_draw_dc, TRANSPARENT);						// 글배경 투명
	::SetTextColor(mh_draw_dc, RGB(255, 255, 255));			// 글자색 흰색

	return 0;
}


void HeaderGrid::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
	// CImage객체의 DC핸들 반납, 제거
	m_draw_image.ReleaseDC();
	m_draw_image.Destroy();

	::DeleteObject(mh_font);
}


void HeaderGrid::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CWnd::OnPaint() for painting messages
	m_draw_image.Draw(dc, 0, 0);
}

int HeaderGrid::CheckGridLine(CPoint point)
{
	HID* p = m_item_data;
	int position = 0;
	for (int i = 0; i < m_count; i++) {
		position += p->width;
		p++;
		if (point.x >= (position - 3) && point.x < (position + 3)) {
			return i;
		}
	}
	return -1;
}

void HeaderGrid::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_is_clicked) {
		int index = CheckGridLine(point);
		if(index != -1){
			m_is_clicked = 1;
			SetCapture();						// 대화상자화면 벗어나도 가능하게끔 처리
			m_click_position = point;				// 마우스 클릭 위치 갱신
			m_select_grid_index = index;
		}
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void HeaderGrid::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked) {
		ReleaseCapture();					// SetCapture 상태 해제 (필수)
		m_is_clicked = 0;
	}
	CWnd::OnLButtonUp(nFlags, point);
}


void HeaderGrid::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	int index = CheckGridLine(point);
	if (index != -1) {				// 그리드선 위에 있으면 마우스커서 변경
		::SetCursor(mh_resize_we_cursor);
	}

	if (m_is_clicked) {
		m_item_data[m_select_grid_index].width += point.x - m_click_position.x;
		m_click_position = point;
		if (mh_buddy_wnd && IsWindow(mh_buddy_wnd)) {
			::PostMessage(mh_buddy_wnd, 44001, m_count, (LPARAM)m_item_data);
		}
		RedrawItemData();
	}
	CWnd::OnMouseMove(nFlags, point);
}

void HeaderGrid::AddItemData(const TCHAR* ap_name, short a_width)
{
	// 배열의 크기를 벗어나지 않았는지 체크
	if (m_count < MAX_HEADER_ITEM_COUNT) {
		// 항목이 추가될 위치의 주소를 얻음
		HID* p = m_item_data + m_count;
		// 폭 저장
		p->width = a_width;
		// 추가될 이름의 길이 저장
		p->m_len = (short)_tcslen(ap_name);
		// 추가될 이름 저장
		memcpy(p->m_item_name, ap_name, (p->m_len + 1) << 1);				// 널문자때문에 +1하고 유니코드기 때문에 쉬프트 << 1
		m_count++;
	}
}

void HeaderGrid::DrawHeaderItem()
{
	::SetDCBrushColor(mh_draw_dc, RGB(0, 0, 0));
	::SetDCPenColor(mh_draw_dc, RGB(0, 0, 0));
	// 전체 화면을 검은색으로 지운다
	::Rectangle(mh_draw_dc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);

	::SetDCPenColor(mh_draw_dc, RGB(100, 232, 255));
	HID* p = m_item_data;
	RECT r = {0, m_rect.top, 0, m_rect.bottom};
	for (int i = 0; i < m_count; i++) {
		r.right += p->width;
		::DrawText(mh_draw_dc, p->m_item_name, p->m_len, &r, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		r.left = r.right;
		p++;										// 다음 배열로 이동

		::MoveToEx(mh_draw_dc, r.right, m_rect.top, NULL);
		::LineTo(mh_draw_dc, r.right, m_rect.bottom);
	}
}

void HeaderGrid::RedrawItemData()
{
	DrawHeaderItem();			// 이미지 객체에 다시 그림을 그린다.
	Invalidate(0);						// 이미지 객체를 화면에 출력한다. 
}