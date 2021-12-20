#ifndef _TW_DCP_H_
#define _TW_DCP_H_

// �� Ŭ������ GDI+ �Լ����� ���ϰ� ����� �� �ֵ��� ��������ϴ�.
// �� Ŭ������ ������ ��� �����鼭 �����ǰų� ����� �߰��ɼ� �ֽ��ϴ�.
// -------------------------------------------------------------------------
// �� Ŭ������ ó�� ���� ����� ����� �����ϴ� �������� ���۱� ǥ�ø� ������ �ּ���.
// Ŭ���� �ʱ� �� ���� : �輺��(tipsware@naver.com)
// Ŭ���� ���� : https://cafe.naver.com/mythread
// ó�� ���� ��¥ : 2020�� 3�� 24�� (ȭ����)
// ó�� ������ ������Ʈ ��¥ : 2020�� 3�� 25�� (������)

// �� Ŭ������ ����̳� ������ �����ߴٸ� �Ʒ��� �̷��� �����ֽø� �˴ϴ�.
// Ŭ���� ���� ������ : �ռ���
// ������ ���� ��¥ :


#include <Gdiplus.h>       // GDI+�� ����ϱ� ���� ��� ����
using namespace Gdiplus;   // Gdiplus:: ǥ���� ���̱� ����

#define RGB24(r,g,b) (0xFF000000 | (r << 16) | (g << 8) | b)   // 0xFFRRGGBB
#define RGB32(a,r,g,b) ((a << 24) | (r << 16) | (g << 8) | b)  // 0xAARRGGBB

// DCP�� DC Plus�� �ǹ�, �� Ŭ������ ���� ���۸� ������ �׻� ����Ѵ�.
class TW_DCP
{
protected:
    Brush *mp_brush;  // �귯�� ��ü
    Brush *mp_font_brush;  // �۲� �������� ����� �귯�� ��ü
    Pen *mp_pen;  // �� ��ü
    Gdiplus::Font *mp_font;  // ��Ʈ ��ü
    Bitmap *mp_bitmap;  // ��Ʈ�� ��ü
    Graphics *mp_graphic;  // ��¿� ��ü

    int m_cx, m_cy;  // ��� ������ ũ�� (���� ����)
    int m_last_pos_x, m_last_pos_y;  // Line�� ������ �׸� �� ���
    Color m_temp_color;  // ������ ������ �� �ӽ÷� ����� ��ü

    static ULONG_PTR m_token;  // GDI+ ���̺귯�� �������
    static int m_object_count;  // DCP ��ü�� ������ ���

public:
    TW_DCP();
    TW_DCP(int a_cx, int a_cy);
    virtual ~TW_DCP();

    void Init();  // ��ü�� �ʱ�ȭ�� �� ����ϴ� �⺻ �Լ�
    void CreateDCP(int a_cx, int a_cy);   // �۾� ������ �����ؼ� ��� ��ü�� �����ϴ� �Լ�
    void Clear(ARGB a_color); // a_color�� ��ü ������ ä���.
    void Clear();  // ������ Brush �������� ��ü ������ ä���.

    // �簢���� �׸��� �Լ���
    void Rectangle(int a_sx, int a_sy, int a_ex, int a_ey);  // ä���� �׵θ� ���� �׸�
    void FillSolidRect(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color);  // ä��⸸ ��
    void FillSolidRect(int a_sx, int a_sy, int a_ex, int a_ey);  // ä��⸸ ��
    void DrawRect(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color);  // �׵θ��� �׸�
    void DrawRect(int a_sx, int a_sy, int a_ex, int a_ey); // �׵θ��� �׸�

    // Ÿ���� �׸��� �Լ���
    void Ellipse(int a_sx, int a_sy, int a_ex, int a_ey);  // ä���� �׵θ� ���� �׸�
    void FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color); // ä��⸸ ��
    void FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey); // ä��⸸ ��
    void DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color); // �׵θ��� �׸�
    void DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey); // �׵θ��� �׸�

    // ���� �׸��� �Լ���
    void DrawLine(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color);  // ����, ���� ����ؼ� ���׸���
    void DrawLine(int a_sx, int a_sy, int a_ex, int a_ey);  // ����, ���� ����ؼ� ���׸���
    void MoveTo(int a_x, int a_y);  // ���� ���� ��ġ�� ����
    void LineTo(int a_x, int a_y);  // MoveTo �Ǵ� ������ LineTo�� ����� ������ ���� ����
    void DrawArc(REAL a_x, REAL a_y, REAL a_cx, REAL a_cy, REAL a_start_angle, REAL a_sweep_angle); // Arc�� �׵θ��� �׸��� �Լ�
    void FillPie(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle); // Pie�� �׸��� �Լ�

    // ���ӵ� ���� �׸��� �Լ�
    void DrawLines(Gdiplus::Point *ap_pos_list, int a_count);

    // �ٰ����� �׸��� �Լ���
    void FillPolygon(Gdiplus::Point *ap_pos_list, int a_count); // ���� ä������ �ٰ����� �׸��� �Լ�
    void DrawPolygon(Gdiplus::Point *ap_pos_list, int a_count); // �ٰ����� �׵θ��� �׸��� �Լ�

    void SetDCBrushColor(ARGB a_color);  // ä��� ������ ����
    void SetDCPenColor(ARGB a_color);  // �� ������ ����
    void SetDCPenColor(DashStyle a_style, REAL a_width, ARGB a_color);  // �� ��Ÿ��, ���� �׸��� �� ���� ����
    void SetTextColor(ARGB a_color);  // �۲��� ������ ����
    Gdiplus::Font *SelectObject(Gdiplus::Font *ap_font);  // ��Ʈ ��ü�� �ٽ� �����Ѵ�.
    Gdiplus::Font *CreateFontObject(const wchar_t *ap_font_name, REAL a_font_size); // GDI+�� �۲� ��ü�� �����ϴ� �Լ�    
    void DestroyFont(Gdiplus::Font *ap_font); // ������ �۲� ��ü�� �����ϴ� �Լ�


    void Draw(Image *ap_image, int a_x, int a_y);  // ���޵� �̹��� ��ü�� ���
    void Draw(HDC ah_dc, int a_x = 0, int a_y = 0);  // ���޵� DC�� ���� �̹����� ���

    // ���ڿ��� ������ ��ġ�� ����ϴ� �Լ���
    void TextOut(int a_x, int a_y, ARGB a_color, const wchar_t *ap_str, int a_str_len);
    void TextOut(int a_x, int a_y, const wchar_t *ap_str, int a_str_len);

    GraphicsPath *CreatePath(); // path ��ü�� �����ϴ� �Լ�
    void DestroyPath(GraphicsPath *ap_path); // path ��ü�� �����ϴ� �Լ�
    void DrawPath(GraphicsPath *ap_path);  // �������� ������ �� ���� �����ؼ� �׸��� �׸��� �Լ�
    void FillPath(GraphicsPath *ap_path);  // �������� ������ �� ���� �����ؼ� �׸��� �׸��� �Լ�
    void ShowPath(GraphicsPath *ap_path);  // �������� ������ �� ���� �����ؼ� �׸��� �׸��� �Լ�


    // ���� ��ȣ ����� ���� �ܺο��� ����� �� �ְ� ���ִ� �Լ���
    Image *GetImage() { return mp_bitmap; }
    Graphics *GetGraphics() { return mp_graphic; }

    // GetImage �Լ��� GetGraphics �Լ��� ���ϰ� ����ϵ��� ������ �����ε� ���
    operator Image *() { return mp_bitmap; }
    operator Graphics *() { return mp_graphic; }
};

#endif