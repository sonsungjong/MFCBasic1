// TW_DCP.cpp: ���� ����
#include "pch.h"
#include "TW_DCP.h"

// static ��� ���� �ʱ�ȭ
int TW_DCP::m_object_count = 0;
ULONG_PTR TW_DCP::m_token = 0;

TW_DCP::TW_DCP()
{
    Init();
}

TW_DCP::TW_DCP(int a_cx, int a_cy)
{
    Init();
    CreateDCP(a_cx, a_cy);
}

TW_DCP::~TW_DCP()
{
    // ����ϴ� GDI+ ��ü�� �����Ѵ�.
    delete mp_brush;
    delete mp_pen;
    delete mp_font;
    delete mp_font_brush;

    m_object_count--;  // DCP ��ü�� ���� ���ҽ�Ų��.
    // �� ��ü�� DCP ��ü�� ������ ��ü��� GDI+�� �����Ѵ�.
    if (m_object_count == 0) GdiplusShutdown(m_token);
}

void TW_DCP::Init()
{
    if (m_object_count == 0) { // �� ��ü�� DCP ��ü�� ù ��ü��� GDI+�� �ʱ�ȭ�Ѵ�.
        GdiplusStartupInput gpsi;
        GdiplusStartup(&m_token, &gpsi, NULL);
    }
    m_object_count++;  // DCP ��ü�� ���� ������Ų��.
    m_last_pos_x = m_last_pos_y = m_cx = m_cy = 0;  // ��ǥ �� ũ�� ���� �ʱ�ȭ
    mp_bitmap = NULL;   // ��µ� �̹����� ������ �̹��� ��ü
    mp_graphic = NULL;  // �׸� �׸��� �۾��� ������ ��ü

    mp_brush = new SolidBrush(RGB24(255, 255, 255));  // ��� �귯�ø� �����Ѵ�.
    mp_font_brush = new SolidBrush(RGB24(0, 0, 0));  // �۲ÿ� ����� ������ �귯�ø� �����Ѵ�.
    mp_pen = new Pen(RGB24(0, 0, 0));  // �׷����� �� ������ �����Ѵ�.
    mp_font = new Gdiplus::Font(L"����ü", 9);  // �⺻ �۲��� �����Ѵ�.   
}

// GDI+�� �۲� ��ü �����ϴ� �Լ�
Gdiplus::Font *TW_DCP::CreateFontObject(const wchar_t *ap_font_name, REAL a_font_size)
{
    return new Gdiplus::Font(ap_font_name, a_font_size);
}

// ������ �۲� ��ü�� �����ϴ� �Լ�
void TW_DCP::DestroyFont(Gdiplus::Font *ap_font)
{
    delete ap_font;
}

void TW_DCP::CreateDCP(int a_cx, int a_cy)
{
    // ��� ��ġ�� �����Ǿ� ���� �ʰų� ���� ���̰� �޶������ �����Ѵ�.
    if (mp_graphic == NULL || m_cx != a_cx || m_cy != a_cy) {
        // ���ο� ���� ���̷� ����
        m_cx = a_cx;
        m_cy = a_cy;
        // ������ ����ϴ� ��ü���� �����Ѵ�.
        if (mp_graphic != NULL) delete mp_graphic;
        if (mp_bitmap != NULL) delete mp_bitmap;
        // ���ο� ũ�⿡ �°� ��Ʈ�ʰ� ��� �׷��� ��ü�� �����Ѵ�.
        mp_bitmap = new Bitmap(m_cx, m_cy);  // ��Ʈ���� ����
        mp_graphic = new Graphics(mp_bitmap); // ������ �̹����� ����ϴ� �׷��� ��ü�� ����

        // 'AntiAlias'�� ����ϵ��� �����Ѵ�. (������ SmoothingModeInvalid)
        mp_graphic->SetSmoothingMode(SmoothingModeAntiAlias);
    }
}

// a_color�� ��ü ������ ä���.
void TW_DCP::Clear(ARGB a_color)
{
    mp_graphic->Clear(a_color);
}

