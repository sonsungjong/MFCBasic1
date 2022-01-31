// SJ_ProgressCtrl.cpp : implementation file
//

#include "pch.h"
#include "MFCL108ProgressCtrl.h"
#include "SJ_ProgressCtrl.h"


// SJ_ProgressCtrl

IMPLEMENT_DYNAMIC(SJ_ProgressCtrl, CWnd)

SJ_ProgressCtrl::SJ_ProgressCtrl()
{
	m_pos = 0;
	m_min = 0;
	m_max = 100;

	m_bk_color = RGB(0, 80, 160);
	m_fore_color = RGB(0, 160, 255);
}

SJ_ProgressCtrl::~SJ_ProgressCtrl()
{
}


BEGIN_MESSAGE_MAP(SJ_ProgressCtrl, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// SJ_ProgressCtrl message handlers
void SJ_ProgressCtrl::CreateProgress(CWnd* ap_parent, CRect a_rect, int a_ctrl_id)
{
	Create(nullptr, nullptr, WS_CHILD | WS_VISIBLE, a_rect, ap_parent, a_ctrl_id);
}

void SJ_ProgressCtrl::CreateProgress(CWnd* ap_parent, int a_guide_ctrl_id, int a_ctrl_id)
{
	CRect r;
	ap_parent->GetDlgItem(a_guide_ctrl_id)->GetWindowRect(r);
	ap_parent->ScreenToClient(r);
	CreateProgress(ap_parent, r, a_ctrl_id);
}

void SJ_ProgressCtrl::SetRange(int a_min, int a_max)
{
	if (a_min == a_max) { return; }
	if (a_max < a_min) {
		m_max = a_min;
		m_min = a_max;
	}
	else {
		m_min = a_min;
		m_max = a_max;
	}
}

void SJ_ProgressCtrl::SetPos(int a_pos)
{
	m_pos = a_pos;
	if (m_pos < m_min) { m_pos = m_min; }
	else if (m_pos > m_max) { m_pos = m_max; }
}

int SJ_ProgressCtrl::GetPos()
{
	return m_pos;
}

void SJ_ProgressCtrl::SetColor(COLORREF a_bk_color, COLORREF a_fore_color)
{
	m_bk_color = a_bk_color;
	m_fore_color = a_fore_color;
}



void SJ_ProgressCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CWnd::OnPaint() for painting messages
	
	CDC* p_dc = m_mem_image.GetDC();
	int pos = m_pos * (m_width-2) / (m_max - m_min);

	// 배경색과 테두리색
	CBrush fill_brush1(m_bk_color), fill_brush2(m_fore_color);
	CPen border_pen1(PS_SOLID, 1, m_bk_color), border_pen2(PS_SOLID, 1, m_fore_color);

	CBrush* p_old_brush = p_dc->SelectObject(&fill_brush1);
	CPen* p_old_pen = p_dc->SelectObject(&border_pen2);
	// 첫번째 사각형
	p_dc->Rectangle(0, 0, m_width, m_height);

	p_dc->SelectObject(&fill_brush2);
	p_dc->SelectObject(&border_pen1);
	// 두번째 사각형
	p_dc->Rectangle(1, 1, pos, m_height-1);

	p_dc->SelectObject(p_old_pen);
	p_dc->SelectObject(p_old_brush);
	fill_brush1.DeleteObject();
	fill_brush2.DeleteObject();
	border_pen1.DeleteObject();
	border_pen2.DeleteObject();

	CString str;
	str.Format(L"%d", m_pos);
	p_dc->SetBkMode(TRANSPARENT);					// 텍스트배경 제거
	p_dc->SetTextColor(RGB(255, 255, 255));
	p_dc->DrawText(str, CRect(0, 0, m_width, m_height), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_mem_image.Draw(&dc, 0, 0);
}

// 대화상자가 아닌 일반 Wnd가 만들어질때 한번만 호출되는 함수
int SJ_ProgressCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CRect r;
	GetClientRect(r);

	m_width = r.Width();
	m_height = r.Height();

	// 메모리DC 클래스 사용 (깜빡임제거)
	m_mem_image._CreateDC(this, m_width, m_height);

	return 0;
}
