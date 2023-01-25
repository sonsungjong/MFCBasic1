#include "pch.h"
#include "DCP.h"

// static멤버변수(클래스 멤버만 공유할 수 있는 전역변수) 초기화
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

	m_object_count--;						// DCP 객체수 감소
	if (m_object_count == 0) {							// 마지막 객체가 해제될 때 GDI+ 를 해제
		Gdiplus::GdiplusShutdown(m_token);
	}
}

void DCP::Init()
{
	if (m_object_count == 0) {							// 첫 DCP 객체라면 GDI+ 를 초기화 시킨다.
		Gdiplus::GdiplusStartupInput gpsi;
		Gdiplus::GdiplusStartup(&m_token, &gpsi, NULL);
	}
	m_object_count++;						// DCP 객체수 증가
	// 좌표 및 크기 정보 초기화
	m_last_position_x = 0;
	m_last_position_y = 0;
	m_width = 0;
	m_height = 0;

	mp_bitmap = NULL;						// 출력 이미지를 저장할 이미지 객체
	mp_graphic = NULL;						// 그림 그리기 객체

	mp_brush = new Gdiplus::SolidBrush(RGB24(255, 255, 255));				// 기본 브러시
	mp_font_brush = new Gdiplus::SolidBrush(RGB24(0, 0, 0));					// 기본 브러시 (글꼴용)
	mp_pen = new Gdiplus::Pen(RGB24(0, 0, 0));				// 선 색상
	mp_font = new Gdiplus::Font(_T("굴림체"), 9);				// 기본 글꼴
}

void DCP::CreateDCP(INT a_width, INT a_height)
{
	// 출력 장치가 생성되어 있지 않거나 폭과 높이가 달라야만 생성한다.
	if (mp_graphic == NULL || m_width != a_width || m_height != a_height) {
		// 새로운 폭과 높이 설정
		m_width = a_width;
		m_height = a_height;

		// 기존 객체 제거
		if (mp_graphic != NULL) {
			delete mp_graphic;
		}
		if (mp_bitmap != NULL) {
			delete mp_bitmap;
		}

		// 새로운 크기에 맞게 비트맵과 출력 그래픽 객체 생성
		mp_bitmap = new Gdiplus::Bitmap(m_width, m_height);
		mp_graphic = new Gdiplus::Graphics(mp_bitmap);

		// 'AntiAlias' 사용
		mp_graphic->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
	}
}

// a_color로 전체 영역을 채운다.
void DCP::Clear(Gdiplus::ARGB a_color)
{
	mp_graphic->Clear(a_color);
}

// 설정된 Brush 색상으로 전체 영역을 채운다.
void DCP::Clear()
{
	mp_graphic->Clear(m_temp_color);
}

