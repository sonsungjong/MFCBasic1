#include "pch.h"
#include "TW_Direct2D.h"

TWD_View::TWD_View()
{
	mh_wnd = NULL;
	mp_target = NULL;
	m_view_size.width = m_view_size.height = 0;
	// 기본으로 생성되는 글꼴의 이름과 크기를 지정한다.
	memcpy(m_def_font_name, _T("맑은 고딕"), 12);
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

	// 문자열 출력 형식을 지정할 자원 생성
	if (S_OK == gp_tw_d2d->GetWriteFactory()->CreateTextFormat(m_def_font_name, NULL,
		DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		m_def_font_size, _T("ko-kr"), &mp_text_format)) {
		// 수평정렬 (가운데)
		mp_text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		// 수직정렬 (가운데)
		mp_text_format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	// 윈도우 렌더타겟 생성에서 주소를 가져올 포인터
	ID2D1HwndRenderTarget* p_hwnd_target;
	// 지정한 윈도우 클라이언트 영역에 그림을 그리는 RenderTarget 생성
	gp_tw_d2d->GetFactory()->CreateHwndRenderTarget(RenderTargetProperties(),
		HwndRenderTargetProperties(ah_wnd, m_view_size), &p_hwnd_target);

	// 부모 인터페이스로 주소를 보관
	mp_target = p_hwnd_target;

	// 선과 텍스트 출력에 사용할 브러시 생성
	mp_target->CreateSolidColorBrush(m_def_color, &mp_user_brush);

	return 1;
}

// WM_PAINT에서 호출해야하는 함수
void TWD_View::OnPaint()
{
	// WM_PAINT 플래그를 무효화
	::ValidateRect(mh_wnd, NULL);
	UpdateView();
}

// 뷰를 강제로 갱신하는 함수
void TWD_View::UpdateView()
{
	mp_target->BeginDraw();
	// 화면을 검은색으로
	mp_target->Clear(m_bk_color);

	OnDraw();
	mp_target->EndDraw();
}
