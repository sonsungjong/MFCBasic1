// SJ_Edit.cpp : implementation file
//

#include "pch.h"
#include "MFCL206EditCtrl2.h"
#include "SJ_Edit.h"


// SJ_Edit

IMPLEMENT_DYNAMIC(SJ_Edit, CEdit)

SJ_Edit::SJ_Edit()
{
	// OnInitialDialog�� �ִ� �ڵ�
	m_edit_focus_text_color = RGB(100, 228, 100);
	m_edit_text_color = RGB(255, 228, 0);
	m_edit_bk_color = RGB(93, 93, 93);
	mh_edit_bk_brush = ::CreateSolidBrush(m_edit_bk_color);
}

SJ_Edit::~SJ_Edit()
{
	// OnDestroy�� �ִ� �ڵ�
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
		// ��Ŀ�� ��
		pDC->SetTextColor(m_edit_focus_text_color);			// ���ڻ�
	}
	else {
		// ��Ŀ�� �ƴ� ��
		pDC->SetTextColor(m_edit_text_color);			// ���ڻ�
	}
	pDC->SetBkColor(m_edit_bk_color);						// ����
	return mh_edit_bk_brush;									// �ڽ� ����
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

	// �������� brush ����
	DeleteObject(mh_edit_bk_brush);

	// �ٲ� �귯�÷� �����
	mh_edit_bk_brush = ::CreateSolidBrush(m_edit_bk_color);
}