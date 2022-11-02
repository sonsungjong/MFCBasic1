#include "pch.h"
#include "DCP.h"

// static멤버변수 : 클래스 멤버만 공유하는 전역변수
int DCP::m_object_count = 0;
ULONG_PTR DCP::m_token = 0;

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
	}
	if (mp_bitmap != NULL) {
		delete mp_bitmap;
	}

	m_object_count--;
	if (m_object_count == 0) {
		GdiplusShutdown(m_token);
	}
}

void DCP::Init()
{
	if (m_object_count == 0) {
		GdiplusStartupInput gpsi;
		GdiplusStartup(&m_token, &gpsi, NULL);
	}
	m_object_count++;
	m_last_position_x = m_last_position_y = m_width = m_height = 0;
	mp_bitmap = NULL;
	mp_graphic = NULL;

	mp_brush = new SolidBrush(RGB24(255, 255, 255));
	mp_font_brush = new SolidBrush(RGB24(0, 0, 0));
	mp_pen = new Pen(RGB24(0, 0, 0));
	mp_font = new Gdiplus::Font(_T("굴림체"), 9);
}

void DCP::CreateDCP(int a_width, int a_height)
{
	if (mp_graphic == NULL || m_width != a_width || m_height != a_height) {
		m_width = a_width;
		m_height = a_height;
		if (mp_graphic != NULL) {
			delete mp_graphic;
		}
		if (mp_bitmap != NULL) {
			delete mp_bitmap;
		}

		mp_bitmap = new Bitmap(m_width, m_height);
		mp_graphic = new Gdiplus::Graphics(mp_bitmap);

		mp_graphic->SetSmoothingMode(SmoothingModeAntiAlias);
	}
}

void DCP::Rectangle(int a_sx, int a_sy, int a_ex, int a_ey)
{
	mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
	mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

void DCP::FillSolidRect(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	((SolidBrush*)mp_brush)->SetColor(m_temp_color);
	mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
}

void DCP::FillSolidRect(int a_sx, int a_sy, int a_ex, int a_ey)
{
	mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
}

void DCP::DrawRect(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	mp_pen->SetColor(m_temp_color);
	mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

void DCP::DrawRect(int a_sx, int a_sy, int a_ex, int a_ey)
{
	mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

void DCP::Ellipse(int a_sx, int a_sy, int a_ex, int a_ey)
{
	// 내부 채우기
	mp_graphic->FillEllipse(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
	// 테두리 그리기
	mp_graphic->DrawEllipse(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

void DCP::FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	((SolidBrush*)mp_brush)->SetColor(m_temp_color);
	mp_graphic->FillEllipse(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
}

void DCP::FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey)
{
	mp_graphic->FillEllipse(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
}

void DCP::DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	mp_pen->SetColor(m_temp_color);
	mp_graphic->DrawEllipse(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

void DCP::DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey)
{
	mp_graphic->DrawEllipse(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

void DCP::DrawLine(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	mp_pen->SetColor(m_temp_color);
	mp_graphic->DrawLine(mp_pen, a_sx, a_sy, a_ex, a_ey);
	m_last_position_x = a_ex;
	m_last_position_y = a_ey;
}

void DCP::DrawLine(int a_sx, int a_sy, int a_ex, int a_ey)
{
	mp_graphic->DrawLine(mp_pen, a_sx, a_sy, a_ex, a_ey);
	m_last_position_x = a_ex;
	m_last_position_y = a_ey;
}

void DCP::MoveTo(int a_x, int a_y)
{
	m_last_position_x = a_x;
	m_last_position_y = a_y;
}

void DCP::LineTo(int a_x, int a_y)
{
	mp_graphic->DrawLine(mp_pen, m_last_position_x, m_last_position_y, a_x, a_y);
	m_last_position_x = a_x;
	m_last_position_y = a_y;
}

void DCP::SetDCBrushColor(ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	((SolidBrush*)mp_brush)->SetColor(m_temp_color);
}

void DCP::SetDCPenColor(ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	mp_pen->SetColor(m_temp_color);
}

void DCP::SetDCPenColor(DashStyle a_style, REAL a_width, ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	mp_pen->SetColor(m_temp_color);
	mp_pen->SetWidth(a_width);
	mp_pen->SetDashStyle(a_style);
}

void DCP::SetTextColor(ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	((SolidBrush*)mp_font_brush)->SetColor(m_temp_color);
}

Gdiplus::Font* DCP::SelectObject(Gdiplus::Font* ap_font)
{
	Gdiplus::Font* p_old_font = mp_font;
	mp_font = ap_font;
	return p_old_font;
}

void DCP::TextOut(int a_x, int a_y, ARGB a_color, const TCHAR* ap_str, int a_str_len)
{
	m_temp_color.SetValue(a_color);
	((SolidBrush*)mp_font_brush)->SetColor(m_temp_color);
	mp_graphic->DrawString(ap_str, a_str_len, mp_font, PointF(REAL(a_x), REAL(a_y)), mp_font_brush);
}

void DCP::TextOut(int a_x, int a_y, const TCHAR* ap_str, int a_str_len)
{
	mp_graphic->DrawString(ap_str, a_str_len, mp_font, PointF(REAL(a_x), REAL(a_y)), mp_font_brush);
}

void DCP::Draw(Image* ap_image, int a_x, int a_y)
{
	// 이미지 출력
	mp_graphic->DrawImage(ap_image, a_x, a_y);
}

void DCP::Draw(HDC ah_dc, int a_x, int a_y)
{
	// 전달된 DC에 현재 이미지를 출력
	Gdiplus::Graphics* p_graphic = new Gdiplus::Graphics(ah_dc);
	p_graphic->DrawImage(mp_bitmap, 0, 0);
	delete p_graphic;
}