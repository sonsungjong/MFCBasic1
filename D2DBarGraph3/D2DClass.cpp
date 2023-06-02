#include "pch.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>



#include "D2DClass.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")

D2DClass::D2DClass()
{
	m_rect = { NULL, };
	m_factory = NULL;
	m_render_target = NULL;
	m_brush = NULL;
	m_write_text = NULL;
	m_text_format = NULL;
	m_size = { NULL, };
	m_wnd = NULL;

	m_hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (SUCCEEDED(m_hr)) {
		m_hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_factory);
	}
	
	if (!SUCCEEDED(m_hr)) {
		AfxMessageBox(_T("Direct2D 생성 실패"));
	}
}

D2DClass::~D2DClass()
{
	D2DRelease(&m_write_text);
	D2DRelease(&m_brush);
	D2DRelease(&m_text_format);
	D2DRelease(&m_render_target);
	D2DRelease(&m_factory);

	CoUninitialize();
}



void D2DClass::SetWndTarget(HWND a_wnd, RECT* ap_rect)
{
	m_wnd = a_wnd;
	m_rect.left = (float)ap_rect->left;
	m_rect.top = (float)ap_rect->top;
	m_rect.right = (float)ap_rect->right;
	m_rect.bottom = (float)ap_rect->bottom;
	m_size = SizeU(ap_rect->right - ap_rect->left, ap_rect->bottom - ap_rect->top);

	ID2D1HwndRenderTarget* p_hwnd_target;
	m_hr = m_factory->CreateHwndRenderTarget(RenderTargetProperties(), HwndRenderTargetProperties(a_wnd, m_size), &p_hwnd_target);

	// 인터페이스로 주소 보관
	m_render_target = p_hwnd_target;
}

// WM_PAINT에서 사용
void D2DClass::D2DRenderBegin()
{
	if (m_render_target == NULL) {
		return;
	}
	::ValidateRect(m_wnd, NULL);				// WM_PAINT 플래그 무효화
	// D2D 그리기 시작
	m_render_target->BeginDraw();
}

// 배경색
void D2DClass::D2DBackground(D2D1_COLOR_F a_color)
{
	m_render_target->Clear(a_color);
}

// WM_PAINT에서 사용
void D2DClass::D2DRenderEnd()
{
	// D2D 그리기 종료하고 화면에 적용
	m_render_target->EndDraw();
}


void D2DClass::D2DBarGraph()
{
	m_render_target->CreateSolidColorBrush(ColorF(ColorF::Black), &m_brush);
	// 막대 그래프 그리는 코드 예시
	float barWidth = 50.0f;
	float barSpacing = 20.0f;
	float barHeight[] = { 100.0f, 200.0f, 300.0f, 150.0f, 250.0f };
	D2D1_COLOR_F colors[] = {
		{0.0f, 0.125f, 0.3f, 1.0f},
		{0.5f, 0.125f, 0.3f, 1.0f},
		{0.1f, 0.125f, 0.3f, 0.5f},
		{0.0f, 0.5f, 0.3f, 1.0f},
		{0.0f, 0.125f, 0.125f, 1.0f}
	};
	size_t barCount = sizeof(barHeight) / sizeof(barHeight[0]);

	for (size_t i = 0; i < barCount; ++i)
	{
		D2D1_RECT_F barRect = D2D1::RectF(barSpacing + i * (barWidth + barSpacing), m_render_target->GetSize().height - barHeight[i],
			barSpacing + (i + 1) * barWidth + i * barSpacing, m_render_target->GetSize().height);
		m_brush->SetColor(colors[i]);
		if (m_brush != NULL) {
			m_render_target->FillRectangle(barRect, m_brush);
		}
	}
}

void D2DClass::D2DTextOut(TCHAR* text, float x, float y, float a_font_size, D2D1_COLOR_F a_text_color, TCHAR* font_style)
{
	m_font_size = a_font_size;
	int text_count = _tcslen(text);
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_write_text),
		reinterpret_cast<IUnknown**>(&m_write_text));
	m_render_target->CreateSolidColorBrush(a_text_color, &m_brush);
	m_write_text->CreateTextFormat(font_style, NULL, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, m_font_size, _T("ko-kr"), &m_text_format);
	m_text_format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);			// 수직정렬 가운데
	//m_text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);							// 수평정렬 가운데

	D2D1_RECT_F r{ x, y, x+(m_font_size*text_count), y + m_font_size };
	if (m_brush != NULL && m_text_format != NULL) {
		m_render_target->DrawText(text, text_count+1, m_text_format, r, m_brush);
	}
}

void D2DClass::D2DRectangle(float x, float y, float end_x, float end_y, D2D1_COLOR_F a_color)
{
	m_render_target->CreateSolidColorBrush(a_color, &m_brush);
	if (m_brush != NULL) {
		m_render_target->DrawRectangle({ x, y, end_x, end_y }, m_brush);
	}
}

