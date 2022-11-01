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
		mp_graphic = new Graphics(mp_bitmap);

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

}

void DCP::FillSolidRect(int a_sx, int a_sy, int a_ex, int a_ey)
{

}

void DCP::DrawRect(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{

}

void DCP::DrawRect(int a_sx, int a_sy, int a_ex, int a_ey)
{

}

void DCP::Ellipse(int a_sx, int a_sy, int a_ex, int a_ey)
{

}

void DCP::FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{

}

void DCP::FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey)
{

}

void DCP::DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{

}

void DCP::DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey)
{

}

void DCP::DrawLine(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{

}

void DCP::DrawLine(int a_sx, int a_sy, int a_ex, int a_ey)
{

}

void DCP::MoveTo(int a_x, int a_y)
{

}

void DCP::LineTo(int a_x, int a_y)
{

}

void DCP::SetDCBrushColor(ARGB a_color)
{

}

void DCP::SetDCPenColor(ARGB a_color)
{

}

void DCP::SetDCPenColor(DashStyle a_style, REAL a_width, ARGB a_color)
{

}

void DCP::Draw(Image* ap_image, int a_x, int a_y)
{

}

void DCP::Draw(HDC ah_dc, int a_x, int a_y)
{

}