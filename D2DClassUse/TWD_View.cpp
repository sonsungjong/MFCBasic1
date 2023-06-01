#include "pch.h"
#include "TW_Direct2D.h"

TWD_View::TWD_View()
{
	mh_wnd = NULL;
	mp_target = NULL;
	m_view_size.width = m_view_size.height = 0;
	// �⺻���� �����Ǵ� �۲��� �̸��� ũ�⸦ �����Ѵ�.
	memcpy(m_def_font_name, _T("���� ���"), 12);
	m_def_font_size = 16.0f;
}

TWD_View::~TWD_View()
{
	TWD_IRelease(&mp_target);
	TWD_IRelease(&mp_user_brush);
	TWD_IRelease(&mp_text_format);
}

int TWD_View::Create(HWND ah_wnd, RECT* ap_rect)
{
	mh_wnd = ah_wnd;
	m_view_size.width = ap_rect->right - ap_rect->left;
	m_view_size.height = ap_rect->bottom - ap_rect->top;

	// ���ڿ� ��� ������ ������ �ڿ� ����
	if (S_OK == gp_tw_d2d->GetWriteFactory()->CreateTextFormat(m_def_font_name, NULL,
		DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		m_def_font_size, _T("ko-kr"), &mp_text_format)) {
		// �������� (���)
		mp_text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		// �������� (���)
		mp_text_format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	// ������ ����Ÿ�� �������� �ּҸ� ������ ������
	ID2D1HwndRenderTarget* p_hwnd_target;
	// ������ ������ Ŭ���̾�Ʈ ������ �׸��� �׸��� RenderTarget ����
	gp_tw_d2d->GetFactory()->CreateHwndRenderTarget(RenderTargetProperties(),
		HwndRenderTargetProperties(ah_wnd, m_view_size), &p_hwnd_target);

	// �θ� �������̽��� �ּҸ� ����
	mp_target = p_hwnd_target;

	// ���� �ؽ�Ʈ ��¿� ����� �귯�� ����
	mp_target->CreateSolidColorBrush(m_def_color, &mp_user_brush);

	return 1;
}

// WM_PAINT���� ȣ���ؾ��ϴ� �Լ�
void TWD_View::OnPaint()
{
	// WM_PAINT �÷��׸� ��ȿȭ
	::ValidateRect(mh_wnd, NULL);
	UpdateView();
}

// �並 ������ �����ϴ� �Լ�
void TWD_View::UpdateView()
{
	mp_target->BeginDraw();
	// ȭ���� ����������
	mp_target->Clear(m_bk_color);

	OnDraw();
	mp_target->EndDraw();
}
