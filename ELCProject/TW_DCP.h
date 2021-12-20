#ifndef _TW_DCP_H_
#define _TW_DCP_H_

// 이 클래스는 GDI+ 함수들을 편하게 사용할 수 있도록 만들었습니다.
// 이 클래스는 예제를 계속 만들어가면서 수정되거나 기능이 추가될수 있습니다.
// -------------------------------------------------------------------------
// 이 클래스를 처음 만든 사람의 노력을 존중하는 마음으로 저작권 표시를 유지해 주세요.
// 클래스 초기 모델 제작 : 김성엽(tipsware@naver.com)
// 클래스 배포 : https://cafe.naver.com/mythread
// 처음 만든 날짜 : 2020년 3월 24일 (화요일)
// 처음 마지막 업데이트 날짜 : 2020년 3월 25일 (수요일)

// 이 클래스의 기능이나 내용을 변경했다면 아래에 이력을 남겨주시면 됩니다.
// 클래스 내용 변경자 : 손성종
// 마지막 변경 날짜 :


#include <Gdiplus.h>       // GDI+를 사용하기 위한 헤더 파일
using namespace Gdiplus;   // Gdiplus:: 표현을 줄이기 위해

#define RGB24(r,g,b) (0xFF000000 | (r << 16) | (g << 8) | b)   // 0xFFRRGGBB
#define RGB32(a,r,g,b) ((a << 24) | (r << 16) | (g << 8) | b)  // 0xAARRGGBB

// DCP는 DC Plus의 의미, 이 클래스는 더블 버퍼링 개념을 항상 사용한다.
class TW_DCP
{
protected:
    Brush *mp_brush;  // 브러시 객체
    Brush *mp_font_brush;  // 글꼴 색상으로 사용할 브러시 객체
    Pen *mp_pen;  // 펜 객체
    Gdiplus::Font *mp_font;  // 폰트 객체
    Bitmap *mp_bitmap;  // 비트맵 객체
    Graphics *mp_graphic;  // 출력용 객체

    int m_cx, m_cy;  // 출력 영역의 크기 (폭과 높이)
    int m_last_pos_x, m_last_pos_y;  // Line을 연속을 그릴 때 사용
    Color m_temp_color;  // 색상을 변경할 때 임시로 사용할 객체

    static ULONG_PTR m_token;  // GDI+ 라이브러리 사용정보
    static int m_object_count;  // DCP 객체의 개수를 계산

public:
    TW_DCP();
    TW_DCP(int a_cx, int a_cy);
    virtual ~TW_DCP();

    void Init();  // 객체를 초기화할 때 사용하는 기본 함수
    void CreateDCP(int a_cx, int a_cy);   // 작업 영역을 지정해서 출력 객체를 생성하는 함수
    void Clear(ARGB a_color); // a_color로 전체 영역을 채운다.
    void Clear();  // 설정된 Brush 색상으로 전체 영역을 채운다.

    // 사각형을 그리는 함수들
    void Rectangle(int a_sx, int a_sy, int a_ex, int a_ey);  // 채우기와 테두리 같이 그림
    void FillSolidRect(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color);  // 채우기만 함
    void FillSolidRect(int a_sx, int a_sy, int a_ex, int a_ey);  // 채우기만 함
    void DrawRect(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color);  // 테두리만 그림
    void DrawRect(int a_sx, int a_sy, int a_ex, int a_ey); // 테두리만 그림

    // 타원을 그리는 함수들
    void Ellipse(int a_sx, int a_sy, int a_ex, int a_ey);  // 채우기와 테두리 같이 그림
    void FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color); // 채우기만 함
    void FillSolidEllipse(int a_sx, int a_sy, int a_ex, int a_ey); // 채우기만 함
    void DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color); // 테두리만 그림
    void DrawEllipse(int a_sx, int a_sy, int a_ex, int a_ey); // 테두리만 그림

    // 선을 그리는 함수들
    void DrawLine(int a_sx, int a_sy, int a_ex, int a_ey, ARGB a_color);  // 시작, 끝을 사용해서 선그리기
    void DrawLine(int a_sx, int a_sy, int a_ex, int a_ey);  // 시작, 끝을 사용해서 선그리기
    void MoveTo(int a_x, int a_y);  // 선의 시작 위치를 지정
    void LineTo(int a_x, int a_y);  // MoveTo 또는 마지막 LineTo를 사용한 지점과 선을 연결
    void DrawArc(REAL a_x, REAL a_y, REAL a_cx, REAL a_cy, REAL a_start_angle, REAL a_sweep_angle); // Arc의 테두리를 그리는 함수
    void FillPie(int a_x, int a_y, int a_cx, int a_cy, REAL a_start_angle, REAL a_sweep_angle); // Pie를 그리는 함수

    // 연속된 선을 그리는 함수
    void DrawLines(Gdiplus::Point *ap_pos_list, int a_count);

    // 다각형을 그리는 함수들
    void FillPolygon(Gdiplus::Point *ap_pos_list, int a_count); // 속이 채워지는 다각형을 그리는 함수
    void DrawPolygon(Gdiplus::Point *ap_pos_list, int a_count); // 다각형의 테두리를 그리는 함수

    void SetDCBrushColor(ARGB a_color);  // 채우기 색상을 변경
    void SetDCPenColor(ARGB a_color);  // 선 색상을 변경
    void SetDCPenColor(DashStyle a_style, REAL a_width, ARGB a_color);  // 선 스타일, 굵기 그리고 선 색상 변경
    void SetTextColor(ARGB a_color);  // 글꼴의 색상을 변경
    Gdiplus::Font *SelectObject(Gdiplus::Font *ap_font);  // 폰트 객체를 다시 설정한다.
    Gdiplus::Font *CreateFontObject(const wchar_t *ap_font_name, REAL a_font_size); // GDI+용 글꼴 객체를 생성하는 함수    
    void DestroyFont(Gdiplus::Font *ap_font); // 지정한 글꼴 객체를 제거하는 함수


    void Draw(Image *ap_image, int a_x, int a_y);  // 전달된 이미지 객체를 출력
    void Draw(HDC ah_dc, int a_x = 0, int a_y = 0);  // 전달된 DC에 현재 이미지를 출력

    // 문자열을 지정한 위치에 출력하는 함수들
    void TextOut(int a_x, int a_y, ARGB a_color, const wchar_t *ap_str, int a_str_len);
    void TextOut(int a_x, int a_y, const wchar_t *ap_str, int a_str_len);

    GraphicsPath *CreatePath(); // path 객체를 생성하는 함수
    void DestroyPath(GraphicsPath *ap_path); // path 객체를 제거하는 함수
    void DrawPath(GraphicsPath *ap_path);  // 여러가지 도형을 한 번에 연결해서 그림을 그리는 함수
    void FillPath(GraphicsPath *ap_path);  // 여러가지 도형을 한 번에 연결해서 그림을 그리는 함수
    void ShowPath(GraphicsPath *ap_path);  // 여러가지 도형을 한 번에 연결해서 그림을 그리는 함수


    // 내부 보호 멤버의 값을 외부에서 사용할 수 있게 해주는 함수들
    Image *GetImage() { return mp_bitmap; }
    Graphics *GetGraphics() { return mp_graphic; }

    // GetImage 함수와 GetGraphics 함수를 편하게 사용하도록 연산자 오버로딩 사용
    operator Image *() { return mp_bitmap; }
    operator Graphics *() { return mp_graphic; }
};

#endif