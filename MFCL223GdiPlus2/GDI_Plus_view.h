#pragma once
#include <gdiplus.h>
using namespace Gdiplus;

// GDI_Plus_view
#define MAX_GDI_PLUS_COUNT				200

struct CircleDataPlus
{
	int x;
	int y;
	int radius;
	BYTE a, r, g, b;			// 색상
};

class GDI_Plus_view : public CWnd
{
private:
	CircleDataPlus m_list[MAX_GDI_PLUS_COUNT];			// 타원 정보
	CRect m_rect;					// 작업 영역
	ULONG_PTR m_token;				// GDI+ 라이브러리 해제용

	SolidBrush* mp_brush;				// GDI+ 브러시
	Bitmap* mp_mem_image;					// GDI+ 출력을 잠시 저장할 비트맵 객체
	Graphics* mp_mem_graphic;					// 비트맵 객체로 그림을 그리는 출력 객체

	DECLARE_DYNAMIC(GDI_Plus_view)
public:
	GDI_Plus_view();
	virtual ~GDI_Plus_view();

	void NormalDraw(CDC* ap_dc);					// GDI+ 일반 출력
	void ImageDraw(CDC* ap_dc);					// GDI+ 이미지 출력
	void ChangeRate(BYTE a_rate);					// 투명도 변경

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


