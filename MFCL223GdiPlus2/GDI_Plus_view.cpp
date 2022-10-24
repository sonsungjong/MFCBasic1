// GDI_Plus_view.cpp : implementation file
//

#include "pch.h"
#include "MFCL223GdiPlus2.h"
#include "GDI_Plus_view.h"


// GDI_Plus_view

IMPLEMENT_DYNAMIC(GDI_Plus_view, CWnd)

GDI_Plus_view::GDI_Plus_view()
{

}

GDI_Plus_view::~GDI_Plus_view()
{
}




BEGIN_MESSAGE_MAP(GDI_Plus_view, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// GDI_Plus_view message handlers




void GDI_Plus_view::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CWnd::OnPaint() for painting messages
	// NormalDraw(&dc);						// GDI+ 일반 출력
	ImageDraw(&dc);					// 이미지에 GDI+ 출력
}


int GDI_Plus_view::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1){
		return -1;
	}
	// TODO:  Add your specialized creation code here
	GdiplusStartupInput gpsi;
	if (GdiplusStartup(&m_token, &gpsi, NULL) != Ok) {
		return 0;
	}
	GetClientRect(m_rect);

	int w = m_rect.Width();
	int h = m_rect.Height();
	srand((unsigned int)time(NULL));

	// MemDC 연결, mp_mem_graphic으로 그리면 됨
	mp_mem_image = new Bitmap(w, h);
	mp_mem_graphic = new Graphics(mp_mem_image);				// dc를 넣으면 dc에 그려지고, image에 넣으면 image에 그려짐
	
	mp_brush = new SolidBrush(Color(255, 255, 255, 255));
	mp_mem_graphic->SetSmoothingMode(SmoothingModeAntiAlias);

	CircleDataPlus* p = m_list;
	for (int i = 0; i < MAX_GDI_PLUS_COUNT; i++, p++) {
		p->x = rand() % w;
		p->y = rand() % h;
		p->radius = rand() % 40 + 10;
		p->a = 255;
		p->r = rand() % 256;
		p->g = rand() % 256;
		p->b = rand() % 256;
	}

	SetTimer(1, 10, NULL);
	return 0;
}


void GDI_Plus_view::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);

	delete mp_mem_graphic;
	delete mp_mem_image;
	delete mp_brush;

	GdiplusShutdown(m_token);				// GDI+ 종료
}


void GDI_Plus_view::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		int w = m_rect.Width();
		int h = m_rect.Height();

		CircleDataPlus* p = m_list;
		for (int i = 0; i < MAX_GDI_PLUS_COUNT; i++, p++) {
			p->radius--;
			if (p->radius == 0) {
				p->x = rand() % w;
				p->y = rand() % h;
				p->radius = rand() % 40 + 10;
				p->r = rand() % 256;
				p->g = rand() % 256;
				p->b = rand() % 256;
			}
		}
		Invalidate(FALSE);
	}
	else {
		CWnd::OnTimer(nIDEvent);
	}
}

void GDI_Plus_view::NormalDraw(CDC* ap_dc)
{
	// DC로 GDI+ 사용
	Graphics* p_graphic = new Graphics(ap_dc->m_hDC);
	p_graphic->SetSmoothingMode(SmoothingModeAntiAlias);

	mp_brush->SetColor(Color(255, 255, 255, 255));
	p_graphic->FillRectangle(mp_brush, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);

	CircleDataPlus* p = m_list;
	for (int i = 0; i < MAX_GDI_PLUS_COUNT; i++) {
		mp_brush->SetColor(Color(p->a, p->r, p->g, p->b));
		p_graphic->FillEllipse(mp_brush, p->x - p->radius, p->y - p->radius,
			p->radius * 2, p->radius * 2);
		p++;				// 다음 주소로 이동
	}
	delete p_graphic;
}

void GDI_Plus_view::ImageDraw(CDC* ap_dc)
{
	// memDC 적용
	Graphics* p_graphic = new Graphics(ap_dc->m_hDC);			// **이걸로 안그림
	mp_brush->SetColor(Color(255, 255, 255, 255));
	mp_mem_graphic->FillRectangle(mp_brush, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);

	CircleDataPlus* p = m_list;
	for (int i = 0; i < MAX_GDI_PLUS_COUNT; i++, p++) {
		mp_brush->SetColor(Color(p->a, p->r, p->g, p->b));
		mp_mem_graphic->FillEllipse(mp_brush, p->x - p->radius, p->y - p->radius,
			p->radius * 2, p->radius * 2);
	}
	p_graphic->DrawImage(mp_mem_image, 0, 0);			// 마지막에 해당 이미지를 출력
	delete p_graphic;
}

void GDI_Plus_view::ChangeRate(BYTE a_rate)
{
	for (int i = 0; i < MAX_GDI_PLUS_COUNT; i++) {
		m_list[i].a = a_rate;
	}
}