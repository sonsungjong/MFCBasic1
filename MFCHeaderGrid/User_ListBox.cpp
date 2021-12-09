// TW_ListBox.cpp: 구현 파일
#include "pch.h"
#include "User_ListBox.h"

// User_ListBox
IMPLEMENT_DYNAMIC(User_ListBox, CListBox)

User_ListBox::User_ListBox()
{
	// 리스트 박스가 사용할 색상 정보를 구성한다.
	m_bk_brush_color = RGB(32, 38, 46);
	m_select_brush_color = m_focus_brush_color = RGB(49, 52, 70);

	m_focus_pen_color = m_select_pen_color = RGB(102, 117, 144);
	m_bk_pen_color = m_bk_brush_color;
}

User_ListBox::~User_ListBox()
{
}

BEGIN_MESSAGE_MAP(User_ListBox, CListBox)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_DRAWITEM_REFLECT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_CONTROL_REFLECT(LBN_DBLCLK, &User_ListBox::OnLbnDblclk)
	ON_MESSAGE(44001, &User_ListBox::On44001)
END_MESSAGE_MAP()

// TW_ListBox 메시지 처리기
HBRUSH User_ListBox::CtlColor(CDC * /*pDC*/, UINT /*nCtlColor*/)
{
	return mh_list_bk_brush;
}

// 각 항목의 배경을 그리기 위해 사용할 함수
void User_ListBox::BaseDraw(HDC ah_dc, RECT *ap_rect)
{
	// 전체 갱신, 포커스드 갱신, 선택 갱신인 경우에 처리한다.
	if (mp_last_lpds->itemAction & 0x07) { // 0x07 = ODA_DRAWENTIRE|ODA_FOCUS|ODA_SELECT
		// 색상만 변경해서 사용하는 펜과 브러시 객체를 선택한다.
		::SelectObject(ah_dc, ::GetStockObject(DC_BRUSH));
		::SelectObject(ah_dc, ::GetStockObject(DC_PEN));
		// 현재 선택된 상태인지 체크한다.
		if (mp_last_lpds->itemState & ODS_SELECTED) {
			// 선택된 상태의 펜 색상을 설정한다.
			::SetDCPenColor(ah_dc, m_select_pen_color);
			// 포커스 상태인지 체크하고 포커스 상태라면 조금더 
			// 밝은 배경색을 사용하고 아니라면 배경색과 동일한 색상을 사용한다.
			if (mp_last_lpds->itemState & ODS_FOCUS) {
				::SetDCBrushColor(ah_dc, m_focus_brush_color);
			} else ::SetDCBrushColor(ah_dc, m_select_brush_color);
		} else {
			// 선택된 상태가 아니라면 배경색과 같은 브러시와 펜을 사용한다.
			::SetDCPenColor(ah_dc, m_bk_pen_color);
			::SetDCBrushColor(ah_dc, m_bk_brush_color);
		}
		// 항목의 배경을 그린다.
		::Rectangle(ah_dc, ap_rect->left, ap_rect->top, ap_rect->right, ap_rect->bottom);
	}
}

void User_ListBox::DrawItem(LPDRAWITEMSTRUCT lpds)
{
	// 각 함수의 인자로 넘어갈 정보를 멤버로 백업해서 사용한다.
	mp_last_lpds = lpds;

	// 유효한 항목의 인덱스인지 체크한다.
	if ((UINT)lpds->itemID < (UINT)GetCount()) {
		// 각 항목의 배경을 그린다.
		BaseDraw(lpds->hDC, &lpds->rcItem);
		// 선택된 항목의 정보를 출력한다.
		UserDraw(lpds->hDC, &lpds->rcItem, (void *)lpds->itemData);
	}
}

void User_ListBox::CreateMemoryDC()
{
	CRect r;
	GetClientRect(r);					// 리스트박스의 클라이언트 영역을 얻는다
	m_draw_image.Create(r.Width(), r.Height(), 32);						// 리스트박스 전체 영역을 덮을 수 있는 이미지 객체를 만든다
	mh_draw_dc = m_draw_image.GetDC();									// 이미지 객체에 글미을 그릴때 사용할 DC를 얻는다.

	// 생성된 이미지에 리스트박스 배경 색상 적용
	::SelectObject(mh_draw_dc, ::GetStockObject(DC_BRUSH));
	::SelectObject(mh_draw_dc, ::GetStockObject(DC_PEN));
	::SetDCBrushColor(mh_draw_dc, m_bk_brush_color);
	::SetDCPenColor(mh_draw_dc, m_bk_pen_color);
	::Rectangle(mh_draw_dc, r.left, r.top, r.right, r.bottom);
}

int User_ListBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListBox::OnCreate(lpCreateStruct) == -1) return -1;

	// 리스트박스 그리기에 사용할 메모리 DC생성
	CreateMemoryDC();

	// 리스트 박스가 배경 채우기용으로 사용할 브러시를 생성한다.
	mh_list_bk_brush = ::CreateSolidBrush(m_bk_brush_color);
	// 상속된 클래스에서 리스트 박스 생성시에 함께 작업할 내용이
	// 있다면 이 함수를 오버라이딩해서 사용!
	CreateUserObject();
	return 0;
}

