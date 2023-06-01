#ifndef MFC_D2D_H_
#define MFC_D2D_H_

#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "DWRITE.lib")

using namespace D2D1;

// COM���� ������ ��ü�� �����ϴ� �Լ�
template<class Interface> void d2dRelease(Interface** ap_interface_object)
{
	if (*ap_interface_object != NULL) {
		(*ap_interface_object)->Release();
		(*ap_interface_object) = NULL;
	}
}

// ������ ������ ���콺 ��ǥ�� ���ԵǾ� �ִ��� üũ�ϴ� �Լ�
__inline int d2dPtInRect(D2D1_RECT_F* ap_rect, CPoint* ap_pos)
{
	return ap_rect->left <= ap_pos->x && ap_rect->top <= ap_pos->y &&
		ap_rect->right >= ap_pos->x && ap_rect->bottom >= ap_pos->y;
}


class D2D_Core
{
	// D2D Factory
	ID2D1Factory* mp_factory;

	// ���ڿ� ��� ���� Factory
	IDWriteFactory* mp_write_factory;

public:
	D2D_Core();
	virtual ~D2D_Core();

	ID2D1Factory* getFactory();
	IDWriteFactory* getWriteFactory();
};

extern D2D_Core* gp_d2d;

class D2D_View
{
protected:
	// D2D �׸��׸���
	ID2D1RenderTarget* mp_target;
	// ���� �ؽ�Ʈ ��� �귯��
	ID2D1SolidColorBrush* mp_user_brush;
	// ���ڿ� �۲�
	IDWriteTextFormat* mp_text_format;
	// ���� ũ��
	D2D1_SIZE_U m_view_size;
	// View�� ����� ������ �ڵ� ��
	HWND mh_wnd;

	// �⺻ �귯��
	D2D1_COLOR_F m_def_color = { 1.0f, 1.0f, 1.0f, 1.0f };				// RGBA
	D2D1_COLOR_F m_bk_color = { 0.0f, 0.5f, 0.0f, 1.0f };				// RGBA

	// �۲��̸��� ũ��
	TCHAR m_font_name[32];
	float m_font_size;

public:
	D2D_View();
	virtual ~D2D_View();

	// View ���� �Լ�
	int createView(HWND ah_wnd, RECT* ap_rect);

	// WM_PAINT �޽��� ó���⿡�� ȣ���ؾ��ϴ� �Լ�
	virtual void d2dPaint();
	// View �׸��� �۾��� ������ �Լ�
	virtual void d2dDraw() {

		D2D1_RECT_F r{ 30.0f, 30.0f, 450.0f, 150.0f };
		// �۲��� ��µ� ��ġ�� �簢������ ǥ��
		mp_target->DrawRectangle(r, mp_user_brush);
		// �۲� ���
		mp_target->DrawText(_T("�̰��� ������@@"), 9, mp_text_format, r, mp_user_brush);
	}
	// View�� ������ �����ϴ� �Լ�
	void updatePaint();

};


#endif