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
	m_font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	SendMessage(WM_SETFONT, (WPARAM)m_font, (LPARAM)TRUE);

	LVITEM item;
	::ZeroMemory(&item, sizeof(item));
	item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	item.pszText = _T("TEST ITEM");
	item.iItem = 5;
	item.iImage = 1;
	item.state = LVIS_SELECTED | LVIS_FOCUSED;

	// 격자 모양 추가 후 컬럼 추가
	SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER);							// 격자 | 행선택 | 더블버퍼
	InsertColumn(0, _T("No"), LVCFMT_CENTER, 40);
	InsertColumn(1, _T("Name"), LVCFMT_CENTER, 100);
	InsertColumn(2, _T("Kor"), LVCFMT_CENTER, 60);
	InsertColumn(3, _T("Eng"), LVCFMT_CENTER, 60);
	InsertColumn(4, _T("Math"), LVCFMT_CENTER, 60);
	InsertColumn(5, _T("Sum"), LVCFMT_CENTER, 100);
	InsertColumn(6, _T("Avg"), LVCFMT_CENTER, 60);
	InsertColumn(7, _T("상세 보기"), LVCFMT_CENTER, 100);
	ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	CString strItem;
	// 항목 삽입
	for (int i = 0; i < 30; i++) {
		strItem.Format(_T("%d"), i+1);
		InsertItem(i, strItem);
		SetItem(i, 1, LVIF_TEXT, _T("item"), NULL, NULL, NULL, NULL);
		SetItem(i, 2, LVIF_TEXT, _T("33"), NULL, NULL, NULL, NULL);
		SetItem(i, 3, LVIF_TEXT, _T("44"), NULL, NULL, NULL, NULL);
		SetItem(i, 4, LVIF_TEXT, _T("55"), NULL, NULL, NULL, NULL);
		SetItem(i, 5, LVIF_TEXT, _T("22"), NULL, NULL, NULL, NULL);
		SetItem(i, 6, LVIF_TEXT, _T("10.1"), NULL, NULL, NULL, NULL);
		// SetBtn 7
	}

}

void MY_GridListCtrl::SetGridLine2()
{
	// 리스트컨트롤 Font
	m_font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_MODERN, _T("맑은 고딕"));
	SendMessage(WM_SETFONT, (WPARAM)m_font, (LPARAM)TRUE);

	// 리스트 컨트롤 기본 설정
	LVITEM item;
	::ZeroMemory(&item, sizeof(item));
	item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	item.pszText = _T("LIG");
	item.iItem = 5;
	item.iImage = 1;
	item.state = LVIS_SELECTED | LVIS_FOCUSED;

	// 격자 모양 추가 후 컬럼 추가
	SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);							// 격자 추가
	InsertColumn(0, _T("No"), LVCFMT_LEFT, 40);
	InsertColumn(1, _T("부대명"), LVCFMT_LEFT, 120);
	InsertColumn(2, _T("재고번호"), LVCFMT_CENTER, 180);
	InsertColumn(3, _T("일련번호"), LVCFMT_CENTER, 180);
	InsertColumn(4, _T("탄종"), LVCFMT_CENTER, 120);
	InsertColumn(5, _T("온도"), LVCFMT_CENTER, 120);
	InsertColumn(6, _T("습도"), LVCFMT_CENTER, 120);
	InsertColumn(7, _T("충격량"), LVCFMT_CENTER, 120);
	InsertColumn(8, _T("지역"), LVCFMT_CENTER, 120);
	InsertColumn(9, _T("이상여부"), LVCFMT_CENTER, 120);
	InsertColumn(10, _T("권장점검일"), LVCFMT_CENTER, 180);
	InsertColumn(11, _T("상태"), LVCFMT_CENTER, 60);
	InsertColumn(12, _T("상세 보기"), LVCFMT_CENTER, 100);
	ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	CString strItem;
	// 항목 갯수 30개
	for (int i = 0; i < 30; i++) {
		strItem.Format(_T("%d"), i + 1);
		InsertItem(i, strItem);
		SetItem(i, 1, LVIF_TEXT, _T("한국"), NULL, NULL, NULL, NULL);
		SetItem(i, 2, LVIF_TEXT, _T("1430010876337"), NULL, NULL, NULL, NULL);
		SetItem(i, 3, LVIF_TEXT, _T("JN17148851"), NULL, NULL, NULL, NULL);
		SetItem(i, 4, LVIF_TEXT, _T("천궁"), NULL, NULL, NULL, NULL);
		SetItem(i, 5, LVIF_TEXT, _T("-36.5℃"), NULL, NULL, NULL, NULL);
		SetItem(i, 6, LVIF_TEXT, _T("20℃"), NULL, NULL, NULL, NULL);
		SetItem(i, 7, LVIF_TEXT, _T("9.8"), NULL, NULL, NULL, NULL);
		SetItem(i, 8, LVIF_TEXT, _T("서울"), NULL, NULL, NULL, NULL);
		SetItem(i, 9, LVIF_TEXT, _T("이상"), NULL, NULL, NULL, NULL);
		SetItem(i, 10, LVIF_TEXT, _T("2028-03-21"), NULL, NULL, NULL, NULL);
		SetItem(i, 11, LVIF_TEXT, _T("C"), NULL, NULL, NULL, NULL);
		// SetBtn 12
	}

	
}


BEGIN_MESSAGE_MAP(MY_GridListCtrl, CListCtrl)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_MEASUREITEM()
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




void MY_GridListCtrl::MyDraw(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	int index = lpDrawItemStruct->itemID;

	if (index >= 0 && index < GetItemCount())
	{
		CDC* dc = CDC::FromHandle(lpDrawItemStruct->hDC);
		CRect r = lpDrawItemStruct->rcItem;

		if (lpDrawItemStruct->itemState & ODS_SELECTED)
		{
			// 선택 라인에 대해 글자색과 영역색
			dc->SetTextColor(RGB(30, 30, 250));
			dc->FillSolidRect(r, RGB(188, 231, 241));
		}
		else
		{
			// 선택이 안된 경우
			dc->SetTextColor(RGB(0, 0, 0));
			dc->FillSolidRect(r, RGB(255, 255, 255));
		}

		LV_COLUMN column_data;
		column_data.mask = LVCF_WIDTH;

		CString str;
		// 각 컬럼은 앞쪽 5만큼 여백을 갖고 문자열을 출력한다
		// 리스트 컨트롤이 갖고 있는 헤더 컨트롤의 포인터를 얻어서 컬럼수를 구한다
		int blank = 10;
		int header_count = GetHeaderCtrl()->GetItemCount();

		// 반복문을 돌려 TextOut으로 그린다 (만약 마지막 컬럼만 다른 컨트롤로 주고 싶으면 -1)
		for (int i = 0; i < header_count; i++)
		{
			CRect rcSubItem;
			GetSubItemRect(index, i, LVIR_BOUNDS, rcSubItem);

			// 데이터를 얻는다
			str = GetItemText(index, i);
			if (i == 0) {
				dc->TextOut(r.left + blank, r.top + blank, str);
			}
			else if (i == header_count - 1)
			{
				COLORREF old_color = dc->SetTextColor(RGB(255, 255, 255));
				dc->FillSolidRect(&rcSubItem, RGB(0, 100, 255));
				dc->DrawText(_T("상세 보기"), &rcSubItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
				dc->SetTextColor(old_color);
			}
			else {
				dc->DrawText(str, &rcSubItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
			}


		}
	}
}