void User_ListBox::OnDestroy()
{
	CListBox::OnDestroy();

	// 상속된 클래스에서 리스트 박스 제거시에 함께 작업할 내용이
	// 있다면 이 함수를 오버라이딩해서 사용!
	DeleteUserObject();
	// 리스트 박스가 배경 채우기용으로 사용할 브러시를 제거한다.
	::DeleteObject(mh_list_bk_brush);

	// DC를 반납하고 제거
	m_draw_image.ReleaseDC();
	m_draw_image.Destroy();
}

void User_ListBox::PreSubclassWindow()
{
	CListBox::PreSubclassWindow();

	// 리스트박스 그리기에 사용할 메모리 DC생성
	CreateMemoryDC();
	// 리스트 박스가 배경 채우기용으로 사용할 브러시를 생성한다.
	mh_list_bk_brush = ::CreateSolidBrush(m_bk_brush_color);
	// 상속된 클래스에서 리스트 박스 생성시에 함께 작업할 내용이 있다면 이 함수를 오버라이딩해서 사용!
	CreateUserObject();
}

// 리스트 박스의 특정 항목 위치만 갱신하는 함수
void User_ListBox::UpdateItemInfo(int a_index, int a_count)
{
	CRect r;
	if (a_count == 1) GetItemRect(a_index, r);  // 선택한 항목의 좌표를 얻는다.
	else {
		CRect temp_rect;
		// 원하는 항목 개수만큼 반복하면서 영역을 합친다.
		for (int i = 0; i < a_count; i++) {
			GetItemRect(a_index + i, temp_rect);  // 선택한 항목의 좌표를 얻는다.
			r.UnionRect(r, temp_rect);  // r 영역에 temp_rect영역을 합친다.
		}
	}
	InvalidateRect(r, 0);  // r영역만 갱신한다.
}

void User_ListBox::OnLbnDblclk()
{
	POINT pos;
	// 현재 마우스 위치를 얻는다.
	GetCursorPos(&pos);
	// 마우스 좌표를 리스트 박스 기준으로 변경한다.
	ScreenToClient(&pos);

	BOOL out_side_flag = 0;
	// 마우스가 위치한 곳에 있는 항목의 위치 값을 구한다.
	// 항목이 없는 곳이면 항목의 갯수에 해당하는 값이 반환한다.
	// 예를 들어, 항목이 6개면 유효 인덱스는 0~5까지인데 빈곳을
	// 클릭하면 6이 나옵니다. 그리고 이때는 out_side_flag 값이 
	// 1이 되기 때문에 이 값을 함께 체크하는 것이 안전합니다.
	UINT index = ItemFromPoint(pos, out_side_flag);
	UINT check_index = GetCurSel();
	if (!out_side_flag && index == check_index) {
		// index 위치가 유효한 경우에만 더블 클릭을 수행!
		ProcessDoubleClicked(check_index);
	}
}


afx_msg LRESULT User_ListBox::On44001(WPARAM wParam, LPARAM lParam)
{
	SetBuddyMessage(wParam, (void*)lParam);
	return 0;
}

// Invalidate 재정의
void User_ListBox::Invalidate(BOOL bErase)
{
	CRect r;
	GetClientRect(r);
	if (bErase) {					// 배경지우기 옵션
		::SelectObject(mh_draw_dc, ::GetStockObject(DC_BRUSH));
		::SelectObject(mh_draw_dc, ::GetStockObject(DC_PEN));
		::SetDCBrushColor(mh_draw_dc, m_bk_brush_color);
		::SetDCPenColor(mh_draw_dc, m_bk_pen_color);
		::Rectangle(mh_draw_dc, r.left, r.top, r.right, r.bottom);
	}
	if (GetCount() > 0) {
		int item_cy = GetItemHeight(0);
		// 실제 보여지는 항목의 갯수
		int show_count = r.Height() / item_cy;
		// 항목수가 높이와 일치하지 않으면 (일부만 걸쳐있으면) 1만큼 더해줌
		if (r.Height() % GetItemHeight(0)) {show_count++;}
		int top_index = GetTopIndex(), select_index = GetCurSel();
		int count = GetCount() - top_index;
		if (count > show_count) { count = show_count; }
		DRAWITEMSTRUCT dis;
		dis.CtlType = ODT_LISTBOX;							// 컨트롤 종류
		dis.CtlID = GetDlgCtrlID();								// 컨트롤 아이디
		dis.itemAction = 0x07;									// 그리기가 발생한 이유
		dis.hwndItem = m_hWnd;
		dis.hDC = mh_draw_dc;

		for (int i = 0; i < count; i++) {
			dis.itemID = i + top_index;
			dis.itemState = select_index == dis.itemID;						// ODS_SELECTED
			dis.rcItem.left = 0;
			dis.rcItem.right = r.right;
			dis.rcItem.top = i * item_cy;
			dis.rcItem.bottom = (i + 1) * item_cy;
			
			dis.itemData = GetItemData(dis.itemID);

			mp_last_lpds = &dis;

			BaseDraw(dis.hDC, &dis.rcItem);
			UserDraw(dis.hDC, &dis.rcItem, (void*)dis.itemData);
		}
	}
	HDC h_dc = ::GetDC(m_hWnd);
	// 이미지 객체에 그려진 내용을 리스트박스 전체 영역에 출력
	::BitBlt(h_dc, 0, 0, r.Width(), r.Height(), mh_draw_dc, 0, 0, SRCCOPY);
	::ReleaseDC(m_hWnd, h_dc);
}