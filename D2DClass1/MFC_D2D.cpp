#include "pch.h"
#include "MFC_D2D.h"

D2D_Core* gp_d2d;

D2D_Core::D2D_Core()
{
	gp_d2d = this;
	mp_factory = NULL;
	mp_write_factory = NULL;

	// COM�� ����ϱ� ���� �ʱ�ȭ �Լ� ȣ��
	if (S_OK == CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)) {
		// D2D ����� ���� ���丮 ����
		if (S_OK == D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mp_factory))
		{
			// ���ڿ� ���ҽ� ���丮 ����
			DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(mp_write_factory), reinterpret_cast<IUnknown**>(&mp_write_factory));
		}
	}
}

D2D_Core::~D2D_Core()
{
	if (mp_factory != NULL) {
		// D2D ����
		d2dRelease(&mp_write_factory);
		d2dRelease(&mp_factory);
	}
	CoUninitialize();
}

ID2D1Factory* D2D_Core::getFactory()
{
	return mp_factory;
}

IDWriteFactory* D2D_Core::getWriteFactory()
{
	return mp_write_factory;
}

D2D_View::D2D_View()
{
	mh_wnd = NULL;
	mp_target = NULL;
	m_view_size.width = m_view_size.height = 0;
	memcpy(m_font_name, _T("���� ���"), 12);
	m_font_size = 16.0f;
}

D2D_View::~D2D_View()
{
	d2dRelease(&mp_target);
	d2dRelease(&mp_user_brush);
	d2dRelease(&mp_text_format);
}

int D2D_View::createView(HWND ah_wnd, RECT* ap_rect)
{
	mh_wnd = ah_wnd;
	m_view_size.width = ap_rect->right - ap_rect->left;
	m_view_size.height = ap_rect->bottom - ap_rect->top;

	// ���� Ÿ�� �ּ�
	ID2D1HwndRenderTarget* p_hwnd_target;
	// ������ �׸��� �׸��� ���� Render Target
	gp_d2d->getFactory()->CreateHwndRenderTarget(RenderTargetProperties(), HwndRenderTargetProperties(ah_wnd, m_view_size), &p_hwnd_target);

	// ���ڿ� ���� ����
	if (S_OK == gp_d2d->getWriteFactory()->CreateTextFormat(m_font_name, NULL, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, m_font_size, _T("ko-kr"), &mp_text_format)) {
		//mp_text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);						// ���� ��� ����
		// ���� ��� ����
		mp_text_format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}


	// ����� ����
	mp_target = p_hwnd_target;


	// ���� �ؽ�Ʈ �귯�� ����
	mp_target->CreateSolidColorBrush(m_def_color, &mp_user_brush);
	return 1;
}

void D2D_View::d2dPaint()
{
	// WM_PAINT ��ȿȭ
	::ValidateRect(mh_wnd, NULL);
	updatePaint();
}

void D2D_View::updatePaint()
{
	mp_target->BeginDraw();
	// ȭ�� ��ü�� ��������
	//mp_target->Clear(m_bk_color);

	d2dDraw();

	mp_target->EndDraw();
}
