// SJ_ListBox.cpp : implementation file
//

#include "pch.h"
#include "MFCL104ListBoxOwnerDrawLib.h"
#include "SJ_ListBox.h"


// SJ_ListBox

IMPLEMENT_DYNAMIC(SJ_ListBox, CListBox)

SJ_ListBox::SJ_ListBox() : m_list_box_brush(RGB(0,0,128))
{

}

SJ_ListBox::~SJ_ListBox()
{
}


BEGIN_MESSAGE_MAP(SJ_ListBox, CListBox)
	ON_WM_DRAWITEM_REFLECT()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// SJ_ListBox message handlers
void SJ_ListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here

	// 예외처리
	if (lpDrawItemStruct->itemID != 0xFFFFFFFF) {
		if ((lpDrawItemStruct->itemAction & ODA_DRAWENTIRE) || (lpDrawItemStruct->itemAction & ODA_FOCUS) || (lpDrawItemStruct->itemAction & ODA_SELECT))
		{
			CDC* p_dc = CDC::FromHandle(lpDrawItemStruct->hDC);				// 깡통WrapperClass

			if (lpDrawItemStruct->itemState & ODS_SELECTED) {			// 선택시
				p_dc->FillSolidRect(&lpDrawItemStruct->rcItem, RGB(0, 200, 255));
				p_dc->SetTextColor(RGB(255, 255, 0));
			}
			else {
				p_dc->FillSolidRect(&lpDrawItemStruct->rcItem, RGB(0, 0, 128));
				p_dc->SetTextColor(RGB(200, 200, 200));
			}

			CString str;
			GetText(lpDrawItemStruct->itemID, str);
			p_dc->TextOut(lpDrawItemStruct->rcItem.left + 5, lpDrawItemStruct->rcItem.top + 6, str);
		}
	}
	
}


HBRUSH SJ_ListBox::CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/)
{
	// TODO:  Change any attributes of the DC here

	// TODO:  Return a non-NULL brush if the parent's handler should not be called
	return m_list_box_brush;
}
