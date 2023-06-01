#include "pch.h"
#include "MFC_D2D.h"

D2D_Core* gp_d2d;

D2D_Core::D2D_Core()
{
	gp_d2d = this;
	mp_factory = NULL;
	mp_write_factory = NULL;

	// COM을 사용하기 위해 초기화 함수 호출
	if (S_OK == CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)) {
		// D2D 사용을 위한 팩토리 생성
		if (S_OK == D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mp_factory))
		{
			// 문자열 리소스 팩토리 생성
			DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(mp_write_factory), reinterpret_cast<IUnknown**>(&mp_write_factory));
		}
	}
}

D2D_Core::~D2D_Core()
{
	if (mp_factory != NULL) {
		// D2D 해제
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
	memcpy(m_font_name, _T("맑은 고딕"), 12);
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

	// 렌더 타겟 주소
	ID2D1HwndRenderTarget* p_hwnd_target;
	// 영역에 그림을 그리기 위한 Render Target
	gp_d2d->getFactory()->CreateHwndRenderTarget(RenderTargetProperties(), HwndRenderTargetProperties(ah_wnd, m_view_size), &p_hwnd_target);

	// 문자열 형식 생성
	if (S_OK == gp_d2d->getWriteFactory()->CreateTextFormat(m_font_name, NULL, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, m_font_size, _T("ko-kr"), &mp_text_format)) {
		//mp_text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);						// 수평 가운데 정렬
		// 수직 가운데 정렬
		mp_text_format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}


	// 멤버로 보관
	mp_target = p_hwnd_target;


	// 선과 텍스트 브러시 생성
	mp_target->CreateSolidColorBrush(m_def_color, &mp_user_brush);
	return 1;
}

void D2D_View::d2dPaint()
{
	// WM_PAINT 무효화
	::ValidateRect(mh_wnd, NULL);
	updatePaint();
}

void D2D_View::updatePaint()
{
	mp_target->BeginDraw();
	// 화면 전체를 배경색으로
	//mp_target->Clear(m_bk_color);

	d2dDraw();

	mp_target->EndDraw();
}