// 사각형을 그린다 (기존 브러시와 펜을 사용)
void DCP::Rectangle(INT a_sx, INT a_sy, INT a_ex, INT a_ey)
{
	// 내부 채우기
	mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
	// 테두리 그리기
	mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

// 사각형을 그린다 (펜색 지정, 브러시색 지정)
void DCP::Rectangle(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_pen_color, Gdiplus::ARGB a_fill_color)
{
	// 내부 채우기
	m_temp_color.SetValue(a_fill_color);
	((Gdiplus::SolidBrush*)mp_brush)->SetColor(m_temp_color);
	mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);

	// 테두리 그리기
	m_temp_color.SetValue(a_pen_color);
	mp_pen->SetColor(m_temp_color);
	mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

// 지정한 색상으로 사각형을 그린다 (채우기)
void DCP::FillSolidRect(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	((Gdiplus::SolidBrush*)mp_brush)->SetColor(m_temp_color);
	mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
}

// 사각형을 그린다 (채우기)
void DCP::FillSolidRect(INT a_sx, INT a_sy, INT a_ex, INT a_ey)
{
	mp_graphic->FillRectangle(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
}

// 지정한 색상으로 사각형을 그린다 (테두리)
void DCP::DrawRect(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	mp_pen->SetColor(m_temp_color);
	mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

// 사각형을 그린다 (테두리)
void DCP::DrawRect(INT a_sx, INT a_sy, INT a_ex, INT a_ey)
{
	mp_graphic->DrawRectangle(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

// 타원을 그린다. (채우기와 테두리 모두 수행, 기존의 사용하던 브러시와 펜으로)
void DCP::Ellipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey)
{
	// 내부 채우기
	mp_graphic->FillEllipse(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
	// 테두리 그리기
	mp_graphic->DrawEllipse(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

// 지정한 색상으로 타원을 그린다 (채우기만 수행)
void DCP::FillSolidEllipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	((Gdiplus::SolidBrush*)mp_brush)->SetColor(m_temp_color);
	mp_graphic->FillEllipse(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
}

// 기존 브러시로 타원을 그린다 (채우기만 수행)
void DCP::FillSolidEllipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey)
{
	mp_graphic->FillEllipse(mp_brush, a_sx, a_sy, a_ex - a_sx, a_ey - a_sy);
}

// 지정한 색상으로 타원을 그린다 (테두리)
void DCP::DrawEllipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	mp_pen->SetColor(m_temp_color);
	mp_graphic->DrawEllipse(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

// 타원을 그린다 (테두리)
void DCP::DrawEllipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey)
{
	mp_graphic->DrawEllipse(mp_pen, a_sx, a_sy, a_ex - a_sx - 1, a_ey - a_sy - 1);
}

// 펜으로 선을 그린다 (시작점과 끝점 사용, 색상지정 가능)
void DCP::DrawLine(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	mp_pen->SetColor(m_temp_color);
	mp_graphic->DrawLine(mp_pen, a_sx, a_sy, a_ex, a_ey);
	m_last_position_x = a_ex;
	m_last_position_y = a_ey;
}

// 펜으로 선을 그린다. (시작점과 끝점 사용)
void DCP::DrawLine(INT a_sx, INT a_sy, INT a_ex, INT a_ey)
{
	mp_graphic->DrawLine(mp_pen, a_sx, a_sy, a_ex, a_ey);
	m_last_position_x = a_ex;
	m_last_position_y = a_ex;
}

// 선의 시작점을 정한다. 선은 그려지지 않는다.
void DCP::MoveTo(INT a_x, INT a_y)
{
	m_last_position_x = a_x;
	m_last_position_y = a_y;
}

// 이전에 그린 선 또는 MoveTo로 지정한 점으로부터 끝점과 연결하는 선을 그린다.
void DCP::LineTo(INT a_x, INT a_y)
{
	mp_graphic->DrawLine(mp_pen, m_last_position_x, m_last_position_y, a_x, a_y);
	m_last_position_x = a_x;
	m_last_position_y = a_y;
}

// 속이 채워진 다각형 그리기
void DCP::FillPolygon(Gdiplus::Point* ap_position_list, INT a_count)
{
	mp_graphic->FillPolygon(mp_brush, ap_position_list, a_count);
}

// 다각형 테두리 그리기
void DCP::DrawPolygon(Gdiplus::Point* ap_position_list, INT a_count)
{
	mp_graphic->DrawPolygon(mp_pen, ap_position_list, a_count);
}

// Arc 테두리 그리기
void DCP::DrawArc(Gdiplus::REAL a_x, Gdiplus::REAL a_y, Gdiplus::REAL a_cx, Gdiplus::REAL a_cy, Gdiplus::REAL a_start_angle, Gdiplus::REAL a_sweep_angle)
{
	mp_graphic->DrawArc(mp_pen, a_x, a_y, a_cx, a_cy, a_start_angle, a_sweep_angle);
}

// 브러시 색상 변경
void DCP::SetDCBrushColor(Gdiplus::ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	((Gdiplus::SolidBrush*)mp_brush)->SetColor(m_temp_color);
}

// 팬 색상 변경
void DCP::SetDCPenColor(Gdiplus::ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	mp_pen->SetColor(m_temp_color);
}

// 팬 변경 (스타일, 굵기, 색상)
void DCP::SetDCPenColor(Gdiplus::DashStyle a_style, Gdiplus::REAL a_width, Gdiplus::ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	mp_pen->SetColor(m_temp_color);
	mp_pen->SetWidth(a_width);
	mp_pen->SetDashStyle(a_style);
}

// 글꼴 색상 변경
void DCP::SetTextColor(Gdiplus::ARGB a_color)
{
	m_temp_color.SetValue(a_color);
	((Gdiplus::SolidBrush*)mp_font_brush)->SetColor(m_temp_color);
}

// 폰트 글꼴, 크기 재설정
Gdiplus::Font* DCP::SelectObject(Gdiplus::Font* ap_font)
{
	Gdiplus::Font* p_old_font = mp_font;
	mp_font = ap_font;
	return p_old_font;					// 이전 폰트 객체의 주소를 반환
}

// 폰트 글꼴, 크기 재설정
void DCP::SelectObject(const TCHAR* ap_style, INT a_size)
{
	delete mp_font;
	mp_font = new Gdiplus::Font(ap_style, a_size);
}

// 문자열 출력 (색상)
void DCP::GpTextOut(INT a_x, INT a_y, Gdiplus::ARGB a_color, const TCHAR* ap_str, INT a_str_len)
{
	m_temp_color.SetValue(a_color);
	((Gdiplus::SolidBrush*)mp_font_brush)->SetColor(m_temp_color);
	mp_graphic->DrawString(ap_str, a_str_len, mp_font, Gdiplus::PointF(Gdiplus::REAL(a_x), Gdiplus::REAL(a_y)), mp_font_brush);
}

// 문자열 출력
void DCP::GpTextOut(INT a_x, INT a_y, const TCHAR* ap_str, INT a_str_len)
{
	mp_graphic->DrawString(ap_str, a_str_len, mp_font, Gdiplus::PointF(Gdiplus::REAL(a_x), Gdiplus::REAL(a_y)), mp_font_brush);
}

// 이미지 객체를 출력
void DCP::Draw(Gdiplus::Image* ap_image, INT a_x, INT a_y)
{
	// 이미지 출력
	mp_graphic->DrawImage(ap_image, a_x, a_y);
}

// 경로를 받아 해당 이미지 출력 (원본 크기)
void DCP::Draw(TCHAR* a_file_path, INT a_x, INT a_y)
{
	Gdiplus::Image* image = Gdiplus::Image::FromFile(a_file_path);
	// 이미지 출력
	mp_graphic->DrawImage(image, a_x, a_y);
}

// 경로를 받아 원하는 크기로 이미지 출력
void DCP::Draw(TCHAR* a_file_path, INT a_x, INT a_y, INT a_width, INT a_height)
{
	Gdiplus::Image* image = Gdiplus::Image::FromFile(a_file_path);
	// 이미지 출력
	mp_graphic->DrawImage(image, Gdiplus::Rect(a_x, a_y, a_width, a_height));
}

// DC에 현재 이미지를 출력
void DCP::Draw(HDC ah_dc, INT a_x, INT a_y)
{
	// 전달된 DC에 현재 이미지를 출력
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

