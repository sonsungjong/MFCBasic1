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
	 
	// ������ ���� ������
	GetClientRect(m_rect);

	mh_font = ::CreateFont(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
		DEFAULT_PITCH | FF_SWISS, _T("����"));

	// �������� ���ֱ� ���� CImage (�޸�DC) ���
	m_draw_image.Create(m_rect.Width(), m_rect.Height(), 32);
	mh_draw_dc = m_draw_image.GetDC();

	::SelectObject(mh_draw_dc, ::GetStockObject(DC_BRUSH));
	::SelectObject(mh_draw_dc, ::GetStockObject(DC_PEN));
	::SelectObject(mh_draw_dc, mh_font);							// ����Ʈ ����
	::SetBkMode(mh_draw_dc, TRANSPARENT);						// �۹�� ����
	::SetTextColor(mh_draw_dc, RGB(255, 255, 255));			// ���ڻ� ���

	return 0;
}


void HeaderGrid::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
	// CImage��ü�� DC�ڵ� �ݳ�, ����
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
			SetCapture();						// ��ȭ����ȭ�� ����� �����ϰԲ� ó��
			m_click_position = point;				// ���콺 Ŭ�� ��ġ ����
			m_select_grid_index = index;
		}
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void HeaderGrid::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked) {
		ReleaseCapture();					// SetCapture ���� ���� (�ʼ�)
		m_is_clicked = 0;
	}
	CWnd::OnLButtonUp(nFlags, point);
}


void HeaderGrid::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	int index = CheckGridLine(point);
	if (index != -1) {				// �׸��弱 ���� ������ ���콺Ŀ�� ����
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
	// �迭�� ũ�⸦ ����� �ʾҴ��� üũ
	if (m_count < MAX_HEADER_ITEM_COUNT) {
		// �׸��� �߰��� ��ġ�� �ּҸ� ����
		HID* p = m_item_data + m_count;
		// �� ����
		p->width = a_width;
		// �߰��� �̸��� ���� ����
		p->m_len = (short)_tcslen(ap_name);
		// �߰��� �̸� ����
		memcpy(p->m_item_name, ap_name, (p->m_len + 1) << 1);				// �ι��ڶ����� +1�ϰ� �����ڵ�� ������ ����Ʈ << 1
		m_count++;
	}
}

void HeaderGrid::DrawHeaderItem()
{
	::SetDCBrushColor(mh_draw_dc, RGB(0, 0, 0));
	::SetDCPenColor(mh_draw_dc, RGB(0, 0, 0));
	// ��ü ȭ���� ���������� �����
	::Rectangle(mh_draw_dc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);

	::SetDCPenColor(mh_draw_dc, RGB(100, 232, 255));
	HID* p = m_item_data;
	RECT r = {0, m_rect.top, 0, m_rect.bottom};
	for (int i = 0; i < m_count; i++) {
		r.right += p->width;
		::DrawText(mh_draw_dc, p->m_item_name, p->m_len, &r, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		r.left = r.right;
		p++;										// ���� �迭�� �̵�

		::MoveToEx(mh_draw_dc, r.right, m_rect.top, NULL);
		::LineTo(mh_draw_dc, r.right, m_rect.bottom);
	}
}

void HeaderGrid::RedrawItemData()
{
	DrawHeaderItem();			// �̹��� ��ü�� �ٽ� �׸��� �׸���.
	Invalidate(0);						// �̹��� ��ü�� ȭ�鿡 ����Ѵ�. 
}