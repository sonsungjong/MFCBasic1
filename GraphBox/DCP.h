#ifndef DCP_H_
#define DCP_H_

#include <gdiplus.h>

#define RGB24(r,g,b) (0xFF000000 | ((r) << 16) | ((g) << 8) | (b))					// 0xFFRRGGBB
#define RGB32(a,r,g,b) (((a)<<24)|((r)<<16)|((g)<<8)|(b))							// 0xAARRGGBB

// DC Plus Ŭ����, ������۸� ���
class DCP
{
protected:
	Gdiplus::Brush* mp_brush;
	Gdiplus::Brush* mp_font_brush;
	Gdiplus::Font* mp_font;

	int m_last_position_x;
	int m_last_position_y;
	Gdiplus::Color m_temp_color;				// ���� ������ ���� �ӽ� ��ü

	int m_width;				// ��� ��
	int m_height;				// ��� ����
	static ULONG_PTR m_token;				// GDI+ ���̺귯�� ��� ����
	static int m_object_count;					// DCP ��ü ���� ���

public:
	Gdiplus::Pen* mp_pen = NULL;
	Gdiplus::Bitmap* mp_bitmap;
	Gdiplus::Graphics* mp_graphic;
	explicit DCP();
	explicit DCP(int a_width, int a_height);
	virtual ~DCP();

	void Init();
	void CreateDCP(int a_width, int a_height);

	// �簢�� (���� ä���)
	void Rectangle(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_pen_color = NULL, Gdiplus::ARGB a_fill_color = NULL);
	void DrawRect(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_pen_color = NULL);
	void FillSolidRect(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_fill_color = NULL);

	// Ÿ�� (���� ä���)
	void Ellipse(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_pen_color = NULL, Gdiplus::ARGB a_fill_color = NULL);
	void DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_pen_color = NULL);
	void FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_fill_color = NULL);

	// �� �׸���
	void DrawLine(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_pen_color = NULL);
	void MoveTo(int a_sx, int a_sy);
	void LineTo(int a_ex, int a_ey, Gdiplus::ARGB a_pen_color = NULL);

	// �� ���� (�� ��Ÿ�ϰ� �β�)
	void SetPenStyle(Gdiplus::DashStyle a_style, Gdiplus::REAL a_thickness, Gdiplus::ARGB a_pen_color = NULL);

	// �ؽ�Ʈ ���
	void DCPText(int a_x, int a_y, const TCHAR* ap_str, Gdiplus::ARGB a_text_color = NULL);

	// �ؽ�Ʈ �۲ð� ũ�� ����, �ۻ���
	void DCPTextSetting(const TCHAR* ap_font_style, int a_font_size, Gdiplus::ARGB a_text_color = NULL);

	// �̹��� ��� (��θ� �޾� �ش� �̹��� ��� - ũ��� ���� �Է� ���ϸ� ����ũ�� ����)
	void DCPImage(const TCHAR* a_file_path, int a_x, int a_y, int a_width = 0, int a_height = 0);

	// DC�� �ݿ�!! (�߿�)
	void Draw(HDC ah_dc, int a_x = 0, int a_y = 0);

	// ��ü ���� ���� ä���
	void Clear(Gdiplus::ARGB a_color = NULL);

	// �ٰ��� �׸���(�׵θ�)
	void FillPolygon(Gdiplus::Point* ap_position_list, int a_count, Gdiplus::ARGB a_fill_color = NULL);

	// �ٰ��� �׸���(ä���)
	void DrawPolygon(Gdiplus::Point* ap_position_list, int a_count, Gdiplus::ARGB a_pen_color = NULL);

	// �ٰ��� �׸��� (��+ä���)
	void Polygon(Gdiplus::Point* ap_position_list, int a_count, Gdiplus::ARGB a_pen_color, Gdiplus::ARGB a_fill_color);

	// Arc�׸��� (�׵θ�)
	void DrawArc(Gdiplus::REAL a_x, Gdiplus::REAL a_y, Gdiplus::REAL a_cx, Gdiplus::REAL a_cy, Gdiplus::REAL a_start_angle, Gdiplus::REAL a_sweep_angle, Gdiplus::ARGB a_pen_color = NULL);

	// �׷��� �׸���

};

#endif