#include "pch.h"

using namespace Gdiplus;
using namespace DllExports;

#include "DCP.h"
#pragma comment(lib, "gdiplus.lib")				// MFC������ ���ص���

// static ��������� �������� �ʱ�ȭ
ULONG_PTR DCP::m_token = 0;				// GDI+ ���̺귯�� ��� ����
int DCP::m_object_count = 0;					// DCP ��ü ���� ���

// DC�� ���� ��Ʈ�� �̹����� ��� (��)
void DCP::Draw(HDC ah_dc, int a_x, int a_y)
{
	// ���޵� DC�� ���� �̹����� ��� (���� ���۸�)
	Gdiplus::Graphics* p_graphic = new Gdiplus::Graphics(ah_dc);
	p_graphic->DrawImage(mp_bitmap, a_x, a_y);
	delete p_graphic;
}

DCP::DCP()
{
	Init();
}

DCP::DCP(int a_width, int a_height)
{
	Init();
	CreateDCP(a_width, a_height);
}

DCP::~DCP()
{
	delete mp_brush;
	delete mp_pen;
	delete mp_font;
	delete mp_font_brush;

	if (mp_graphic != NULL) {
		delete mp_graphic;
		mp_graphic = NULL;
	}
	if (mp_bitmap != NULL) {
		delete mp_bitmap;
		mp_bitmap = NULL;
	}

	m_object_count--;					// DCP ��ü�� ����
	if (m_object_count == 0) {
		Gdiplus::GdiplusShutdown(m_token);				// ������ ��ü�� ������ �� GDI+ ���̺귯�� ����
	}
}

void DCP::Init()
{
	// ù DCP ��ü�� GDI+ �ʱ�ȭ
	if (m_object_count == 0) {
		Gdiplus::GdiplusStartupInput gpsi;
		Gdiplus::GdiplusStartup(&m_token, &gpsi, NULL);
	}
	m_object_count++;				// DCP ��ü�� ����

	// �ʱ�ȭ
	m_last_position_x = 0;
	m_last_position_y = 0;
	m_width = 0;
	m_height = 0;

	mp_bitmap = NULL;				// ��� �̹����� ������ �̹��� ��ü
	mp_graphic = NULL;				// �׸� �׸��� ��ü

	mp_brush = new Gdiplus::SolidBrush(RGB24(255, 255, 255));				// �⺻ �귯�� (�Ͼ�)
	mp_font_brush = new Gdiplus::SolidBrush(RGB24(0, 0, 0));					// �⺻ �귯�� (�۲ÿ�, ����)
	mp_pen = new Gdiplus::Pen(RGB24(0, 0, 0));										// �⺻ �� ���� (����)
	mp_font = new Gdiplus::Font(L"���� ���", 9);									// �⺻ �۲�
}

void DCP::CreateDCP(int a_width, int a_height)
{
	// ��� ��ġ�� �����Ǿ� ���� �ʰų� ���� ���̰� �޶�߸� �����Ѵ�
	if (mp_graphic == NULL || m_width != a_width || m_height != a_height) {
		m_width = a_width;
		m_height = a_height;

		// ���� ��ü ����
		if (mp_graphic != NULL) {
			delete mp_graphic;
		}
		if (mp_bitmap != NULL) {
			delete mp_bitmap;
		}

		// ���ο� ũ�⿡ �°� ��Ʈ�ʰ� ��� �׷��� ��ü ���� (���� ���۸�)
		mp_bitmap = new Gdiplus::Bitmap(m_width, m_height);
		mp_graphic = new Gdiplus::Graphics(mp_bitmap);

		// 'AntiAlias' ���
		mp_graphic->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	}
}

