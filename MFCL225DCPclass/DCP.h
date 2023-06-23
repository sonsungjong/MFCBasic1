#ifndef DCP_H_
#define DCP_H_

// 클래스 초기 모델 제작 : 김성엽(tipsware@naver.com)
// 클래스 배포 : https://cafe.naver.com/mythread
// 처음 만든 날짜 : 2020년 3월 24일 (화요일)
// 처음 마지막 업데이트 날짜 : 2020년 3월 25일 (수요일)

// 이 클래스의 기능이나 내용을 변경했다면 아래에 이력을 남겨주시면 됩니다.
// 클래스 내용 변경자 : 손성종
// 마지막 변경 날짜 : 2022년 12월 9일 (금요일)

#include <gdiplus.h>
using namespace Gdiplus;

// MFC는 lib 필요없음
//#pragma comment(lib, "gdiplus.lib")

#define RGB24(r,g,b) (0xFF000000 | ((r) << 16) | ((g) << 8) | (b))					// 0xFFRRGGBB
#define RGB32(a,r,g,b) (((a)<<24)|((r)<<16)|((g)<<8)|(b))							// 0xAARRGGBB

// DC Plus 클래스, 더블버퍼링 사용
class DCP
{
private:
	Gdiplus::Brush* mp_brush;
	Gdiplus::Brush* mp_font_brush;
	Gdiplus::Pen* mp_pen;
	Gdiplus::Font* mp_font;
	Gdiplus::Bitmap* mp_bitmap;
	Gdiplus::Graphics* mp_graphic;

	INT m_width;				// 출력 폭
	INT m_height;			// 출력 높이
	INT m_last_position_x;
	INT m_last_position_y;
	Gdiplus::Color m_temp_color;					// 색상 변경을 위한 임시 객체

	static ULONG_PTR m_token;				// GDI+ 라이브러리 사용 정보
	static INT m_object_count;					// DCP 객체 갯수 계산

public:
	explicit DCP();
	explicit DCP(INT a_width, INT a_height);
	virtual ~DCP();

	void Init();
	void CreateDCP(INT a_width, INT a_height);

	// 사각형
	void Rectangle(INT a_sx, INT a_sy, INT a_ex, INT a_ey);
	void Rectangle(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_pen_color, Gdiplus::ARGB a_fill_color);
	void FillSolidRect(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color);
	void FillSolidRect(INT a_sx, INT a_sy, INT a_ex, INT a_ey);
	void DrawRect(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color);
	void DrawRect(INT a_sx, INT a_sy, INT a_ex, INT a_ey);

	// 타원
	void Ellipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey);
	void FillSolidEllipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color);
	void FillSolidEllipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey);
	void DrawEllipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color);
	void DrawEllipse(INT a_sx, INT a_sy, INT a_ex, INT a_ey);

	// 선그리기
	void DrawLine(INT a_sx, INT a_sy, INT a_ex, INT a_ey, Gdiplus::ARGB a_color);
	void DrawLine(INT a_sx, INT a_sy, INT a_ex, INT a_ey);
	void MoveTo(INT a_x, INT a_y);
	void LineTo(INT a_x, INT a_y);

	// 브러시 색상 변경
	void SetDCBrushColor(Gdiplus::ARGB a_color);
	// 펜 색상 변경
	void SetDCPenColor(Gdiplus::ARGB a_color);
	// 펜 변경 (스타일, 굵기, 색상)
	void SetDCPenColor(Gdiplus::DashStyle a_style, Gdiplus::REAL a_width, Gdiplus::ARGB a_color);
	// 글꼴 색상 변경
	void SetTextColor(Gdiplus::ARGB a_color);
	// 폰트 객체 재설정 , 이전 폰트 객체의 주소를 반환함
	Gdiplus::Font* SelectObject(Gdiplus::Font* ap_font);
	void SelectObject(const TCHAR* ap_style, INT a_size);

	// 텍스트 출력 (색상부여)
	void GpTextOut(INT a_x, INT a_y, Gdiplus::ARGB a_color, const TCHAR* ap_str, INT a_str_len);
	// 텍스트 출력 (기존색상)
	void GpTextOut(INT a_x, INT a_y, const TCHAR* ap_str, INT a_str_len);

	// 이미지 객체 출력
	void Draw(Gdiplus::Image* ap_image, INT a_x, INT a_y);

	// 경로를 받아 해당 이미지 출력 (원본 크기)
	void Draw(TCHAR* a_file_path, INT a_x, INT a_y);
	// 경로를 받아 원하는 크기로 이미지 출력
	void Draw(TCHAR* a_file_path, INT a_x, INT a_y, INT a_width, INT a_height);

	// DC에 현재 이미지 출력
	void Draw(HDC ah_dc, INT a_x = 0, INT a_y = 0);

	// Get
	Gdiplus::Image* GetImage();
	Gdiplus::Graphics* GetGraphics();

	// Get함수들을 편하게 사용할 수 있도록 연산자 오버로딩
	operator Gdiplus::Image* ();
	operator Gdiplus::Graphics* ();

	// 전체 영역 색상 채우기
	void Clear(Gdiplus::ARGB a_color);
	void Clear();

	// 다각형 그리기 (채우기)
	void FillPolygon(Gdiplus::Point* ap_position_list, INT a_count);

	// 다각형 그리기 (테두리)
	void DrawPolygon(Gdiplus::Point* ap_position_list, INT a_count);

	// Arc 그리기 (테두리)
	void DrawArc(Gdiplus::REAL a_x, Gdiplus::REAL a_y, Gdiplus::REAL a_cx, Gdiplus::REAL a_cy, Gdiplus::REAL a_start_angle, Gdiplus::REAL a_sweep_angle);
};

#endif