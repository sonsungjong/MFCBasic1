// SJ_Edit.cpp : implementation file
//

#include "pch.h"
#include "MFCL206EditCtrl2.h"
#include "SJ_Edit.h"


// SJ_Edit

IMPLEMENT_DYNAMIC(SJ_Edit, CEdit)

SJ_Edit::SJ_Edit()
{
	// OnInitialDialog에 있던 코드
	m_edit_focus_text_color = RGB(100, 228, 100);
	m_edit_text_color = RGB(255, 228, 0);
	m_edit_bk_color = RGB(93, 93, 93);
	mh_edit_bk_brush = ::CreateSolidBrush(m_edit_bk_color);
}

SJ_Edit::~SJ_Edit()
{
	// OnDestroy에 있던 코드
	DeleteObject(mh_edit_bk_brush);
}




BEGIN_MESSAGE_MAP(SJ_Edit, CEdit)
	ON_WM_CTLCOLOR_REFLECT()
	ON_CONTROL_REFLECT(EN_KILLFOCUS, &SJ_Edit::OnEnKillfocus)
END_MESSAGE_MAP()



// SJ_Edit message handlers




HBRUSH SJ_Edit::CtlColor(CDC* pDC, UINT nCtlColor)
{
	HWND cur_focus = ::GetFocus();
	if (cur_focus == m_hWnd) {
		// 포커스 시
		pDC->SetTextColor(m_edit_focus_text_color);			// 글자색
	}
	else {
		// 포커스 아닐 시
		pDC->SetTextColor(m_edit_text_color);			// 글자색
	}
	pDC->SetBkColor(m_edit_bk_color);						// 배경색
	return mh_edit_bk_brush;									// 박스 배경색
}


void SJ_Edit::OnEnKillfocus()
{
	Invalidate();
}

void SJ_Edit::ChangeColor(COLORREF a_edit_bk_color, COLORREF a_edit_text_color, COLORREF a_edit_focus_text_color)
{
	this->m_edit_bk_color = a_edit_bk_color;
	this->m_edit_text_color = a_edit_text_color;
	this->m_edit_focus_text_color = a_edit_focus_text_color;

	// 만들어놓은 brush 제거
	DeleteObject(mh_edit_bk_brush);

	// 바뀐 브러시로 재생성
	mh_edit_bk_brush = ::CreateSolidBrush(m_edit_bk_color);
}