// DataListWnd.cpp : implementation file
//

#include "pch.h"
#include "MFCL230DataList.h"
#include "DataListWnd.h"


// DataListWnd

IMPLEMENT_DYNAMIC(DataListWnd, CWnd)

DataListWnd::DataListWnd()
{

}

DataListWnd::~DataListWnd()
{
}


BEGIN_MESSAGE_MAP(DataListWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()



// DataListWnd message handlers


int DataListWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) {
		return -1;
	}
	// TODO:  Add your specialized creation code here
	GetClientRect(&m_view_rect);
	m_view_cx = m_view_rect.Width();
	m_view_cy = m_view_rect.Height();
	m_item_view_count = m_view_cy / ITEM_HEIGHT;
	if ((m_view_cy % ITEM_HEIGHT) != 0) {
		m_item_view_count++;
	}

	SetScrollRange(SB_VERT, 0, MAX_GROUP_COUNT - m_item_view_count + 1, 0);

	// 이미지 만들고
	m_draw_image.Create(m_view_rect.Width(), m_view_rect.Height(), 32);
	// DC와 연결하고
	m_draw_dc.Attach(m_draw_image.GetDC());

	// 펜과 브러시 셋팅
	m_bk_brush.CreateSolidBrush(RGB(61, 77, 103));
	m_bk_pen.CreatePen(PS_SOLID, 1, RGB(61, 77, 103));
	m_grid_pen.CreatePen(PS_SOLID, 1, RGB(71, 93, 123));

	DrawData();

	memset(m_data_list, 0, sizeof(m_data_list));

	return 0;
}

void DataListWnd::DrawData()
{
	m_draw_dc.SelectObject(&m_bk_brush);
	m_draw_dc.SelectObject(&m_bk_pen);
	m_draw_dc.Rectangle(m_view_rect);

	m_draw_dc.SetBkColor(RGB(61, 77, 103));							// 글자 자체 배경색 변경
	m_draw_dc.SetTextColor(RGB(0, 200, 255));				// 글자색 변경

	int scroll_pos = GetScrollPos(SB_VERT), count = m_item_view_count;
	if (count + scroll_pos >= MAX_GROUP_COUNT) {
		count--;
	}

	m_draw_dc.SelectObject(&m_grid_pen);

	int *p;
	int len;

	if (m_state_check) {
		for (int i = 0; i < count; i++) {
			p = m_data_list[i + scroll_pos];

			m_draw_dc.SetTextColor(RGB(190, 190, 190));
			len = _stprintf_s(m_temp_string, 128, _T("Group %03d :"), i + scroll_pos + 1);
			m_draw_dc.TextOut(5, i * ITEM_HEIGHT + 2, m_temp_string, len);

			for (int sub_i = 0; sub_i < MAX_VALUE_COUNT; sub_i++)
			{
				len = _stprintf_s(m_temp_string, 128, _T("%03d,"), *p);
				if (*p < 100) {
					m_draw_dc.SetTextColor(RGB(0, 255, 100));
				}
				else if(*p > 900){
					m_draw_dc.SetTextColor(RGB(255, 0, 100));
				}
				else {
					m_draw_dc.SetTextColor(RGB(0, 200, 255));
				}
				m_draw_dc.TextOut(84+sub_i*32, i * ITEM_HEIGHT + 2, m_temp_string, len);
				p++;

			}

			m_draw_dc.MoveTo(3, (i + 1) * ITEM_HEIGHT - 2);
			m_draw_dc.LineTo(m_view_cx - 3, (i + 1) * ITEM_HEIGHT - 2);
		}
	}
	else {
		for (int i = 0; i < count && i + scroll_pos < MAX_GROUP_COUNT; i++) {
			p = m_data_list[i + scroll_pos];
			len = _stprintf_s(m_temp_string, 128, _T("Group %03d : %03d, %03d, %03d, %03d, %03d"), i+scroll_pos+1, *p, *(p+1), *(p+2), *(p+3), *(p+4));

			m_draw_dc.TextOut(5, i * ITEM_HEIGHT + 2, m_temp_string, len);
			m_draw_dc.MoveTo(3, (i + 1) * ITEM_HEIGHT - 2);
			m_draw_dc.LineTo(m_view_cx - 3, (i + 1) * ITEM_HEIGHT - 2);
		}
	}
}

void DataListWnd::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
	m_draw_dc.Detach();
	m_draw_image.ReleaseDC();
	m_draw_image.Destroy();

	m_bk_brush.DeleteObject();
	m_bk_pen.DeleteObject();
	m_grid_pen.DeleteObject();
}


void DataListWnd::OnPaint()
{
	CPaintDC dc(this);
	m_draw_image.Draw(dc, 0, 0);

}


void DataListWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar == NULL) {
		ProcessScroll(nSBCode, nPos, SB_VERT);
		DrawData();
		Invalidate(FALSE);
	}

	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void DataListWnd::UpdateData(int a_index, int* ap_data)
{
	if (a_index < MAX_GROUP_COUNT) {
		memcpy(m_data_list + a_index, ap_data, sizeof(int) * MAX_VALUE_COUNT);
	}
}

void DataListWnd::Redraw()
{
	DrawData();

	// CPaintDC : WM_PAINT 할 때 사용되는 DC
	// CClientDC : 

	CClientDC dc(this);
	m_draw_image.Draw(dc, 0, 0);
	
}


void DataListWnd::ProcessScroll(UINT nSBCode, UINT nPos, int a_scroll_type)
{
	if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK)
	{
		SetScrollPos(a_scroll_type, nPos);
	}
	else {
		int scroll_pos = GetScrollPos(a_scroll_type), min = 0, max = 0;
		GetScrollRange(a_scroll_type, &min, &max);
		switch (nSBCode)
		{
		case SB_LINEDOWN:
			if (scroll_pos < max) { SetScrollPos(a_scroll_type, scroll_pos + 1); }
			break;
		case SB_LINEUP:
			if (scroll_pos > min) { SetScrollPos(a_scroll_type, scroll_pos - 1); }
			break;
		case SB_PAGEDOWN:
			if (scroll_pos + 10 < max) { SetScrollPos(a_scroll_type, scroll_pos + 10); }
			break;
		case SB_PAGEUP:
			if (scroll_pos - 10 > min) { SetScrollPos(a_scroll_type, scroll_pos - 10); }
			break;
		}
	}
}

void DataListWnd::SetStateCheck(int a_state)
{
	m_state_check = a_state;
	Redraw();
}