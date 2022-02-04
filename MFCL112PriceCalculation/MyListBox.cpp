// MyListBox.cpp : implementation file
//

#include "pch.h"
#include "MFCL112PriceCalculation.h"
#include "MyListBox.h"


// MyListBox

IMPLEMENT_DYNAMIC(MyListBox, CCheckListBox)

MyListBox::MyListBox()
{

}

MyListBox::~MyListBox()
{
}


BEGIN_MESSAGE_MAP(MyListBox, CCheckListBox)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// MyListBox message handlers




void MyListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  Add your code to draw the specified item
	CCheckListBox::DrawItem(lpDrawItemStruct);

	CDC* p_dc = CDC::FromHandle(lpDrawItemStruct->hDC);
	CString str;

	//ItemInfo* p = (ItemInfo*) GetItemDataPtr(lpDrawItemStruct->itemID);
	ItemInfo* p = (ItemInfo*) lpDrawItemStruct->itemData;

	if (p->count > 1) {
		str.Format(_T("(%d) %d개"), p->count*p->price, p->count);
	}else{ str.Format(_T("%d개"), p->count); }
	
	p_dc->SetBkMode(TRANSPARENT);
	if (lpDrawItemStruct->itemState & ODS_SELECTED) { p_dc->SetTextColor(RGB(255, 255, 255)); }
	else { p_dc->SetTextColor(RGB(0, 0, 0)); }
	p_dc->DrawText(str, &lpDrawItemStruct->rcItem, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
}


void MyListBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CCheckListBox::OnKeyDown(nChar, nRepCnt, nFlags);
	// TODO: Add your message handler code here and/or call default
	// 키보드를 마우스라고 속임
	GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(),LBN_SELCHANGE), (LPARAM)m_hWnd);
}
