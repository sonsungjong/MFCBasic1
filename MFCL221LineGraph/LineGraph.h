#pragma once
#include <gdiplus.h>
using namespace Gdiplus;

// LineGraph
typedef struct BlogInquiryData
{
	char data[12];				// ��¥
	char data_of_week[3];			// ����
	int total;							// ��ü
	int neighbor;							// ���̿�
	int adjoin;								// �����̿�
	int etc;									// ��Ÿ
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
	Bitmap* mp_mem_image;						// Bitmap�� �׸��� �׸���
	Graphics* mp_mem_graphic;

	// �׷��� ��ǥ
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


