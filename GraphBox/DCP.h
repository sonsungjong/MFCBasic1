#ifndef DCP_H_
#define DCP_H_

#include <gdiplus.h>

#define RGB24(r,g,b) (0xFF000000 | ((r) << 16) | ((g) << 8) | (b))					// 0xFFRRGGBB
#define RGB32(a,r,g,b) (((a)<<24)|((r)<<16)|((g)<<8)|(b))							// 0xAARRGGBB

// DC Plus 클래스, 더블버퍼링 사용
class DCP
{
protected:
	Gdiplus::Brush* mp_brush;
	Gdiplus::Brush* mp_font_brush;
	Gdiplus::Font* mp_font;

	int m_last_position_x;
	int m_last_position_y;
	Gdiplus::Color m_temp_color;				// 색상 변경을 위한 임시 객체

	int m_width;				// 출력 폭
	int m_height;				// 출력 높이
	static ULONG_PTR m_token;				// GDI+ 라이브러리 사용 정보
	static int m_object_count;					// DCP 객체 갯수 계산

public:
	Gdiplus::Pen* mp_pen = NULL;
	Gdiplus::Bitmap* mp_bitmap;
	Gdiplus::Graphics* mp_graphic;
	explicit DCP();
	explicit DCP(int a_width, int a_height);
	virtual ~DCP();

	void Init();
	void CreateDCP(int a_width, int a_height);

	// 사각형 (선과 채우기)
	void Rectangle(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_pen_color = NULL, Gdiplus::ARGB a_fill_color = NULL);
	void DrawRect(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_pen_color = NULL);
	void FillSolidRect(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_fill_color = NULL);

	// 타원 (선과 채우기)
	void Ellipse(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_pen_color = NULL, Gdiplus::ARGB a_fill_color = NULL);
	void DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_pen_color = NULL);
	void FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_fill_color = NULL);

	// 선 그리기
	void DrawLine(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_pen_color = NULL);
	void MoveTo(int a_sx, int a_sy);
	void LineTo(int a_ex, int a_ey, Gdiplus::ARGB a_pen_color = NULL);

	// 펜 변경 (선 스타일과 두께)
	void SetPenStyle(Gdiplus::DashStyle a_style, Gdiplus::REAL a_thickness, Gdiplus::ARGB a_pen_color = NULL);

	// 텍스트 출력
	void DCPText(int a_x, int a_y, const TCHAR* ap_str, Gdiplus::ARGB a_text_color = NULL);

	// 텍스트 글꼴과 크기 변경, 글색상
	void DCPTextSetting(const TCHAR* ap_font_style, int a_font_size, Gdiplus::ARGB a_text_color = NULL);

	// 이미지 출력 (경로를 받아 해당 이미지 출력 - 크기와 높이 입력 안하면 원본크기 적용)
	void DCPImage(const TCHAR* a_file_path, int a_x, int a_y, int a_width = 0, int a_height = 0);

	// DC에 반영!! (중요)
	void Draw(HDC ah_dc, int a_x = 0, int a_y = 0);

	// 전체 영역 색상 채우기
	void Clear(Gdiplus::ARGB a_color = NULL);

	// 다각형 그리기(테두리)
	void FillPolygon(Gdiplus::Point* ap_position_list, int a_count, Gdiplus::ARGB a_fill_color = NULL);

	// 다각형 그리기(채우기)
	void DrawPolygon(Gdiplus::Point* ap_position_list, int a_count, Gdiplus::ARGB a_pen_color = NULL);

	// 다각형 그리기 (선+채우기)
	void Polygon(Gdiplus::Point* ap_position_list, int a_count, Gdiplus::ARGB a_pen_color, Gdiplus::ARGB a_fill_color);

	// Arc그리기 (테두리)
	void DrawArc(Gdiplus::REAL a_x, Gdiplus::REAL a_y, Gdiplus::REAL a_cx, Gdiplus::REAL a_cy, Gdiplus::REAL a_start_angle, Gdiplus::REAL a_sweep_angle, Gdiplus::ARGB a_pen_color = NULL);

	// 그래프 그리기

};

#endif