// ������ Brush �������� ��ü ������ ä���.
void TW_DCP::Clear()
{
    mp_graphic->Clear(m_temp_color);
}

// ������ ����ϴ� ��� �귯�÷� �簢���� �׸���. (ä���, �׵θ� ��� ����)
void TW_DCP::Rectangle(int a_sx, int a_sy, int a_ex, int a_ey)
{
    mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy); // ä��� ����
    mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1); // �׵θ� �׸�
}

// ������ �������� �簢���� �׸���. (ä��⸸ ����)
void TW_DCP::FillSolidRect(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{
    m_temp_color.SetValue(a_color); // ������ ������ ���� ��ü�� ����
    ((SolidBrush *)mp_brush)->SetColor(m_temp_color);  // �귯�� ��ü�� ���� �ݿ�
    mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);  // ä��� ����
}

// ���ο� ������ �������� �ʰ� ���� �귯�÷� �簢���� �׸���. (ä��⸸ ����)
void TW_DCP::FillSolidRect(int a_sx, int a_sy, int a_ex, int a_ey)
{
    mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy); // ä��� ����
}

// ������ �������� �簢���� �׸���. (�׵θ��� �׸�)
void TW_DCP::DrawRect(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{
    m_temp_color.SetValue(a_color); // ������ ������ ���� ��ü�� ����
    mp_pen->SetColor(m_temp_color);  // �� ��ü�� ���� �ݿ�
    mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);  // �׵θ� �׸�
}

// ���ο� ������ �������� �ʰ� ���� ������ �簢���� �׸���. (�׵θ��� �׸�)
void TW_DCP::DrawRect(int a_sx, int a_sy, int a_ex, int a_ey)
{
    mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1); // �׵θ� �׸�
}

// ������ ����ϴ� ��� �귯�÷� Ÿ���� �׸���. (ä���, �׵θ� ��� ����)
void TW_DCP::Ellipse(int a_sx, int a_sy, int a_ex, int a_ey)
{
    mp_graphic->FillEllipse(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);  // ä��� ����
    mp_graphic->DrawEllipse(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1); // �׵θ� �׸�
}
// ������ �������� Ÿ���� �׸���. (ä��⸸ ����)
void TW_DCP::FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{
    m_temp_color.SetValue(a_color); // ������ ������ ���� ��ü�� ����
    ((SolidBrush *)mp_brush)->SetColor(m_temp_color); // �귯�� ��ü�� ���� �ݿ�
    mp_graphic->FillEllipse(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy); // �׵θ� �׸�
}

// ���ο� ������ �������� �ʰ� ���� �귯�÷� Ÿ���� �׸���. (ä��⸸ ����)
void TW_DCP::FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey)
{
    mp_graphic->FillEllipse(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy); // �׵θ� �׸�
}

// ������ �������� Ÿ���� �׸���. (�׵θ��� �׸�)
void TW_DCP::DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{
    m_temp_color.SetValue(a_color); // ������ ������ ���� ��ü�� ����
    mp_pen->SetColor(m_temp_color); // �� ��ü�� ���� �ݿ�
    mp_graphic->DrawEllipse(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);  // �׵θ� �׸�
}

// ���ο� ������ �������� �ʰ� ���� ������ Ÿ���� �׸���. (�׵θ��� �׸�)
void TW_DCP::DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey)
{
    mp_graphic->DrawEllipse(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1); // �׵θ� �׸�
}

