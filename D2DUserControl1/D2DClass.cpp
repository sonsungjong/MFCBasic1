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
	mp_bitmap = NULL;

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
void D2DClass::D2DRenderBegin()
{
	if (m_render_target == NULL) {
		return;
	}
	::ValidateRect(m_wnd, NULL);				// WM_PAINT 플래그 무효화
	// D2D 그리기 시작
	m_render_target->BeginDraw();
}

// 배경색 지정
void D2DClass::D2DBackground(D2D1_COLOR_F a_color)
{
	m_render_target->Clear(a_color);
}

// WM_PAINT 에서 사용
void D2DClass::D2DRenderEnd()
{
	// D2D 그리기 종료하고 화면에 적용
	m_render_target->EndDraw();
}
void D2DClass::D2DTextOut(TCHAR* a_text, float a_x, float a_y, float a_font_size, D2D1_COLOR_F a_text_color, TCHAR* font_style)
{
	m_font_size = a_font_size;
	int text_count = _tcslen(a_text);
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_write_text),
		reinterpret_cast<IUnknown**>(&m_write_text));
	m_render_target->CreateSolidColorBrush(a_text_color, &m_brush);
	m_write_text->CreateTextFormat(font_style, NULL, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, m_font_size, _T("ko-kr"), &m_text_format);
	m_text_format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);			// 수직정렬 가운데
	//m_text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);							// 수평정렬 가운데

	D2D1_RECT_F r{ a_x, a_y, a_x + (m_font_size * text_count), a_y + m_font_size };
	if (m_brush != NULL && m_text_format != NULL) {
		m_render_target->DrawText(a_text, text_count + 1, m_text_format, r, m_brush);
	}
}
void D2DClass::D2DRectangle(float a_x, float a_y, float a_end_x, float a_end_y, D2D1_COLOR_F a_color)
{
	m_render_target->CreateSolidColorBrush(a_color, &m_brush);
	if (m_brush != NULL) {
		m_render_target->DrawRectangle({ a_x, a_y, a_end_x, a_end_y }, m_brush);
		m_render_target->FillRectangle({ a_x, a_y, a_end_x, a_end_y }, m_brush);
	}
}

void D2DClass::D2DLine(float a_x, float a_y, float a_end_x, float a_end_y, D2D1_COLOR_F a_color)
{
}

void D2DClass::D2DPng(float a_x, float a_y, float a_end_x, float a_end_y, const TCHAR* ap_path)
{
	if (mp_bitmap != NULL) {
		mp_bitmap->Release();
		mp_bitmap = NULL;
	}

	IWICImagingFactory* p_wic_factory;
	(void)CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&p_wic_factory));
	IWICBitmapDecoder* p_decoder;			// 압축 이미지 해제
	IWICBitmapFrameDecode* p_frame;
	IWICFormatConverter* p_converter;
	int result = 0;

	if (S_OK == p_wic_factory->CreateDecoderFromFilename(ap_path, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &p_decoder)) {
		// 파일을 구성하는 이미지 중에서 첫번째 이미지를 선택한다.
		if (S_OK == p_decoder->GetFrame(0, &p_frame)) {
			// IWICBitmap형식의 비트맵을 ID2D1Bitmap. 형식으로 변환하기 위한 객체 생성
			if (S_OK == p_wic_factory->CreateFormatConverter(&p_converter)) {
				// 선택된 그림을 어떤 형식의 비트맵으로 변환할 것인지 설정한다.
				if (S_OK == p_converter->Initialize(p_frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom)) {
					// IWICBitmap 형식의 비트맵으로 ID2D1Bitmap 객체를 생성한다.
					if (S_OK == m_render_target->CreateBitmapFromWicBitmap(p_converter, NULL, &mp_bitmap)) { result = 1; }  // 성공적으로 생성한 경우
				}
				p_converter->Release();  // 이미지 변환 객체 제거
			}
			p_frame->Release();   // 그림파일에 있는 이미지를 선택하기 위해 사용한 객체 제거
		}
		p_decoder->Release();     // 압축을 해제하기 위해 생성한 객체 제거
	}
	p_wic_factory->Release();     // WIC를 사용하기 위해 만들었던 Factory 객체 제거

	m_render_target->DrawBitmap(mp_bitmap, { a_x, a_y, a_end_x, a_end_y });
}
