#ifndef DCP_H_
#define DCP_H_

#include <gdiplus.h>
using namespace Gdiplus;

#define RGB24(r,g,b) (0xFF000000 | (r << 16) | (g << 8) | b)
#define RGB32(a,r,g,b) ( (a<<24)| (r << 16) | (g << 8) | b)

class DCP
{
protected:
	Brush* mp_brush;
	Brush* mp_font_brush;
	Pen* mp_pen;
	Gdiplus::Font* mp_font;
	Bitmap* mp_bitmap;
	Graphics* mp_graphic;

	int m_width, m_height;
	int m_last_position_x, m_last_position_y;
	Color m_temp_color;

	static ULONG_PTR m_token;
	static int m_object_count;
public:
	DCP();
	DCP(int a_width, int a_height);
	virtual ~DCP();

	void Init();
	void CreateDCP(int a_width, int a_height);

	// 사각형
	void Rectangle(int a_sx, int a_sy, int a_ex, int a_ey);
	void FillSolidRect(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color);
	void FillSolidRect(int a_sx, int a_sy, int a_ex, int a_ey);
	void DrawRect(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color);
	void DrawRect(int a_sx, int a_sy, int a_ex, int a_ey);

	// 타원
	void Ellipse(int a_sx, int a_sy, int a_ex, int a_ey);
	void FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color);
	void FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey);
	void DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color);
	void DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey);

	// 선 그리기
	void DrawLine(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color);
	void DrawLine(int a_sx, int a_sy, int a_ex, int a_ey);
	void MoveTo(int a_x, int a_y);
	void LineTo(int a_x, int a_y);

	void SetDCBrushColor(ARGB a_color);
	void SetDCPenColor(ARGB a_color);
	void SetDCPenColor(DashStyle a_style, REAL a_width, ARGB a_color);
	void SetTextColor(ARGB a_color);
	Gdiplus::Font* SelectObject(Gdiplus::Font* ap_font);

	void Draw(Image* ap_image, int a_x, int a_y);
	void Draw(HDC ah_dc, int a_x = 0, int a_y = 0);

	void TextOut(int a_x, int a_y, ARGB a_color, const TCHAR* ap_str, int a_str_len);
	void TextOut(int a_x, int a_y, const TCHAR* ap_str, int a_str_len);

	Image* GetImage() { return mp_bitmap; }
	Graphics* GetGraphics() { return mp_graphic; }

	operator Image* () { return mp_bitmap; }
	operator Graphics* () { return mp_graphic; }
};

#endif