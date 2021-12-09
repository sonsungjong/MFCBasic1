#include "pch.h"
#include "SimpleListBox.h"
#include "HeaderGrid.h"

SimpleListBox::SimpleListBox(){}

void SimpleListBox::CreateUserObject()
{
	mh_font = ::CreateFont(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS, _T("굴림"));

	// 리스트박스 한 한목의 높이와 폭
	SetItemHeight(0, 18);
}

void SimpleListBox::DeleteUserObject()
{
	// 모든 항목 제거
	ResetContent();
	// 글꼴 제거
	::DeleteObject(mh_font);
}

void SimpleListBox::UserDraw(HDC ah_dc, RECT* ap_rect, void* ap_data)
{
	// 현재 그려지는 항목의 위치
	int index = mp_last_lpds->itemID;

	// 글꼴 설정
	::SelectObject(ah_dc, mh_font);
	// 문자열 배경은 투명처리
	::SetBkMode(ah_dc, TRANSPARENT);

	// 명령어 이름 출력에 사용할 색상 지정
	::SetTextColor(ah_dc, RGB(255,255,255));
	// 명령어 이름 출력
	const TCHAR* p_str_table[3] = {_T("myid"), _T("손성종"), _T("서울에서 살았을까")};
	RECT r;
	// top과 bottom은 고정
	r.top = ap_rect->top;
	r.bottom = ap_rect->bottom;
	// left와 right는 3개의 폭을 고려
	for (int i = 0; i < 3; i++) {
		r.left = ap_rect->left + m_position[i];
		r.right = ap_rect->left + m_position[i+1];
		::DrawText(ah_dc, p_str_table[i], _tcslen(p_str_table[i]), &r, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
	}
}

void SimpleListBox::ProcessDoubleClicked(int a_index)
{
	
}

void SimpleListBox::AddState(const TCHAR* ap_str, int a_state)
{
	// 상태 정보는 최대 2000개 까지만
	while (GetCount() > 2000) { DeleteString(0); }

	int index = InsertString(-1, ap_str);					// 상태 메시지 추가
	SetItemData(index, a_state);								// 상태 메시지 색상 설정
	SetCurSel(index);												// 추가된 메시지를 선택
}

void SimpleListBox::SetBuddyMessage(int a_count, void* ap_data)
{
	HID* p = (HID*)ap_data;
	int i, position = 0;
	for (i = 0; i < a_count; i++) {
		m_position[i] = position;
		position += p->width;
		p++;
	}
	m_position[i] = position;
	Invalidate();
}