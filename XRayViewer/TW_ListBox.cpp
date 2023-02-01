#include "pch.h"
#include "XRayViewer.h"
#include "TW_ListBox.h"


IMPLEMENT_DYNAMIC(TW_ListBox, CListBox)

TW_ListBox::TW_ListBox() : m_list_box_bk_brush(RGB(30,30,30))
{
	m_select_color = RGB(52, 60, 100);
	m_focus_color = RGB(48, 78, 168);
	m_bk_color = RGB(30, 30, 30);
}

TW_ListBox::~TW_ListBox()
{
}


BEGIN_MESSAGE_MAP(TW_ListBox, CListBox)
	ON_WM_DRAWITEM_REFLECT()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

// 리스트박스 메시지처리기 (상속용 =WM_DRAWITEM)
void TW_ListBox::DrawItem(LPDRAWITEMSTRUCT lpds)
{
	// TODO: Add your message handler code here
	if (lpds->itemID != 0xFFFFFFFF && lpds->itemID < (UINT)GetCount()) {
		if ((lpds->itemAction & ODA_DRAWENTIRE) || (lpds->itemAction & ODA_FOCUS) || (lpds->itemAction & ODA_SELECT)) {
			DrawListItem(CDC::FromHandle(lpds->hDC), &lpds->rcItem, lpds->itemID, (void*)lpds->itemData, lpds->itemState & ODS_SELECTED, lpds->itemState & ODS_FOCUS);
		}
	}
}

// 글자 및 배경색 (상속용 =WM_CTLCOLOR)
HBRUSH TW_ListBox::CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/)
{
	// TODO:  Change any attributes of the DC here

	// TODO:  Return a non-NULL brush if the parent's handler should not be called
	return m_list_box_bk_brush;
}

void TW_ListBox::DrawUserItem(CDC* ap_dc, RECT* ap_rect, int a_index, void* ap_data, unsigned char a_select_flag, unsigned char a_focus_flag)
{
	if (a_select_flag) {
		ap_dc->SetTextColor(RGB(255, 255, 0));
	}
	else {
		ap_dc->SetTextColor(RGB(128, 128, 0));
	}

	CString str;
	GetText(a_index, str);
	ap_dc->TextOut(ap_rect->left + 5, ap_rect->top + 6, str);
}

void TW_ListBox::DrawListItem(CDC* ap_dc, RECT* ap_rect, int a_index, void* ap_data, unsigned char a_select_flag, unsigned char a_focus_flag)
{
	if (a_select_flag) {
		if (a_focus_flag) {
			ap_dc->FillSolidRect(ap_rect, m_focus_color);
		}
		else {
			ap_dc->FillSolidRect(ap_rect, m_select_color);
		}
	}
	else {
		ap_dc->FillSolidRect(ap_rect, m_bk_color);
	}
	DrawUserItem(ap_dc, ap_rect, a_index, ap_data, a_select_flag, a_focus_flag);
}

void TW_ListBox::SetItemColor(COLORREF a_select_color, COLORREF a_focus_color, COLORREF a_bk_color)
{
	m_select_color = a_select_color;
	m_focus_color = a_focus_color;
	m_bk_color = a_bk_color;

	m_list_box_bk_brush.DeleteObject();
	m_list_box_bk_brush.CreateSolidBrush(m_bk_color);
}