void DCP::Rectangle(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_pen_color, Gdiplus::ARGB a_fill_color)
{
	// �簢�� ���λ�
	if (a_fill_color != NULL) {
		m_temp_color.SetValue(a_fill_color);
		((Gdiplus::SolidBrush*)mp_brush)->SetColor(m_temp_color);
	}
	mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);

	// �簢�� �׵θ� �׸���
	if (a_pen_color != NULL) {
		m_temp_color.SetValue(a_pen_color);
		mp_pen->SetColor(m_temp_color);
	}
	mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

void DCP::DrawRect(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_pen_color)
{
	// �簢�� �׵θ� �׸���
	if (a_pen_color != NULL) {
		m_temp_color.SetValue(a_pen_color);
		mp_pen->SetColor(m_temp_color);
	}
	mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

void DCP::FillSolidRect(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_fill_color)
{
	// ���� ���λ�
	if (a_fill_color != NULL) {
		m_temp_color.SetValue(a_fill_color);
		((Gdiplus::SolidBrush*)mp_brush)->SetColor(m_temp_color);
	}
	mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
}

void DCP::Ellipse(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_pen_color, Gdiplus::ARGB a_fill_color)
{
	// ���� ���λ�
	if (a_fill_color != NULL) {
		m_temp_color.SetValue(a_fill_color);
		((Gdiplus::SolidBrush*)mp_brush)->SetColor(m_temp_color);
	}
	mp_graphic->FillEllipse(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);

	// �׵θ�
	if (a_pen_color != NULL) {
		m_temp_color.SetValue(a_pen_color);
		mp_pen->SetColor(m_temp_color);
	}
	mp_graphic->DrawEllipse(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

void DCP::DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_pen_color)
{
	// �׵θ�
	if (a_pen_color != NULL) {
		m_temp_color.SetValue(a_pen_color);
		mp_pen->SetColor(m_temp_color);
	}
	mp_graphic->DrawEllipse(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

void DCP::FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_fill_color)
{
	// ���� ���λ�
	if (a_fill_color != NULL) {
		m_temp_color.SetValue(a_fill_color);
		((Gdiplus::SolidBrush*)mp_brush)->SetColor(m_temp_color);
	}
	mp_graphic->FillEllipse(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);

}

void DCP::DrawLine(int a_sx, int a_sy, int a_ex, int a_ey, Gdiplus::ARGB a_pen_color)
{
	if (a_pen_color != NULL) {
		m_temp_color.SetValue(a_pen_color);
		mp_pen->SetColor(m_temp_color);
	}
	mp_graphic->DrawLine(mp_pen, a_sx, a_sy, a_ex, a_ey);
	m_last_position_x = a_ex;
	m_last_position_y = a_ey;
}

void DCP::MoveTo(int a_sx, int a_sy)
{
	m_last_position_x = a_sx;
	m_last_position_y = a_sy;
}

void DCP::LineTo(int a_ex, int a_ey, Gdiplus::ARGB a_pen_color)
{
	if (a_pen_color != NULL) {
		m_temp_color.SetValue(a_pen_color);
		mp_pen->SetColor(m_temp_color);
	}
	mp_graphic->DrawLine(mp_pen, m_last_position_x, m_last_position_y, a_ex, a_ey);
	m_last_position_x = a_ex;
	m_last_position_y = a_ey;
}

// �� ���� (�� ��Ÿ��, ����)
void DCP::SetPenStyle(Gdiplus::DashStyle a_style, Gdiplus::REAL a_thickness, Gdiplus::ARGB a_pen_color)
{
	mp_pen->SetDashStyle(a_style);
	mp_pen->SetWidth(a_thickness);
	if (a_pen_color != NULL) {
		m_temp_color.SetValue(a_pen_color);
		mp_pen->SetColor(m_temp_color);
	}
}

// Gdiplus TextOut
void DCP::DCPText(int a_x, int a_y, const TCHAR* ap_str, Gdiplus::ARGB a_text_color)
{
	if (a_text_color != NULL) {
		m_temp_color.SetValue(a_text_color);
		((Gdiplus::SolidBrush*)mp_font_brush)->SetColor(m_temp_color);
	}
	int str_len = _tcslen(ap_str);
	mp_graphic->DrawString(ap_str, str_len, mp_font, Gdiplus::PointF(Gdiplus::REAL(a_x), Gdiplus::REAL(a_y)), mp_font_brush);
}

// �ؽ�Ʈ �۲ð� ũ�� ����, �ۻ���
void DCP::DCPTextSetting(const TCHAR* ap_font_style, int a_font_size, Gdiplus::ARGB a_text_color)
{
	delete mp_font;
	mp_font = new Gdiplus::Font(ap_font_style, (Gdiplus::REAL)a_font_size);

	if (a_text_color != NULL) {
		m_temp_color.SetValue(a_text_color);
		((Gdiplus::SolidBrush*)mp_font_brush)->SetColor(m_temp_color);
	}
}

// ��θ� �ָ� �̹����� �׸���
void DCP::DCPImage(const TCHAR* a_file_path, int a_x, int a_y, int a_width, int a_height)
{
	Gdiplus::Image* image = Gdiplus::Image::FromFile(a_file_path);

	if (a_width != 0 && a_height != 0) {
		mp_graphic->DrawImage(image, Gdiplus::Rect(a_x, a_y, a_width, a_height));
	}
	else {
		mp_graphic->DrawImage(image, a_x, a_y);
	}
}



// a_color�� ��ü ������ ä���
void DCP::Clear(Gdiplus::ARGB a_color)
{
	if (a_color == NULL) {
		mp_graphic->Clear(m_temp_color);
	}
	else {
		mp_graphic->Clear(a_color);
	}
}

void DCP::Polygon(Gdiplus::Point* ap_position_list, int a_count, Gdiplus::ARGB a_pen_color, Gdiplus::ARGB a_fill_color)
{
	// ä���
	if (a_fill_color != NULL) {
		m_temp_color.SetValue(a_fill_color);
		((Gdiplus::SolidBrush*)mp_brush)->SetColor(m_temp_color);
	}
	mp_graphic->FillPolygon(mp_brush, ap_position_list, a_count);

	// �׵θ�
	if (a_pen_color != NULL) {
		m_temp_color.SetValue(a_pen_color);
		mp_pen->SetColor(m_temp_color);
	}
	mp_graphic->DrawPolygon(mp_pen, ap_position_list, a_count);
}

// ���� ä���� �ٰ��� �׸���
void DCP::FillPolygon(Gdiplus::Point* ap_position_list, int a_count, Gdiplus::ARGB a_fill_color)
{
	if (a_fill_color != NULL) {
		m_temp_color.SetValue(a_fill_color);
		((Gdiplus::SolidBrush*)mp_brush)->SetColor(m_temp_color);
	}
	mp_graphic->FillPolygon(mp_brush, ap_position_list, a_count);
}

// �ٰ��� �׵θ� �׸���
void DCP::DrawPolygon(Gdiplus::Point* ap_position_list, int a_count, Gdiplus::ARGB a_pen_color)
{
	if (a_pen_color != NULL) {
		m_temp_color.SetValue(a_pen_color);
		mp_pen->SetColor(m_temp_color);
	}
	mp_graphic->DrawPolygon(mp_pen, ap_position_list, a_count);
}

// ��ä��(Arc) �׵θ� 
void DCP::DrawArc(Gdiplus::REAL a_x, Gdiplus::REAL a_y, Gdiplus::REAL a_cx, Gdiplus::REAL a_cy, Gdiplus::REAL a_start_angle, Gdiplus::REAL a_sweep_angle, Gdiplus::ARGB a_pen_color)
{
	if (a_pen_color != NULL) {
		m_temp_color.SetValue(a_pen_color);
		mp_pen->SetColor(m_temp_color);
	}
	mp_graphic->DrawArc(mp_pen, a_x, a_y, a_cx, a_cy, a_start_angle, a_sweep_angle);
}

