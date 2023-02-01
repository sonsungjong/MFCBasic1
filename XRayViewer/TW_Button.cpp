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

// �߿�! : ��ư �޽��� ó���� (MFC �����Լ�)
void TW_Button::DrawItem(LPDRAWITEMSTRUCT lpds)
{
	// TODO:  Add your code to draw the specified item
	CRect rect(lpds->rcItem);				// RECT -> CRect ����ȯ
	CDC* p_dc = CDC::FromHandle(lpds->hDC);

	p_dc->SelectStockObject(DC_BRUSH);				// ����� ���� �귯�� ���
	p_dc->SelectStockObject(DC_PEN);						// ����� ���� �� ���

	if (lpds->itemState & ODS_FOCUS) {
		// �ش� ��ư�� ��Ŀ�� ���¸�
		p_dc->SetDCBrushColor(m_focus_btn_color);				// ��ư ��Ŀ�� �귯�û� ����
		p_dc->SetDCPenColor(m_focus_border_color);					// ��ư ��Ŀ�� ��� ����
	}
	else {
		// �ش� ��ư�� ��Ŀ���� �ȵ� �⺻ ���¸�
		p_dc->SetDCBrushColor(m_btn_color);					// ��ư ��� �귯�û� ����
		p_dc->SetDCPenColor(m_border_color);					// ��ư �׵θ� ��� ����
	}
	// �簢���� �׸���
	p_dc->Rectangle(rect);

	p_dc->SelectStockObject(NULL_BRUSH);				// �귯�û� ����
	p_dc->SetDCPenColor(m_in_border_color);				// �� �� ����
	p_dc->Rectangle(rect.left + 1, rect.top + 1, rect.right - 1, rect.bottom - 1);				// ���ʿ� �簢���� �׸���

	// ��ư�� ������ ��¦ �Ʒ������� �̵����Ѽ� ������ ������ �����Ѵ�
	if (lpds->itemState & ODS_SELECTED) { rect += CPoint(1, 1); }

	CString str;
	GetWindowText(str);				// ��ư�� �ؽ�Ʈ�� ��´�
	p_dc->SetBkMode(TRANSPARENT);				// �ؽ�Ʈ ��� ����ó��
	p_dc->SetTextColor(m_text_color);				// �ؽ�Ʈ�� ����
	p_dc->DrawText(str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);				// ���� ���
}
