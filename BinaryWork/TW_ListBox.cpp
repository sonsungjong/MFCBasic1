// TW_ListBox.cpp : implementation file
//

#include "pch.h"
#include "BinaryWork.h"
#include "TW_ListBox.h"


// TW_ListBox

IMPLEMENT_DYNAMIC(TW_ListBox, CListBox)

TW_ListBox::TW_ListBox()
{
	m_bk_brush_color = RGB(58, 62, 80);
	m_focus_brush_color = RGB(72, 87, 114);

	m_select_brush_color = m_focus_pen_color = m_select_pen_color = RGB(72, 87, 114);
	m_bk_pen_color = m_bk_brush_color;
}

TW_ListBox::~TW_ListBox()
{
}



BEGIN_MESSAGE_MAP(TW_ListBox, CListBox)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_DRAWITEM_REFLECT()
	ON_CONTROL_REFLECT(LBN_DBLCLK, &TW_ListBox::OnLbnDblclk)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()



// TW_ListBox message handlers

void TW_ListBox::BaseDraw(HDC ah_dc, RECT* ap_rect)
{
	// 전체 갱신, 포커스 갱신, 선택 갱신 처리
	if (mp_last_lpds->itemAction & 0x07) {
		::SelectObject(ah_dc, ::GetStockObject(DC_BRUSH));
		::SelectObject(ah_dc, ::GetStockObject(DC_PEN));
		// 선택상태인지 판단
		if (mp_last_lpds->itemState & ODS_SELECTED) {
			// 선택상태 펜으로 변경
			::SetDCPenColor(ah_dc, m_select_pen_color);
			// 포커스 상태인지 체크
			if (mp_last_lpds->itemState & ODS_FOCUS) {
				::SetDCBrushColor(ah_dc, m_focus_brush_color);
			}
			else {
				::SetDCBrushColor(ah_dc, m_select_brush_color);
			}
		}
		else {
			// 선택 상태가 아니면 배경과 같은 브러시/펜 사용
			::SetDCPenColor(ah_dc, m_bk_pen_color);
			::SetDCBrushColor(ah_dc, m_bk_brush_color);
		}
		// 배경
		::Rectangle(ah_dc, ap_rect->left, ap_rect->top, ap_rect->right, ap_rect->bottom);
	}
}

// 특정 항목만 수정하는 함수
void TW_ListBox::UpdateItemInfo(int a_index, int a_count)
{
	CRect r;
	if (a_count == 1) { GetItemRect(a_index, r); }
	else {
		CRect temp_rect;
		// 원하는 항목 개수만큼 반복하면서 영역을 합친다
		for (int i = 0; i < a_count; i++) {
			GetItemRect(a_index + i, temp_rect);
			r.UnionRect(r, temp_rect);
		}
	}
	InvalidateRect(r, FALSE);			// r영역만 갱신한다
}



HBRUSH TW_ListBox::CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/)
{
	// TODO:  Change any attributes of the DC here

	// TODO:  Return a non-NULL brush if the parent's handler should not be called
	return mh_list_bk_brush;
}


void TW_ListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here
	// 멤버로 백업
	mp_last_lpds = lpDrawItemStruct;

	// 유효한 항목의 인덱스인지 체크
	if ((UINT)lpDrawItemStruct->itemID < (UINT)GetCount()) {
		// 배경
		BaseDraw(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem);
		// 선택 항목 출력
		UserDraw(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, (void*)lpDrawItemStruct->itemData);
	}
}


int TW_ListBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	// 리스트 박스 배경용 브러시를 생성
	mh_list_bk_brush = ::CreateSolidBrush(m_bk_brush_color);

	// 상속받은 클래스에서 리스트 박스 생성시 함께 작업할 내용이 있다면 이 함수를 사용!
	CreateUserObject();

	return 0;
}


void TW_ListBox::OnDestroy()
{
	CListBox::OnDestroy();

	// TODO: Add your message handler code here
	// 상속받은 클래스에서 리스트박스 제거시에 함께 작업할 내용이 있다면 이 함수를 오버라이딩해서 사용!
	DeleteUserObject();

	// 배경용 브러시를 제거한다
	::DeleteObject(mh_list_bk_brush);
}


void TW_ListBox::OnLbnDblclk()
{
	// TODO: Add your control notification handler code here
	BOOL out_side_flag = 0;
	// 마우스가 위치한 곳의 항목 위치값을 구한다
	// 항목이 없는 곳이면 항목의 갯수를 반환한다
	UINT index = ItemFromPoint(m_last_dblclk_pos, out_side_flag);
	UINT check_index = GetCurSel();
	if (!out_side_flag && index == check_index) {
		// 유효한 위치일때만 더블 클릭 수행
		ProcessDoubleClicked(check_index);
	}
}


void TW_ListBox::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	// 좌표를 기억한다
	m_last_dblclk_pos = point;

	CListBox::OnLButtonDblClk(nFlags, point);
}


void TW_ListBox::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	// 리스트 박스 배경용 브러시 생성
	mh_list_bk_brush = ::CreateSolidBrush(m_bk_brush_color);

	// 상속받은 클래스에서 리스트 박스 생성 시 함께 작업할 내용이 있다면 이 함수를 사용! (오버라이딩)
	CreateUserObject();
	
}
