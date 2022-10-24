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
	BYTE a, r, g, b;			// ����
};

class GDI_Plus_view : public CWnd
{
private:
	CircleDataPlus m_list[MAX_GDI_PLUS_COUNT];			// Ÿ�� ����
	CRect m_rect;					// �۾� ����
	ULONG_PTR m_token;				// GDI+ ���̺귯�� ������

	SolidBrush* mp_brush;				// GDI+ �귯��
	Bitmap* mp_mem_image;					// GDI+ ����� ��� ������ ��Ʈ�� ��ü
	Graphics* mp_mem_graphic;					// ��Ʈ�� ��ü�� �׸��� �׸��� ��� ��ü

	DECLARE_DYNAMIC(GDI_Plus_view)
public:
	GDI_Plus_view();
	virtual ~GDI_Plus_view();

	void NormalDraw(CDC* ap_dc);					// GDI+ �Ϲ� ���
	void ImageDraw(CDC* ap_dc);					// GDI+ �̹��� ���
	void ChangeRate(BYTE a_rate);					// ���� ����

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


