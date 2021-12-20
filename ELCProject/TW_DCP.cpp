// TW_DCP.cpp: 구현 파일
#include "pch.h"
#include "TW_DCP.h"

// static 멤버 변수 초기화
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
    // 사용하던 GDI+ 객체를 제거한다.
    delete mp_brush;
    delete mp_pen;
    delete mp_font;
    delete mp_font_brush;

    m_object_count--;  // DCP 객체의 수를 감소시킨다.
    // 이 객체가 DCP 객체의 마지막 객체라면 GDI+를 해제한다.
    if (m_object_count == 0) GdiplusShutdown(m_token);
}

void TW_DCP::Init()
{
    if (m_object_count == 0) { // 이 객체가 DCP 객체의 첫 객체라면 GDI+를 초기화한다.
        GdiplusStartupInput gpsi;
        GdiplusStartup(&m_token, &gpsi, NULL);
    }
    m_object_count++;  // DCP 객체의 수를 증가시킨다.
    m_last_pos_x = m_last_pos_y = m_cx = m_cy = 0;  // 좌표 및 크기 정보 초기화
    mp_bitmap = NULL;   // 출력된 이미지를 저장할 이미지 객체
    mp_graphic = NULL;  // 그림 그리기 작업을 진행할 객체

    mp_brush = new SolidBrush(RGB24(255, 255, 255));  // 흰색 브러시를 생성한다.
    mp_font_brush = new SolidBrush(RGB24(0, 0, 0));  // 글꼴에 사용할 검은색 브러시를 생성한다.
    mp_pen = new Pen(RGB24(0, 0, 0));  // 그래프의 선 색상을 생성한다.
    mp_font = new Gdiplus::Font(L"굴림체", 9);  // 기본 글꼴을 생성한다.   
}

// GDI+용 글꼴 객체 생성하는 함수
Gdiplus::Font *TW_DCP::CreateFontObject(const wchar_t *ap_font_name, REAL a_font_size)
{
    return new Gdiplus::Font(ap_font_name, a_font_size);
}

// 지정한 글꼴 객체를 제거하는 함수
void TW_DCP::DestroyFont(Gdiplus::Font *ap_font)
{
    delete ap_font;
}

void TW_DCP::CreateDCP(int a_cx, int a_cy)
{
    // 출력 장치가 생성되어 있지 않거나 폭과 높이가 달라야지만 생성한다.
    if (mp_graphic == NULL || m_cx != a_cx || m_cy != a_cy) {
        // 새로운 폭과 높이로 설정
        m_cx = a_cx;
        m_cy = a_cy;
        // 기존에 사용하던 객체들은 제거한다.
        if (mp_graphic != NULL) delete mp_graphic;
        if (mp_bitmap != NULL) delete mp_bitmap;
        // 새로운 크기에 맞게 비트맵과 출력 그래픽 객체를 생성한다.
        mp_bitmap = new Bitmap(m_cx, m_cy);  // 비트맵을 생성
        mp_graphic = new Graphics(mp_bitmap); // 생성된 이미지에 출력하는 그래픽 객체를 생성

        // 'AntiAlias'를 사용하도록 설정한다. (중지는 SmoothingModeInvalid)
        mp_graphic->SetSmoothingMode(SmoothingModeAntiAlias);
    }
}

// a_color로 전체 영역을 채운다.
void TW_DCP::Clear(ARGB a_color)
{
    mp_graphic->Clear(a_color);
}

// 설정된 Brush 색상으로 전체 영역을 채운다.
void TW_DCP::Clear()
{
    mp_graphic->Clear(m_temp_color);
}

// 기존에 사용하던 펜과 브러시로 사각형을 그린다. (채우기, 테두리 모두 수행)
void TW_DCP::Rectangle(int a_sx, int a_sy, int a_ex, int a_ey)
{
    mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy); // 채우기 수행
    mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1); // 테두리 그림
}

// 지정된 색상으로 사각형을 그린다. (채우기만 수행)
void TW_DCP::FillSolidRect(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{
    m_temp_color.SetValue(a_color); // 지정된 색상을 색상 객체에 설정
    ((SolidBrush *)mp_brush)->SetColor(m_temp_color);  // 브러시 객체에 색상 반영
    mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);  // 채우기 수행
}

// 새로운 색상을 지정하지 않고 기존 브러시로 사각형을 그린다. (채우기만 수행)
void TW_DCP::FillSolidRect(int a_sx, int a_sy, int a_ex, int a_ey)
{
    mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy); // 채우기 수행
}

// 지정된 색상으로 사각형을 그린다. (테두리만 그림)
void TW_DCP::DrawRect(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{
    m_temp_color.SetValue(a_color); // 지정된 색상을 색상 객체에 설정
    mp_pen->SetColor(m_temp_color);  // 펜 객체에 색상 반영
    mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);  // 테두리 그림
}

