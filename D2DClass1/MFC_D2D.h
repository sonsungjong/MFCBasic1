#ifndef MFC_D2D_H_
#define MFC_D2D_H_

#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "DWRITE.lib")

using namespace D2D1;

// COM으로 생성된 객체를 해제하는 함수
template<class Interface> void d2dRelease(Interface** ap_interface_object)
{
	if (*ap_interface_object != NULL) {
		(*ap_interface_object)->Release();
		(*ap_interface_object) = NULL;
	}
}

// 지정한 영역에 마우스 좌표가 포함되어 있는지 체크하는 함수
__inline int d2dPtInRect(D2D1_RECT_F* ap_rect, CPoint* ap_pos)
{
	return ap_rect->left <= ap_pos->x && ap_rect->top <= ap_pos->y &&
		ap_rect->right >= ap_pos->x && ap_rect->bottom >= ap_pos->y;
}


class D2D_Core
{
	// D2D Factory
	ID2D1Factory* mp_factory;

	// 문자열 출력 관련 Factory
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
	// D2D 그림그리기
	ID2D1RenderTarget* mp_target;
	// 선과 텍스트 출력 브러시
	ID2D1SolidColorBrush* mp_user_brush;
	// 문자열 글꼴
	IDWriteTextFormat* mp_text_format;
	// 뷰의 크기
	D2D1_SIZE_U m_view_size;
	// View와 연결된 윈도우 핸들 값
	HWND mh_wnd;

	// 기본 브러시
	D2D1_COLOR_F m_def_color = { 1.0f, 1.0f, 1.0f, 1.0f };				// RGBA
	D2D1_COLOR_F m_bk_color = { 0.0f, 0.5f, 0.0f, 1.0f };				// RGBA

	// 글꼴이름과 크기
	TCHAR m_font_name[32];
	float m_font_size;

public:
	D2D_View();
	virtual ~D2D_View();

	// View 생성 함수
	int createView(HWND ah_wnd, RECT* ap_rect);

	// WM_PAINT 메시지 처리기에서 호출해야하는 함수
	virtual void d2dPaint();
	// View 그리기 작업을 전담할 함수
	virtual void d2dDraw() {

		D2D1_RECT_F r{ 30.0f, 30.0f, 450.0f, 150.0f };
		// 글꼴이 출력될 위치를 사각형으로 표시
		mp_target->DrawRectangle(r, mp_user_brush);
		// 글꼴 출력
		mp_target->DrawText(_T("미가공 파이팅@@"), 9, mp_text_format, r, mp_user_brush);
	}
	// View를 강제로 갱신하는 함수
	void updatePaint();

};


#endif