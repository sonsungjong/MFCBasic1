#pragma once
#include <gdiplus.h>
using namespace Gdiplus;

// LineGraph
typedef struct BlogInquiryData
{
	char data[12];				// 날짜
	char data_of_week[3];			// 요일
	int total;							// 전체
	int neighbor;							// 피이웃
	int adjoin;								// 서로이웃
	int etc;									// 기타
} BID;

class LineGraph : public CWnd
{
	DECLARE_DYNAMIC(LineGraph)
	// GDI
	CImage m_draw_image;
	CDC m_draw_dc;

	// GDI+
	ULONG_PTR m_token;
	SolidBrush* mp_brush;
	Pen* mp_pen;
	Bitmap* mp_mem_image;						// Bitmap에 그림을 그린다
	Graphics* mp_mem_graphic;

	// 그래프 좌표
	CRect m_rect;
	CPtrList m_data_list;


public:
	LineGraph();
	virtual ~LineGraph();
	void CreateGraph(int a_rect_id, CWnd* ap_parent, int a_ctrl_id);
	void LoadData(const TCHAR* ap_data_path);
	void DrawGraph();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
};