// 새로운 색상을 지정하지 않고 기존 펜으로 사각형을 그린다. (테두리만 그림)
void TW_DCP::DrawRect(int a_sx, int a_sy, int a_ex, int a_ey)
{
    mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1); // 테두리 그림
}

// 기존에 사용하던 펜과 브러시로 타원을 그린다. (채우기, 테두리 모두 수행)
void TW_DCP::Ellipse(int a_sx, int a_sy, int a_ex, int a_ey)
{
    mp_graphic->FillEllipse(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);  // 채우기 수행
    mp_graphic->DrawEllipse(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1); // 테두리 그림
}
// 지정된 색상으로 타원을 그린다. (채우기만 수행)
void TW_DCP::FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{
    m_temp_color.SetValue(a_color); // 지정된 색상을 색상 객체에 설정
    ((SolidBrush *)mp_brush)->SetColor(m_temp_color); // 브러시 객체에 색상 반영
    mp_graphic->FillEllipse(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy); // 테두리 그림
}

// 새로운 색상을 지정하지 않고 기존 브러시로 타원을 그린다. (채우기만 수행)
void TW_DCP::FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey)
{
    mp_graphic->FillEllipse(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy); // 테두리 그림
}

// 지정된 색상으로 타원을 그린다. (테두리만 그림)
void TW_DCP::DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{
    m_temp_color.SetValue(a_color); // 지정된 색상을 색상 객체에 설정
    mp_pen->SetColor(m_temp_color); // 펜 객체에 색상 반영
    mp_graphic->DrawEllipse(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);  // 테두리 그림
}

// 새로운 색상을 지정하지 않고 기존 펜으로 타원을 그린다. (테두리만 그림)
void TW_DCP::DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey)
{
    mp_graphic->DrawEllipse(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1); // 테두리 그림
}

// 지정한 색상으로 선을 그린다. (시작 점과 끝 점 사용)
void TW_DCP::DrawLine(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color)
{
    m_temp_color.SetValue(a_color); // 지정된 색상을 색상 객체에 설정
    mp_pen->SetColor(m_temp_color); // 펜 객체에 색상 반영
    mp_graphic->DrawLine(mp_pen, a_sx, a_sy, a_ex, a_ey); // 선 그림
    m_last_pos_x = a_ex; // 선의 끝점을 LineTo 함수로 연결할 수 있도록 기억한다.
    m_last_pos_y = a_ey;
}

// 기존 펜으로 선을 그린다. (시작 점과 끝 점 사용)
void TW_DCP::DrawLine(int a_sx, int a_sy, int a_ex, int a_ey)
{
    mp_graphic->DrawLine(mp_pen, a_sx, a_sy, a_ex, a_ey);  // 선그림
    m_last_pos_x = a_ex; // 선의 끝점을 LineTo 함수로 연결할 수 있도록 기억한다.
    m_last_pos_y = a_ey;
}

// 선의 시작 점을 지정한다. 선이 그려지지는 않는다.
void TW_DCP::MoveTo(int a_x, int a_y)
{
    m_last_pos_x = a_x;
    m_last_pos_y = a_y;
}

// MoveTo 함수로 지정한 점이나 이전에 그린 선의 끝점과 연결하는 선을 그린다.
void TW_DCP::LineTo(int a_x, int a_y)
{
    mp_graphic->DrawLine(mp_pen, m_last_pos_x, m_last_pos_y, a_x, a_y); // 선그림
    m_last_pos_x = a_x;  // 선의 끝점을 LineTo 함수로 연결할 수 있도록 기억한다.
    m_last_pos_y = a_y;
}

// 연속된 선을 그리는 함수
void TW_DCP::DrawLines(Gdiplus::Point *ap_pos_list, int a_count)
{
    mp_graphic->DrawLines(mp_pen, ap_pos_list, a_count);
}

// 속이 채워지는 다각형을 그리는 함수
void TW_DCP::FillPolygon(Gdiplus::Point *ap_pos_list, int a_count)
{
    mp_graphic->FillPolygon(mp_brush, ap_pos_list, a_count);
}

// 다각형의 테두리를 그리는 함수
void TW_DCP::DrawPolygon(Gdiplus::Point *ap_pos_list, int a_count)
{
    mp_graphic->DrawPolygon(mp_pen, ap_pos_list, a_count);
}

// Arc의 테두리를 그리는 함수
void TW_DCP::DrawArc(REAL a_x, REAL a_y, REAL a_cx, REAL a_cy, REAL a_start_angle, REAL a_sweep_angle)
{
    mp_graphic->DrawArc(mp_pen, a_x, a_y, a_cx, a_cy, a_start_angle, a_sweep_angle);
}

// Pie를 그리는 함수
void TW_DCP::FillPie(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle)
{
    mp_graphic->FillPie(mp_brush, a_x, a_y, a_cx, a_cy, a_start_angle, a_sweep_angle);
}

