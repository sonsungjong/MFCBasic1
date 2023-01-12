// TipsButton.cpp : implementation file
//

#include "pch.h"
#include "MFCL233ButtonCtrlMake.h"
#include "TipsButton.h"


// TipsButton

IMPLEMENT_DYNAMIC(TipsButton, CWnd)

TipsButton::TipsButton()
{
	mh_mem_dc = NULL;
	mh_mem_bmp = NULL;
	mh_font = NULL;

	// ��Ŀ�� ����
	m_focus_btn_color = RGB(69, 73, 77);
	m_focus_border_color = RGB(109, 113, 117);
	// ����Ŀ�� ����
	m_btn_color = RGB(39, 43, 47);
	m_border_color = RGB(59, 63, 67);
	// �����׵θ� ����
	m_in_border_color = RGB(157, 171, 196);
	// ��Ʈ ����
	m_text_color = RGB(232, 248, 248);

	m_is_clicked = 0;
	m_push_flag = 0;
}

TipsButton::~TipsButton()
{
}


BEGIN_MESSAGE_MAP(TipsButton, CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()



// TipsButton message handlers

int TipsButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	GetClientRect(m_rect);					// ���� ������ ��ǥ

	HDC hdc = ::GetDC(m_hWnd);
	mh_mem_dc = ::CreateCompatibleDC(hdc);					// �޸�DC ����
	mh_mem_bmp = ::CreateCompatibleBitmap(hdc, m_rect.Width(), m_rect.Height());				// �޸� bitmap ����
	::ReleaseDC(m_hWnd, hdc);				// DC�� bitmap�� ����� �ݳ�

	// �۲�
	mh_font = ::CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("����"));

	::SelectObject(mh_mem_dc, mh_mem_bmp);						// dc�� ��Ʈ�� ����
	::SelectObject(mh_mem_dc, mh_font);								// dc�� �۲� ����

	// ��� �귯�� ������ �����Ͽ� �⺻ ��ü�� ����
	::SelectObject(mh_mem_dc, ::GetStockObject(DC_BRUSH));
	::SelectObject(mh_mem_dc, ::GetStockObject(DC_PEN));
	::SetBkMode(mh_mem_dc, TRANSPARENT);				// �ؽ�Ʈ ��� �����ϰ�

	// �Ϲ� ������ ��ư�� �޸� DC�� �׸���
	DrawButtonImage(0);
	return 0;
}


void TipsButton::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
	// �׸��⿡ ����� ��ü�� ����
	if (mh_mem_dc != NULL) { ::DeleteDC(mh_mem_dc); }
	if (mh_mem_bmp != NULL) { ::DeleteObject(mh_mem_bmp); }
	if (mh_font != NULL) { ::DeleteObject(mh_font); }
}

// �޸�DC�� �׷����ִ� ��Ʈ�ʸ� ���ŵǵ���
void TipsButton::OnPaint()
{
	CPaintDC dc(this);

	// mh_mem_bmp �� ȭ�鿡 ��� (ī��)
	::BitBlt(dc.m_hDC, 0, 0, m_rect.Width(), m_rect.Height(), mh_mem_dc, 0, 0, SRCCOPY);
}


void TipsButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked == 0) {					// ���콺�� ��Ŭ���� �����϶���
		m_is_clicked = 1;						// Ŭ�� ���·� ����
		m_push_flag = 1;						// ������ ���·� ����
		// ��ư�� ������� �������� mh_mem_bmp�� �׸���
		DrawButtonImage(m_push_flag);
		// ȭ�鿡 ���
		Invalidate(FALSE);
		// ���콺�� ��ư ������ ����� ���콺 �޽����� ��� ���� �� �ְ� SetCapture()
		SetCapture();
	}
	CWnd::OnLButtonDown(nFlags, point);
}


void TipsButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked) {						// ���콺�� Ŭ���� ������ ��
		m_is_clicked = 0;				// Ŭ�� ���� ����
		ReleaseCapture();						// SetCapture() ����
		if (m_push_flag == 1) {
			m_push_flag = 0;					// ���� ���� ����
			// ��ư�� ��Ʈ�ʿ� �׸���
			DrawButtonImage(m_push_flag);
			// ȭ�鿡 ����Ѵ�
			Invalidate(FALSE);
			// �θ� �����쿡 Ŭ����ٴ� ���� �޽����� �˸�
			GetParent()->PostMessage(LM_BTN_CLICKED, (WPARAM)GetDlgCtrlID(), (LPARAM)this);					// �θ� �����쿡 LM_BTN_CLICKED �޽��� �߻�
		}
	}
	CWnd::OnLButtonUp(nFlags, point);
}


void TipsButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked)						// ���콺�� Ŭ���� ���¿���
	{
		// ���� ���� ��� ��
		char old_flag = m_push_flag;
		// ���콺�� ��ư ���ʿ� �ִ��� �ٱ��ʿ� �ִ��� ���Ͽ� ���� ���� ����
		if (m_rect.PtInRect(point)) { m_push_flag = 1; }
		else { m_push_flag = 0; }

		// Ŭ�� ���¿��� ����� ���¿� ����� ���°� �ٸ��� ��ư�� ���� �׸��� ȭ�����
		if (old_flag != m_push_flag)				// ��ư ���ʿ��� Ŭ���� ä�� �����̴� ��Ȳ�� ���ؼ� ������ �ȵǰԲ� �Ѵ�
		{
			DrawButtonImage(m_push_flag);
			Invalidate(FALSE);
		}
	}
	CWnd::OnMouseMove(nFlags, point);
}

// �� Ű�� ���� ��Ŀ���� �������� ��
void TipsButton::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	// TODO: Add your message handler code here
	DrawButtonImage(m_push_flag);
	Invalidate(FALSE);
}


void TipsButton::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	// TODO: Add your message handler code here
	DrawButtonImage(m_push_flag);
	Invalidate(FALSE);
}

int TipsButton::CreateButton(CWnd* ap_parent, const TCHAR* ap_title, int a_ctrl_id, int a_guide_rect)
{
	CRect r;
	int result = 0;

	CWnd* p_wnd = ap_parent->GetDlgItem(a_guide_rect);
	if (p_wnd != NULL) {
		p_wnd->GetWindowRect(r);
		ap_parent->ScreenToClient(r);

		result = CreateButton(ap_parent, ap_title, a_ctrl_id, r);
	}
	return result;
}

int TipsButton::CreateButton(CWnd* ap_parent, const TCHAR* ap_title, int a_ctrl_id, CRect a_rect)
{
	// ��ư�� ����� ���ڿ� ����
	m_title_str = ap_title;
	// �־��� ������ ������ ��ư ����� ������ �����츦 ���� (�����ϸ� 1, �����ϸ� 0)
	BOOL result = Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP, a_rect, ap_parent, a_ctrl_id);

    return result;
}

void TipsButton::DrawButtonImage(char a_push_flag)
{
	if (::GetFocus() == m_hWnd) {				// ��Ŀ�� ������ ��
		::SetDCBrushColor(mh_mem_dc, m_focus_btn_color);
		::SetDCPenColor(mh_mem_dc, m_focus_border_color);
	}
	else {
		::SetDCBrushColor(mh_mem_dc, m_btn_color);
		::SetDCPenColor(mh_mem_dc, m_border_color);
	}

	// �簢���� �׸���
	::Rectangle(mh_mem_dc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);

	CRect r;
	if (!a_push_flag)
	{
		// ��ư�� �ȴ���������
		// Brush ��� ����
		HGDIOBJ h_old_brush = ::SelectObject(mh_mem_dc, ::GetStockObject(NULL_BRUSH));
		::SetDCPenColor(mh_mem_dc, m_in_border_color);				// Pen ����
		// ��ư ���� ����
		::Rectangle(mh_mem_dc, m_rect.left + 1, m_rect.top + 1, m_rect.right - 1, m_rect.bottom - 1);
		::SelectObject(mh_mem_dc, h_old_brush);			// �⺻ Brush ����
		r = m_rect;
	}
	else {
		// ��ư�� �������ٸ� ��ư�� �ؽ�Ʈ�� ��¦ �Ʒ��� �̵����� ������ ������ �����Ѵ�
		r = m_rect + CPoint(1, 1);
	}
	// �ؽ�Ʈ ������ �����ؼ� ��ư�� ���ڿ� ���
	::SetTextColor(mh_mem_dc, m_text_color);
	::DrawText(mh_mem_dc, m_title_str, m_title_str.GetLength(), r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

void TipsButton::ChangeColor(COLORREF a_focus_btn_color, COLORREF a_focus_border_color, COLORREF a_btn_color, COLORREF a_border_color, COLORREF a_in_border_color, COLORREF a_text_color)
{
	m_focus_btn_color = a_focus_btn_color;
	m_focus_border_color = a_focus_border_color;
	m_btn_color = a_btn_color;
	m_border_color = a_border_color;
	m_in_border_color = a_in_border_color;
	m_text_color = a_text_color;
}
