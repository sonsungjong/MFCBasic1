#include "pch.h"
#include "DCP.h"

// static�������(Ŭ���� ����� ������ �� �ִ� ��������) �ʱ�ȭ
INT DCP::m_object_count = 0;
ULONG_PTR DCP::m_token = 0;

DCP::DCP()
{
	Init();
}

DCP::DCP(INT a_width, INT a_height)
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

	m_object_count--;						// DCP ��ü�� ����
	if (m_object_count == 0) {							// ������ ��ü�� ������ �� GDI+ �� ����
		Gdiplus::GdiplusShutdown(m_token);
	}
}

void DCP::Init()
{
	if (m_object_count == 0) {							// ù DCP ��ü��� GDI+ �� �ʱ�ȭ ��Ų��.
		Gdiplus::GdiplusStartupInput gpsi;
		Gdiplus::GdiplusStartup(&m_token, &gpsi, NULL);
	}
	m_object_count++;						// DCP ��ü�� ����
	// ��ǥ �� ũ�� ���� �ʱ�ȭ
	m_last_position_x = 0;
	m_last_position_y = 0;
	m_width = 0;
	m_height = 0;

	mp_bitmap = NULL;						// ��� �̹����� ������ �̹��� ��ü
	mp_graphic = NULL;						// �׸� �׸��� ��ü

	mp_brush = new Gdiplus::SolidBrush(RGB24(255, 255, 255));				// �⺻ �귯��
	mp_font_brush = new Gdiplus::SolidBrush(RGB24(0, 0, 0));					// �⺻ �귯�� (�۲ÿ�)
	mp_pen = new Gdiplus::Pen(RGB24(0, 0, 0));				// �� ����
	mp_font = new Gdiplus::Font(_T("����ü"), 9);				// �⺻ �۲�
}

void DCP::CreateDCP(INT a_width, INT a_height)
{
	// ��� ��ġ�� �����Ǿ� ���� �ʰų� ���� ���̰� �޶�߸� �����Ѵ�.
	if (mp_graphic == NULL || m_width != a_width || m_height != a_height) {
		// ���ο� ���� ���� ����
		m_width = a_width;
		m_height = a_height;

		// ���� ��ü ����
		if (mp_graphic != NULL) {
			delete mp_graphic;
		}
		if (mp_bitmap != NULL) {
			delete mp_bitmap;
		}

		// ���ο� ũ�⿡ �°� ��Ʈ�ʰ� ��� �׷��� ��ü ����
		mp_bitmap = new Gdiplus::Bitmap(m_width, m_height);
		mp_graphic = new Gdiplus::Graphics(mp_bitmap);

		// 'AntiAlias' ���
		mp_graphic->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	}
}

// a_color�� ��ü ������ ä���.
void DCP::Clear(Gdiplus::ARGB a_color)
{
	mp_graphic->Clear(a_color);
}

// ������ Brush �������� ��ü ������ ä���.
void DCP::Clear()
{
	mp_graphic->Clear(m_temp_color);
}

