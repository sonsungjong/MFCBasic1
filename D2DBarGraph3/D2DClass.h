#pragma once
class D2DClass
{
protected:
	HRESULT m_hr;
	D2D1_SIZE_U m_size;
	ID2D1Factory* m_factory;
	ID2D1HwndRenderTarget* m_render_target;
	ID2D1SolidColorBrush* m_brush;
	IDWriteFactory* m_write_text;
	IDWriteTextFormat* m_text_format;
	HWND m_wnd;
	RECT m_rect;
	float m_font_size;

public:
	D2DClass();
	virtual ~D2DClass();


	void SetRect(HWND a_wnd, RECT a_rect);
	void D2DRenderBegin();
	void D2DRenderEnd();
	void D2DBackground(D2D1_COLOR_F a_color);
	void D2DTextOut(TCHAR* text, float x, float y, float a_font_size=16.0f, D2D1_COLOR_F a_text_color = { 0.0f, 0.0f, 0.0f, 1.0f }, TCHAR* font_style=_T("¸¼Àº °íµñ"));
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


