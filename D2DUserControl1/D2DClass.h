#ifndef D2D_CLASS_H_
#define D2D_CLASS_H_

using namespace D2D1;

#define D2D_RGBA(r, g, b, a) ColorF((float)r/255.0f, (float)g/255.0f, (float)b/255.0f, (float)a/255.0f)

class D2DClass
{
protected:
	HRESULT m_hr;
	D2D1_SIZE_U m_size;
	ID2D1Factory* m_factory;									// D2D�� ���� ��ü�� ����
	ID2D1RenderTarget* m_render_target;				// ������ Ÿ��
	ID2D1SolidColorBrush* m_brush;
	IDWriteFactory* m_write_text;
	IDWriteTextFormat* m_text_format;
	HWND m_wnd;
	D2D1_RECT_F m_rect;					// ��ü ����
	ID2D1Bitmap* mp_bitmap;

protected:
	float m_font_size;
	float m_font_style;
	D2D1_COLOR_F m_text_color;
	D2D1_COLOR_F m_black_color = { 0.0f, 0.0f, 0.0f, 1.0f };
	D2D1_COLOR_F m_white_color = { 1.0f, 1.0f, 1.0f, 1.0f };

public:
	D2DClass();
	virtual ~D2DClass();
	void SetWndTarget(HWND a_wnd, RECT* ap_rect);
	void D2DRenderBegin();				// WM_PAINT���� ���
	void D2DBackground(D2D1_COLOR_F a_color);			// ����
	void D2DRenderEnd();				// ȭ�鿡 ����

	template<class Interface>
	void D2DRelease(Interface** ap_interface_object)
	{
		if (*ap_interface_object != NULL) {
			(*ap_interface_object)->Release();
			(*ap_interface_object) = NULL;
		}
	}

public:
	void D2DTextOut(TCHAR* a_text, float a_x, float a_y, float a_font_size=16.0f, D2D1_COLOR_F a_text_color = { 0.0f, 0.0f, 0.0f, 1.0f }, TCHAR* font_style= _T("���� ���"));
	void D2DRectangle(float a_x, float a_y, float a_end_x, float a_end_y, D2D1_COLOR_F a_color);
	void D2DLine(float a_x, float a_y, float a_end_x, float a_end_y, D2D1_COLOR_F a_color);
	void D2DPng(float a_x, float a_y, float a_end_x, float a_end_y, const TCHAR* ap_path);
};

#endif	D2D_CLASS_H_