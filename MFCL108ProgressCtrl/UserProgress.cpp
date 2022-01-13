#include "pch.h"
#include "UserProgress.h"

UserProgress::UserProgress() : m_rect(0,0,100,30)
{
	m_pos = 0;
	m_min = 0;
	m_max = 100;
	m_bk_color = RGB(0, 80, 160);
	m_fore_color = RGB(0, 160, 255);
}

UserProgress::~UserProgress(){}

void UserProgress::Create(CRect a_rect)
{
	m_rect = a_rect;
}

CRect UserProgress::GetRect()
{
	return m_rect;
}

void UserProgress::Update(CWnd* ap_parent)
{
	ap_parent->InvalidateRect(m_rect, 0);
}

void UserProgress::Create(CWnd* ap_parent, int a_guide_ctrl)
{
	ap_parent->GetDlgItem(a_guide_ctrl)->GetWindowRect(m_rect);
	ap_parent->ScreenToClient(m_rect);
}

void UserProgress::SetRange(int a_min, int a_max)
{
	if (a_max < a_min) {
		int temp = a_min;
		a_min = a_max;
		a_max = temp;
	}
	else if (a_max == a_min) {
		return;
	}

	m_min = a_min;
	m_max = a_max;
}

void UserProgress::SetPos(int a_pos)
{
	m_pos = a_pos;
	if (m_pos < m_min) m_pos = m_min;
	else if (m_pos > m_max) m_pos = m_max;
}

int UserProgress::GetPos()
{
	return m_pos;
}

void UserProgress::SetColor(COLORREF a_bk_color, COLORREF a_fore_color)
{
	m_bk_color = a_bk_color;
	m_fore_color = a_fore_color;
}

void UserProgress::Draw(CDC* ap_dc)
{
	int pos = m_pos * m_rect.Width() / (m_max - m_min);
	ap_dc->FillSolidRect(m_rect.left + pos, m_rect.top, m_rect.Width(), m_rect.Height(), m_bk_color);
	ap_dc->FillSolidRect(m_rect.left, m_rect.top, pos, m_rect.Height(), m_fore_color);
}