// MY_GridListCtrl.cpp : implementation file
//

#include "pch.h"
#include "GridListCtrl2.h"
#include "MY_GridListCtrl.h"


// MY_GridListCtrl

IMPLEMENT_DYNAMIC(MY_GridListCtrl, CListCtrl)

MY_GridListCtrl::MY_GridListCtrl()
{

}

MY_GridListCtrl::~MY_GridListCtrl()
{
}

void MY_GridListCtrl::SetGridLine()
{
	LVITEM item;
	::ZeroMemory(&item, sizeof(item));
	item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	item.pszText = _T("TEST ITEM");
	item.iItem = 5;
	item.iImage = 1;
	item.state = LVIS_SELECTED | LVIS_FOCUSED;

	// 격자 모양 추가 후 컬럼 추가
	this->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);							// 격자 추가
	this->InsertColumn(0, _T("No"), LVCFMT_LEFT, 40);
	this->InsertColumn(1, _T("Name"), LVCFMT_LEFT, 100);
	this->InsertColumn(2, _T("Kor"), LVCFMT_LEFT, 60);
	this->InsertColumn(3, _T("Eng"), LVCFMT_LEFT, 60);
	this->InsertColumn(4, _T("Math"), LVCFMT_LEFT, 60);
	this->InsertColumn(5, _T("Sum"), LVCFMT_CENTER, 100);
	this->InsertColumn(6, _T("Avg"), LVCFMT_CENTER, 60);
	this->ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	// 항목 삽입
	CString strItem = _T("");
	for (int i = 1; i <= 30; i++) {
		strItem.Format(_T("%d"), i);
		this->InsertItem(i, strItem, i);
	}

	for (int i = 0; i < 30; i++) {
		this->SetItem(i, 1, LVIF_TEXT, _T("item"), NULL, NULL, NULL, NULL);
		this->SetItem(i, 2, LVIF_TEXT, _T("33"), NULL, NULL, NULL, NULL);
		this->SetItem(i, 3, LVIF_TEXT, _T("44"), NULL, NULL, NULL, NULL);
		this->SetItem(i, 4, LVIF_TEXT, _T("55"), NULL, NULL, NULL, NULL);
		this->SetItem(i, 5, LVIF_TEXT, _T("22"), NULL, NULL, NULL, NULL);
		this->SetItem(i, 6, LVIF_TEXT, _T("10.1"), NULL, NULL, NULL, NULL);
	}
}


BEGIN_MESSAGE_MAP(MY_GridListCtrl, CListCtrl)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()



// MY_GridListCtrl message handlers




int MY_GridListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}


void MY_GridListCtrl::OnDestroy()
{
	CListCtrl::OnDestroy();

	// TODO: Add your message handler code here
}


void MY_GridListCtrl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	m_last_lpds = lpDrawItemStruct;				// 멤버로 백업
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	UINT itemState = lpDrawItemStruct->itemState;
	int itemID = lpDrawItemStruct->itemID;

	// Draw item background
	pDC->FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_WINDOW));

	if (itemID >= 0)
	{
		// Draw item text
		CString strText;
		this->GetItemText(itemID, 0, strText);  // assuming the text is in the first column
		pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
		pDC->DrawText(strText, &lpDrawItemStruct->rcItem, DT_LEFT);
	}
	CListCtrl::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
