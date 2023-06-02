#ifndef D2D_CLASS_H_
#define D2D_CLASS_H_

using namespace D2D1;

#define D2D_RGBA(r, g, b, a) ColorF((float)r/255.0f, (float)g/255.0f, (float)b/255.0f, (float)a/255.0f)

class D2DClass
{
protected:
	HRESULT m_hr;
	D2D1_SIZE_U m_size;
	ID2D1Factory* m_factory;												// D2D의 각종 객체 생성을 위한 팩토리
	ID2D1RenderTarget* m_render_target;					// 렌더링 타겟
	ID2D1SolidColorBrush* m_brush;
	IDWriteFactory* m_write_text;										// 문자열 팩토리
	IDWriteTextFormat* m_text_format;								// 문자열 형식
	HWND m_wnd;
	D2D1_RECT_F m_rect;
	D2D1_COLOR_F m_color = {0.0f, 0.0f, 0.0f, 1.0f};				// RGBA 색상 (검정)
	float m_font_size;

public:
	D2DClass();
	virtual ~D2DClass();


	void SetWndTarget(HWND a_wnd, RECT* ap_rect);
	void D2DRenderBegin();
	void D2DRenderEnd();
	void D2DBackground(D2D1_COLOR_F a_color);
	void D2DTextOut(TCHAR* text, float x, float y, float a_font_size=16.0f, D2D1_COLOR_F a_text_color = { 0.0f, 0.0f, 0.0f, 1.0f }, TCHAR* font_style=_T("맑은 고딕"));
	void D2DRectangle(float x, float y, float end_x, float end_y, D2D1_COLOR_F a_color = {0.0f, 0.0f, 0.0f, 1.0f});
	void D2DLine(float x, float y, float end_x, float end_y, D2D1_COLOR_F a_color = { 0.0f, 0.0f, 0.0f, 1.0f });
	void D2DDotLine(float x, float y, float end_x, float end_y, D2D1_COLOR_F a_color = { 0.0f, 0.0f, 0.0f, 1.0f });
	void D2DBarGraph();
	void D2DLineGraph();

	template<class Interface>
	void D2DRelease(Interface** ap_interface_object)
	{
		if (*ap_interface_object != NULL) {
			(*ap_interface_object)->Release();
			(*ap_interface_object) = NULL;
		}
	}

};


#endif