// ������ �������� ���� �׸���. (���� ���� �� �� ���)
void TW_DCP::DrawLine(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{
    m_temp_color.SetValue(a_color); // ������ ������ ���� ��ü�� ����
    mp_pen->SetColor(m_temp_color); // �� ��ü�� ���� �ݿ�
    mp_graphic->DrawLine(mp_pen, a_sx, a_sy, a_ex, a_ey); // �� �׸�
    m_last_pos_x = a_ex; // ���� ������ LineTo �Լ��� ������ �� �ֵ��� ����Ѵ�.
    m_last_pos_y = a_ey;
}

// ���� ������ ���� �׸���. (���� ���� �� �� ���)
void TW_DCP::DrawLine(int a_sx, int a_sy, int a_ex, int a_ey)
{
    mp_graphic->DrawLine(mp_pen, a_sx, a_sy, a_ex, a_ey);  // ���׸�
    m_last_pos_x = a_ex; // ���� ������ LineTo �Լ��� ������ �� �ֵ��� ����Ѵ�.
    m_last_pos_y = a_ey;
}

// ���� ���� ���� �����Ѵ�. ���� �׷������� �ʴ´�.
void TW_DCP::MoveTo(int a_x, int a_y)
{
    m_last_pos_x = a_x;
    m_last_pos_y = a_y;
}

// MoveTo �Լ��� ������ ���̳� ������ �׸� ���� ������ �����ϴ� ���� �׸���.
void TW_DCP::LineTo(int a_x, int a_y)
{
    mp_graphic->DrawLine(mp_pen, m_last_pos_x, m_last_pos_y, a_x, a_y); // ���׸�
    m_last_pos_x = a_x;  // ���� ������ LineTo �Լ��� ������ �� �ֵ��� ����Ѵ�.
    m_last_pos_y = a_y;
}

// ���ӵ� ���� �׸��� �Լ�
void TW_DCP::DrawLines(Gdiplus::Point *ap_pos_list, int a_count)
{
    mp_graphic->DrawLines(mp_pen, ap_pos_list, a_count);
}

// ���� ä������ �ٰ����� �׸��� �Լ�
void TW_DCP::FillPolygon(Gdiplus::Point *ap_pos_list, int a_count)
{
    mp_graphic->FillPolygon(mp_brush, ap_pos_list, a_count);
}

// �ٰ����� �׵θ��� �׸��� �Լ�
void TW_DCP::DrawPolygon(Gdiplus::Point *ap_pos_list, int a_count)
{
    mp_graphic->DrawPolygon(mp_pen, ap_pos_list, a_count);
}

// Arc�� �׵θ��� �׸��� �Լ�
void TW_DCP::DrawArc(REAL a_x, REAL a_y, REAL a_cx, REAL a_cy, REAL a_start_angle, REAL a_sweep_angle)
{
    mp_graphic->DrawArc(mp_pen, a_x, a_y, a_cx, a_cy, a_start_angle, a_sweep_angle);
}

// Pie�� �׸��� �Լ�
void TW_DCP::FillPie(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle)
{
    mp_graphic->FillPie(mp_brush, a_x, a_y, a_cx, a_cy, a_start_angle, a_sweep_angle);
}

// �귯�� ��ü�� ������ �����Ѵ�.
void TW_DCP::SetDCBrushColor(ARGB a_color)
{
    m_temp_color.SetValue(a_color);  // ������ ������ ���� ��ü�� ����
    ((SolidBrush *)mp_brush)->SetColor(m_temp_color); // �귯�� ��ü�� ���� �ݿ�
}

// �� ��ü�� ������ �����Ѵ�.
void TW_DCP::SetDCPenColor(ARGB a_color)
{
    m_temp_color.SetValue(a_color); // ������ ������ ���� ��ü�� ����
    mp_pen->SetColor(m_temp_color); // �� ��ü�� ���� �ݿ�
}

// �� ��ü�� �Ӽ��� �����Ѵ�. (��Ÿ��, ����, ����)
void TW_DCP::SetDCPenColor(DashStyle a_style, REAL a_width, ARGB a_color)
{
    m_temp_color.SetValue(a_color); // ������ ������ ���� ��ü�� ����
    mp_pen->SetColor(m_temp_color); // �� ��ü�� ���� �ݿ�
    mp_pen->SetWidth(a_width);  // �� ��ü�� ���� �ݿ�
    mp_pen->SetDashStyle(a_style); // �� ��ü�� ��Ÿ�� �ݿ�
}

void TW_DCP::SetTextColor(ARGB a_color)  // �۲��� ������ ����
{
    m_temp_color.SetValue(a_color); // ������ ������ ���� ��ü�� ����
    ((SolidBrush *)mp_font_brush)->SetColor(m_temp_color); // �귯�� ��ü�� ���� �ݿ�
}

// ��Ʈ ��ü�� �ٽ� �����Ѵ�. �� �Լ��� ������ �����Ǿ� �ִ� ��Ʈ ��ü�� �ּҸ� ��ȯ�Ѵ�.
Gdiplus::Font *TW_DCP::SelectObject(Gdiplus::Font *ap_font)
{
    Gdiplus::Font *p_old_font = mp_font;  // ������ ��Ʈ ��ü�� ��ȯ�ϱ� ���� ����Ѵ�.
    mp_font = ap_font;  // ���ο� ��Ʈ ��ü�� �����Ѵ�.
    return p_old_font;  // ���� ��Ʈ ��ü�� �ּҸ� ��ȯ�Ѵ�.
}

// ���ڿ��� ������ ��ġ�� ����Ѵ�. (���� ���� ����)
void TW_DCP::TextOut(int a_x, int a_y, ARGB a_color, const wchar_t *ap_str, int a_str_len)
{
    m_temp_color.SetValue(a_color); // ������ ������ ���� ��ü�� ����
    ((SolidBrush *)mp_font_brush)->SetColor(m_temp_color); // �귯�� ��ü�� ���� �ݿ�
    mp_graphic->DrawString(ap_str, a_str_len, mp_font, PointF(REAL(a_x), REAL(a_y)), mp_font_brush);
}

// ���ڿ��� ������ ��ġ�� ����Ѵ�.
void TW_DCP::TextOut(int a_x, int a_y, const wchar_t *ap_str, int a_str_len)
{
    mp_graphic->DrawString(ap_str, a_str_len, mp_font, PointF(REAL(a_x), REAL(a_y)), mp_font_brush);
}

// path ��ü�� �����ϴ� �Լ�
GraphicsPath *TW_DCP::CreatePath()
{
    return new GraphicsPath();
}

// path ��ü�� �����ϴ� �Լ�
void TW_DCP::DestroyPath(GraphicsPath *ap_path)
{
    delete ap_path;
}

// �������� ������ �� ���� �����ؼ� �׸��� �׸��� �Լ�
void TW_DCP::DrawPath(GraphicsPath *ap_path)
{
    mp_graphic->DrawPath(mp_pen, ap_path);
}

// �������� ������ �� ���� �����ؼ� �׸��� �׸��� �Լ�
void TW_DCP::FillPath(GraphicsPath *ap_path)
{
    mp_graphic->FillPath(mp_brush, ap_path);
}

// �������� ������ �� ���� �����ؼ� �׸��� �׸��� �Լ�
void TW_DCP::ShowPath(GraphicsPath *ap_path)
{
    mp_graphic->FillPath(mp_brush, ap_path);
    mp_graphic->DrawPath(mp_pen, ap_path);
}

// ���޵� �̹��� ��ü�� ��� (�ٸ� �̹��� ��ü�� �� �̹��� ��ü�� ����ϴ� �Լ�)
void TW_DCP::Draw(Image *ap_image, int a_x, int a_y)
{
    mp_graphic->DrawImage(ap_image, a_x, a_y);  // �̹����� ���
}

// ���޵� DC�� ���� �̹����� ���
void TW_DCP::Draw(HDC ah_dc, int a_x, int a_y)
{
    Graphics *p_graphic = new Graphics(ah_dc);  // DC �ڵ� ���� ����Ͽ� ��¿� �׷��� ��ü ����
    p_graphic->DrawImage(mp_bitmap, a_x, a_y);  // ��Ʈ�ʿ� �׷��� �̹����� ȭ�鿡 ���
    delete p_graphic;  // ����ϴ� �׷��� ��ü�� �����Ѵ�.
}