// GDI_View.cpp : implementation file
//

#include "pch.h"
#include "MFCL223GdiPlus2.h"
#include "GDI_View.h"


// GDI_View

IMPLEMENT_DYNAMIC(GDI_View, CWnd)

GDI_View::GDI_View()
{

}

GDI_View::~GDI_View()
{
}


BEGIN_MESSAGE_MAP(GDI_View, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// GDI_View message handlers




void GDI_View::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CWnd::OnPaint() for painting messages
	dc.SelectStockObject(DC_BRUSH);
	dc.SetDCBrushColor(RGB(255, 255, 255));
	dc.Rectangle(m_rect);

	dc.SelectStockObject(NULL_PEN);

	CircleData* p = m_list;
	for (int i = 0; i < MAX_GDI_COUNT; i++, p++) {
		dc.SetDCBrushColor(p->color);
		dc.Ellipse(p->x - p->r, p->y - p->r, p->x + p->r, p->y + p->r);
	}
}


int GDI_View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1){
		return -1;
	}
	// TODO:  Add your specialized creation code here
	GetClientRect(m_rect);				// 작업 영역 지정
	int w = m_rect.Width();
	int h = m_rect.Height();
	srand((unsigned int)time(NULL));			// 난수 발생을 위해 기준값을 현재시간으로

	CircleData* p = m_list;				// m_list 배열의 첫 항목을 가리킨다.
	for (int i = 0; i < MAX_GDI_COUNT; i++, p++) {
		p->x = rand() % w;
		p->y = rand() % h;
		p->r = rand() % 40 + 10;
		p->color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}

	SetTimer(1, 10, NULL);				// 1번 타이머를 0.01초 단위로 WM_TIMER발생
	return 0;
}


void GDI_View::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);				// 1번 타이머 중지
}


void GDI_View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		int w = m_rect.Width();
		int h = m_rect.Height();

		CircleData* p = m_list;
		for (int i = 0; i < MAX_GDI_COUNT; i++, p++) {
			p->r--;
			if (p->r == 0) {
				p->x = rand() % w;
				p->y = rand() % h;
				p->r = rand() % 40 + 10;
				p->color = RGB(rand() % 256, rand() % 256, rand() % 256);
			}
		}
		Invalidate(FALSE);
	}
	else {
		CWnd::OnTimer(nIDEvent);
	}
}