// �簢���� �׸��� (���� �귯�ÿ� ���� ���)
void DCP::Rectangle(INT a_sx, INT a_sy, INT a_ex, INT a_ey)
{
	// ���� ä���
	mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
	// �׵θ� �׸���
	mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

// �簢���� �׸��� (��� ����, �귯�û� ����)
void DCP::Rectangle(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_pen_color, Gdiplus::ARGB a_fill_color)
{
	// ���� ä���
	m_temp_color.SetValue(a_fill_color);
	((Gdiplus::SolidBrush*)mp_brush)->SetColor(m_temp_color);
	mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);

	// �׵θ� �׸���
	m_temp_color.SetValue(a_pen_color);
	mp_pen->SetColor(m_temp_color);
	mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

// ������ �������� �簢���� �׸��� (ä���)
void DCP::FillSolidRect(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	((Gdiplus::SolidBrush*)mp_brush)->SetColor(m_temp_color);
	mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
}

// �簢���� �׸��� (ä���)
void DCP::FillSolidRect(INT a_sx, INT a_sy, INT a_ex, INT a_ey)
{
	mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
}

// ������ �������� �簢���� �׸��� (�׵θ�)
void DCP::DrawRect(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	mp_pen->SetColor(m_temp_color);
	mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

// �簢���� �׸��� (�׵θ�)
void DCP::DrawRect(INT a_sx, INT a_sy, INT a_ex, INT a_ey)
{
	mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

// Ÿ���� �׸���. (ä���� �׵θ� ��� ����, ������ ����ϴ� �귯�ÿ� ������)
void DCP::Ellipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey)
{
	// ���� ä���
	mp_graphic->FillEllipse(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
	// �׵θ� �׸���
	mp_graphic->DrawEllipse(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

// ������ �������� Ÿ���� �׸��� (ä��⸸ ����)
void DCP::FillSolidEllipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	((Gdiplus::SolidBrush*)mp_brush)->SetColor(m_temp_color);
	mp_graphic->FillEllipse(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
}

// ���� �귯�÷� Ÿ���� �׸��� (ä��⸸ ����)
void DCP::FillSolidEllipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey)
{
	mp_graphic->FillEllipse(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
}

// ������ �������� Ÿ���� �׸��� (�׵θ�)
void DCP::DrawEllipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	mp_pen->SetColor(m_temp_color);
	mp_graphic->DrawEllipse(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

// Ÿ���� �׸��� (�׵θ�)
void DCP::DrawEllipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey)
{
	mp_graphic->DrawEllipse(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

// ������ ���� �׸��� (�������� ���� ���, �������� ����)
void DCP::DrawLine(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	mp_pen->SetColor(m_temp_color);
	mp_graphic->DrawLine(mp_pen, a_sx, a_sy, a_ex, a_ey);
	m_last_position_x = a_ex;
	m_last_position_y = a_ey;
}

// ������ ���� �׸���. (�������� ���� ���)
void DCP::DrawLine(INT a_sx, INT a_sy, INT a_ex, INT a_ey)
{
	mp_graphic->DrawLine(mp_pen, a_sx, a_sy, a_ex, a_ey);
	m_last_position_x = a_ex;
	m_last_position_y = a_ex;
}

// ���� �������� ���Ѵ�. ���� �׷����� �ʴ´�.
void DCP::MoveTo(INT a_x, INT a_y)
{
	m_last_position_x = a_x;
	m_last_position_y = a_y;
}

// ������ �׸� �� �Ǵ� MoveTo�� ������ �����κ��� ������ �����ϴ� ���� �׸���.
void DCP::LineTo(INT a_x, INT a_y)
{
	mp_graphic->DrawLine(mp_pen, m_last_position_x, m_last_position_y, a_x, a_y);
	m_last_position_x = a_x;
	m_last_position_y = a_y;
}

// ���� ä���� �ٰ��� �׸���
void DCP::FillPolygon(Gdiplus::Point* ap_position_list, INT a_count)
{
	mp_graphic->FillPolygon(mp_brush, ap_position_list, a_count);
}

// �ٰ��� �׵θ� �׸���
void DCP::DrawPolygon(Gdiplus::Point* ap_position_list, INT a_count)
{
	mp_graphic->DrawPolygon(mp_pen, ap_position_list, a_count);
}

// Arc �׵θ� �׸���
void DCP::DrawArc(Gdiplus::REAL a_x, Gdiplus::REAL a_y, Gdiplus::REAL a_cx, Gdiplus::REAL a_cy, Gdiplus::REAL a_start_angle, Gdiplus::REAL a_sweep_angle)
{
	mp_graphic->DrawArc(mp_pen, a_x, a_y, a_cx, a_cy, a_start_angle, a_sweep_angle);
}

// �귯�� ���� ����
void DCP::SetDCBrushColor(Gdiplus::ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	((Gdiplus::SolidBrush*)mp_brush)->SetColor(m_temp_color);
}

// �� ���� ����
void DCP::SetDCPenColor(Gdiplus::ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	mp_pen->SetColor(m_temp_color);
}

// �� ���� (��Ÿ��, ����, ����)
void DCP::SetDCPenColor(Gdiplus::DashStyle a_style, Gdiplus::REAL a_width, Gdiplus::ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	mp_pen->SetColor(m_temp_color);
	mp_pen->SetWidth(a_width);
	mp_pen->SetDashStyle(a_style);
}

// �۲� ���� ����
void DCP::SetTextColor(Gdiplus::ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	((Gdiplus::SolidBrush*)mp_font_brush)->SetColor(m_temp_color);
}

// ��Ʈ �۲�, ũ�� �缳��
Gdiplus::Font* DCP::SelectObject(Gdiplus::Font* ap_font)
{
	Gdiplus::Font* p_old_font = mp_font;
	mp_font = ap_font;
	return p_old_font;					// ���� ��Ʈ ��ü�� �ּҸ� ��ȯ
}

// ��Ʈ �۲�, ũ�� �缳��
void DCP::SelectObject(const TCHAR* ap_style, INT a_size)
{
	delete mp_font;
	mp_font = new Gdiplus::Font(ap_style, a_size);
}

// ���ڿ� ��� (����)
void DCP::GpTextOut(INT a_x, INT a_y, Gdiplus::ARGB a_color, const TCHAR* ap_str, INT a_str_len)
{
	m_temp_color.SetValue(a_color);
	((Gdiplus::SolidBrush*)mp_font_brush)->SetColor(m_temp_color);
	mp_graphic->DrawString(ap_str, a_str_len, mp_font, Gdiplus::PointF(Gdiplus::REAL(a_x), Gdiplus::REAL(a_y)), mp_font_brush);
}

// ���ڿ� ���
void DCP::GpTextOut(INT a_x, INT a_y, const TCHAR* ap_str, INT a_str_len)
{
	mp_graphic->DrawString(ap_str, a_str_len, mp_font, Gdiplus::PointF(Gdiplus::REAL(a_x), Gdiplus::REAL(a_y)), mp_font_brush);
}

// �̹��� ��ü�� ���
void DCP::Draw(Gdiplus::Image* ap_image, INT a_x, INT a_y)
{
	// �̹��� ���
	mp_graphic->DrawImage(ap_image, a_x, a_y);
}

// ��θ� �޾� �ش� �̹��� ��� (���� ũ��)
void DCP::Draw(TCHAR* a_file_path, INT a_x, INT a_y)
{
	Gdiplus::Image* image = Gdiplus::Image::FromFile(a_file_path);
	// �̹��� ���
	mp_graphic->DrawImage(image, a_x, a_y);
}

// ��θ� �޾� ���ϴ� ũ��� �̹��� ���
void DCP::Draw(TCHAR* a_file_path, INT a_x, INT a_y, INT a_width, INT a_height)
{
	Gdiplus::Image* image = Gdiplus::Image::FromFile(a_file_path);
	// �̹��� ���
	mp_graphic->DrawImage(image, Gdiplus::Rect(a_x, a_y, a_width, a_height));
}

// DC�� ���� �̹����� ���
void DCP::Draw(HDC ah_dc, INT a_x, INT a_y)
{
	// ���޵� DC�� ���� �̹����� ���
	Gdiplus::Graphics* p_graphic = new Gdiplus::Graphics(ah_dc);
	p_graphic->DrawImage(mp_bitmap, a_x, a_y);
	delete p_graphic;
}

Gdiplus::Image* DCP::GetImage()
{
	return mp_bitmap;
}

Gdiplus::Graphics* DCP::GetGraphics()
{
	return mp_graphic;
}

DCP::operator Gdiplus::Image* ()
{
	return mp_bitmap;
}

DCP::operator Gdiplus::Graphics* ()
{
	return mp_graphic;
}