// 브러시 객체의 색상을 변경한다.
void TW_DCP::SetDCBrushColor(ARGB a_color)
{
    m_temp_color.SetValue(a_color);  // 지정된 색상을 색상 객체에 설정
    ((SolidBrush *)mp_brush)->SetColor(m_temp_color); // 브러시 객체에 색상 반영
}

// 펜 객체의 색상을 변경한다.
void TW_DCP::SetDCPenColor(ARGB a_color)
{
    m_temp_color.SetValue(a_color); // 지정된 색상을 색상 객체에 설정
    mp_pen->SetColor(m_temp_color); // 펜 객체에 색상 반영
}

// 펜 객체의 속성을 변경한다. (스타일, 굵기, 색상)
void TW_DCP::SetDCPenColor(DashStyle a_style, REAL a_width, ARGB a_color)
{
    m_temp_color.SetValue(a_color); // 지정된 색상을 색상 객체에 설정
    mp_pen->SetColor(m_temp_color); // 펜 객체에 색상 반영
    mp_pen->SetWidth(a_width);  // 펜 객체에 굵기 반영
    mp_pen->SetDashStyle(a_style); // 펜 객체에 스타일 반영
}

void TW_DCP::SetTextColor(ARGB a_color)  // 글꼴의 색상을 변경
{
    m_temp_color.SetValue(a_color); // 지정된 색상을 색상 객체에 설정
    ((SolidBrush *)mp_font_brush)->SetColor(m_temp_color); // 브러시 객체에 색상 반영
}

// 폰트 객체를 다시 설정한다. 이 함수는 이전에 설정되어 있던 폰트 객체의 주소를 반환한다.
Gdiplus::Font *TW_DCP::SelectObject(Gdiplus::Font *ap_font)
{
    Gdiplus::Font *p_old_font = mp_font;  // 기존의 폰트 객체를 반환하기 위해 백업한다.
    mp_font = ap_font;  // 새로운 폰트 객체로 설정한다.
    return p_old_font;  // 기존 폰트 객체의 주소를 반환한다.
}

// 문자열을 지정한 위치에 출력한다. (색상 지정 가능)
void TW_DCP::TextOut(int a_x, int a_y, ARGB a_color, const wchar_t *ap_str, int a_str_len)
{
    m_temp_color.SetValue(a_color); // 지정된 색상을 색상 객체에 설정
    ((SolidBrush *)mp_font_brush)->SetColor(m_temp_color); // 브러시 객체에 색상 반영
    mp_graphic->DrawString(ap_str, a_str_len, mp_font, PointF(REAL(a_x), REAL(a_y)), mp_font_brush);
}

// 문자열을 지정한 위치에 출력한다.
void TW_DCP::TextOut(int a_x, int a_y, const wchar_t *ap_str, int a_str_len)
{
    mp_graphic->DrawString(ap_str, a_str_len, mp_font, PointF(REAL(a_x), REAL(a_y)), mp_font_brush);
}

// path 객체를 생성하는 함수
GraphicsPath *TW_DCP::CreatePath()
{
    return new GraphicsPath();
}

// path 객체를 제거하는 함수
void TW_DCP::DestroyPath(GraphicsPath *ap_path)
{
    delete ap_path;
}

// 여러가지 도형을 한 번에 연결해서 그림을 그리는 함수
void TW_DCP::DrawPath(GraphicsPath *ap_path)
{
    mp_graphic->DrawPath(mp_pen, ap_path);
}

// 여러가지 도형을 한 번에 연결해서 그림을 그리는 함수
void TW_DCP::FillPath(GraphicsPath *ap_path)
{
    mp_graphic->FillPath(mp_brush, ap_path);
}

// 여러가지 도형을 한 번에 연결해서 그림을 그리는 함수
void TW_DCP::ShowPath(GraphicsPath *ap_path)
{
    mp_graphic->FillPath(mp_brush, ap_path);
    mp_graphic->DrawPath(mp_pen, ap_path);
}

// 전달된 이미지 객체를 출력 (다른 이미지 객체를 현 이미지 객체에 출력하는 함수)
void TW_DCP::Draw(Image *ap_image, int a_x, int a_y)
{
    mp_graphic->DrawImage(ap_image, a_x, a_y);  // 이미지를 출력
}

// 전달된 DC에 현재 이미지를 출력
void TW_DCP::Draw(HDC ah_dc, int a_x, int a_y)
{
    Graphics *p_graphic = new Graphics(ah_dc);  // DC 핸들 값을 사용하여 출력용 그래픽 객체 생성
    p_graphic->DrawImage(mp_bitmap, a_x, a_y);  // 비트맵에 그려진 이미지를 화면에 출력
    delete p_graphic;  // 사용하던 그래픽 객체를 제거한다.
}