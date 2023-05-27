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
	// ��ü ����, ��Ŀ�� ����, ���� ���� ó��
	if (mp_last_lpds->itemAction & 0x07) {
		::SelectObject(ah_dc, ::GetStockObject(DC_BRUSH));
		::SelectObject(ah_dc, ::GetStockObject(DC_PEN));
		// ���û������� �Ǵ�
		if (mp_last_lpds->itemState & ODS_SELECTED) {
			// ���û��� ������ ����
			::SetDCPenColor(ah_dc, m_select_pen_color);
			// ��Ŀ�� �������� üũ
			if (mp_last_lpds->itemState & ODS_FOCUS) {
				::SetDCBrushColor(ah_dc, m_focus_brush_color);
			}
			else {
				::SetDCBrushColor(ah_dc, m_select_brush_color);
			}
		}
		else {
			// ���� ���°� �ƴϸ� ���� ���� �귯��/�� ���
			::SetDCPenColor(ah_dc, m_bk_pen_color);
			::SetDCBrushColor(ah_dc, m_bk_brush_color);
		}
		// ���
		::Rectangle(ah_dc, ap_rect->left, ap_rect->top, ap_rect->right, ap_rect->bottom);
	}
}

// Ư�� �׸� �����ϴ� �Լ�
void TW_ListBox::UpdateItemInfo(int a_index, int a_count)
{
	CRect r;
	if (a_count == 1) { GetItemRect(a_index, r); }
	else {
		CRect temp_rect;
		// ���ϴ� �׸� ������ŭ �ݺ��ϸ鼭 ������ ��ģ��
		for (int i = 0; i < a_count; i++) {
			GetItemRect(a_index + i, temp_rect);
			r.UnionRect(r, temp_rect);
		}
	}
	InvalidateRect(r, FALSE);			// r������ �����Ѵ�
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
	// ����� ���
	mp_last_lpds = lpDrawItemStruct;

	// ��ȿ�� �׸��� �ε������� üũ
	if ((UINT)lpDrawItemStruct->itemID < (UINT)GetCount()) {
		// ���
		BaseDraw(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem);
		// ���� �׸� ���
		UserDraw(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, (void*)lpDrawItemStruct->itemData);
	}
}


int TW_ListBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	// ����Ʈ �ڽ� ���� �귯�ø� ����
	mh_list_bk_brush = ::CreateSolidBrush(m_bk_brush_color);

	// ��ӹ��� Ŭ�������� ����Ʈ �ڽ� ������ �Բ� �۾��� ������ �ִٸ� �� �Լ��� ���!
	CreateUserObject();

	return 0;
}


void TW_ListBox::OnDestroy()
{
	CListBox::OnDestroy();

	// TODO: Add your message handler code here
	// ��ӹ��� Ŭ�������� ����Ʈ�ڽ� ���Žÿ� �Բ� �۾��� ������ �ִٸ� �� �Լ��� �������̵��ؼ� ���!
	DeleteUserObject();

	// ���� �귯�ø� �����Ѵ�
	::DeleteObject(mh_list_bk_brush);
}


void TW_ListBox::OnLbnDblclk()
{
	// TODO: Add your control notification handler code here
	BOOL out_side_flag = 0;
	// ���콺�� ��ġ�� ���� �׸� ��ġ���� ���Ѵ�
	// �׸��� ���� ���̸� �׸��� ������ ��ȯ�Ѵ�
	UINT index = ItemFromPoint(m_last_dblclk_pos, out_side_flag);
	UINT check_index = GetCurSel();
	if (!out_side_flag && index == check_index) {
		// ��ȿ�� ��ġ�϶��� ���� Ŭ�� ����
		ProcessDoubleClicked(check_index);
	}
}


void TW_ListBox::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	// ��ǥ�� ����Ѵ�
	m_last_dblclk_pos = point;

	CListBox::OnLButtonDblClk(nFlags, point);
}


void TW_ListBox::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	// ����Ʈ �ڽ� ���� �귯�� ����
	mh_list_bk_brush = ::CreateSolidBrush(m_bk_brush_color);

	// ��ӹ��� Ŭ�������� ����Ʈ �ڽ� ���� �� �Բ� �۾��� ������ �ִٸ� �� �Լ��� ���! (�������̵�)
	CreateUserObject();
	
}
