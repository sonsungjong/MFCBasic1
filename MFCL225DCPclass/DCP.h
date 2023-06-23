#ifndef DCP_H_
#define DCP_H_

// Ŭ���� �ʱ� �� ���� : �輺��(tipsware@naver.com)
// Ŭ���� ���� : https://cafe.naver.com/mythread
// ó�� ���� ��¥ : 2020�� 3�� 24�� (ȭ����)
// ó�� ������ ������Ʈ ��¥ : 2020�� 3�� 25�� (������)

// �� Ŭ������ ����̳� ������ �����ߴٸ� �Ʒ��� �̷��� �����ֽø� �˴ϴ�.
// Ŭ���� ���� ������ : �ռ���
// ������ ���� ��¥ : 2022�� 12�� 9�� (�ݿ���)

#include <gdiplus.h>
using namespace Gdiplus;

// MFC�� lib �ʿ����
//#pragma comment(lib, "gdiplus.lib")

#define RGB24(r,g,b) (0xFF000000 | ((r) << 16) | ((g) << 8) | (b))					// 0xFFRRGGBB
#define RGB32(a,r,g,b) (((a)<<24)|((r)<<16)|((g)<<8)|(b))							// 0xAARRGGBB

// DC Plus Ŭ����, ������۸� ���
class DCP
{
private:
	Gdiplus::Brush* mp_brush;
	Gdiplus::Brush* mp_font_brush;
	Gdiplus::Pen* mp_pen;
	Gdiplus::Font* mp_font;
	Gdiplus::Bitmap* mp_bitmap;
	Gdiplus::Graphics* mp_graphic;

	INT m_width;				// ��� ��
	INT m_height;			// ��� ����
	INT m_last_position_x;
	INT m_last_position_y;
	Gdiplus::Color m_temp_color;					// ���� ������ ���� �ӽ� ��ü

	static ULONG_PTR m_token;				// GDI+ ���̺귯�� ��� ����
	static INT m_object_count;					// DCP ��ü ���� ���

public:
	explicit DCP();
	explicit DCP(INT a_width, INT a_height);
	virtual ~DCP();

	void Init();
	void CreateDCP(INT a_width, INT a_height);

	// �簢��
	void Rectangle(INT a_sx, INT a_sy, INT a_ex, INT a_ey);
	void Rectangle(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_pen_color, Gdiplus::ARGB a_fill_color);
	void FillSolidRect(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color);
	void FillSolidRect(INT a_sx, INT a_sy, INT a_ex, INT a_ey);
	void DrawRect(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color);
	void DrawRect(INT a_sx, INT a_sy, INT a_ex, INT a_ey);

	// Ÿ��
	void Ellipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey);
	void FillSolidEllipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color);
	void FillSolidEllipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey);
	void DrawEllipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color);
	void DrawEllipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey);

	// ���׸���
	void DrawLine(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color);
	void DrawLine(INT a_sx, INT a_sy, INT a_ex, INT a_ey);
	void MoveTo(INT a_x, INT a_y);
	void LineTo(INT a_x, INT a_y);

	// �귯�� ���� ����
	void SetDCBrushColor(Gdiplus::ARGB a_color);
	// �� ���� ����
	void SetDCPenColor(Gdiplus::ARGB a_color);
	// �� ���� (��Ÿ��, ����, ����)
	void SetDCPenColor(Gdiplus::DashStyle a_style, Gdiplus::REAL a_width, Gdiplus::ARGB a_color);
	// �۲� ���� ����
	void SetTextColor(Gdiplus::ARGB a_color);
	// ��Ʈ ��ü �缳�� , ���� ��Ʈ ��ü�� �ּҸ� ��ȯ��
	Gdiplus::Font* SelectObject(Gdiplus::Font* ap_font);
	void SelectObject(const TCHAR* ap_style, INT a_size);

	// �ؽ�Ʈ ��� (����ο�)
	void GpTextOut(INT a_x, INT a_y, Gdiplus::ARGB a_color, const TCHAR* ap_str, INT a_str_len);
	// �ؽ�Ʈ ��� (��������)
	void GpTextOut(INT a_x, INT a_y, const TCHAR* ap_str, INT a_str_len);

	// �̹��� ��ü ���
	void Draw(Gdiplus::Image* ap_image, INT a_x, INT a_y);

	// ��θ� �޾� �ش� �̹��� ��� (���� ũ��)
	void Draw(TCHAR* a_file_path, INT a_x, INT a_y);
	// ��θ� �޾� ���ϴ� ũ��� �̹��� ���
	void Draw(TCHAR* a_file_path, INT a_x, INT a_y, INT a_width, INT a_height);

	// DC�� ���� �̹��� ���
	void Draw(HDC ah_dc, INT a_x = 0, INT a_y = 0);

	// Get
	Gdiplus::Image* GetImage();
	Gdiplus::Graphics* GetGraphics();

	// Get�Լ����� ���ϰ� ����� �� �ֵ��� ������ �����ε�
	operator Gdiplus::Image* ();
	operator Gdiplus::Graphics* ();

	// ��ü ���� ���� ä���
	void Clear(Gdiplus::ARGB a_color);
	void Clear();

	// �ٰ��� �׸��� (ä���)
	void FillPolygon(Gdiplus::Point* ap_position_list, INT a_count);

	// �ٰ��� �׸��� (�׵θ�)
	void DrawPolygon(Gdiplus::Point* ap_position_list, INT a_count);

	// Arc �׸��� (�׵θ�)
	void DrawArc(Gdiplus::REAL a_x, Gdiplus::REAL a_y, Gdiplus::REAL a_cx, Gdiplus::REAL a_cy, Gdiplus::REAL a_start_angle, Gdiplus::REAL a_sweep_angle);
};

#endif