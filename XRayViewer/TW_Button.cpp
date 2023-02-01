#include "pch.h"
#include "XRayViewer.h"
#include "TW_Button.h"

IMPLEMENT_DYNAMIC(TW_Button, CButton)

TW_Button::TW_Button()
{
	m_btn_color = RGB(39, 43, 47);
	m_border_color = RGB(59, 63, 67);
	m_in_border_color = RGB(157, 171, 196);
	m_focus_btn_color = RGB(59, 63, 67);
	m_focus_border_color = RGB(109, 113, 117);
	m_text_color = RGB(232, 248, 248);
}

TW_Button::~TW_Button()
{
}

void TW_Button::ChangeColor(COLORREF a_focus_btn_color, COLORREF a_focus_border_color, COLORREF a_btn_color, COLORREF a_border_color, COLORREF a_in_border_color, COLORREF a_text_color)
{
	m_btn_color = a_btn_color;
	m_border_color = a_border_color;
	m_focus_btn_color = a_focus_btn_color;
	m_focus_border_color = a_focus_border_color;
	m_in_border_color = a_in_border_color;
	m_text_color = a_text_color;
}


BEGIN_MESSAGE_MAP(TW_Button, CButton)
END_MESSAGE_MAP()

// 중요! : 버튼 메시지 처리기 (MFC 가상함수)
void TW_Button::DrawItem(LPDRAWITEMSTRUCT lpds)
{
	// TODO:  Add your code to draw the specified item
	CRect rect(lpds->rcItem);				// RECT -> CRect 형변환
	CDC* p_dc = CDC::FromHandle(lpds->hDC);

	p_dc->SelectStockObject(DC_BRUSH);				// 사용자 지정 브러시 사용
	p_dc->SelectStockObject(DC_PEN);						// 사용자 지정 펜 사용

	if (lpds->itemState & ODS_FOCUS) {
		// 해당 버튼이 포커스 상태면
		p_dc->SetDCBrushColor(m_focus_btn_color);				// 버튼 포커싱 브러시색 지정
		p_dc->SetDCPenColor(m_focus_border_color);					// 버튼 포커싱 펜색 지정
	}
	else {
		// 해당 버튼이 포커스가 안된 기본 상태면
		p_dc->SetDCBrushColor(m_btn_color);					// 버튼 배경 브러시색 지정
		p_dc->SetDCPenColor(m_border_color);					// 버튼 테두리 펜색 지정
	}
	// 사각형을 그린다
	p_dc->Rectangle(rect);

	p_dc->SelectStockObject(NULL_BRUSH);				// 브러시색 제거
	p_dc->SetDCPenColor(m_in_border_color);				// 펜 색 변경
	p_dc->Rectangle(rect.left + 1, rect.top + 1, rect.right - 1, rect.bottom - 1);				// 안쪽에 사각형을 그린다

	// 버튼이 눌리면 살짝 아래쪽으로 이동시켜서 눌러진 느낌이 나게한다
	if (lpds->itemState & ODS_SELECTED) { rect += CPoint(1, 1); }

	CString str;
	GetWindowText(str);				// 버튼의 텍스트를 얻는다
	p_dc->SetBkMode(TRANSPARENT);				// 텍스트 배경 투명처리
	p_dc->SetTextColor(m_text_color);				// 텍스트색 설정
	p_dc->DrawText(str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);				// 글자 출력
}
