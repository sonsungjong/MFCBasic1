// DrawWnd.cpp : implementation file
//

#include "pch.h"
#include "MFCL116Pen.h"
#include "DrawWnd.h"


// DrawWnd

IMPLEMENT_DYNAMIC(DrawWnd, CWnd)

DrawWnd::DrawWnd()
{

}

DrawWnd::~DrawWnd()
{
}


BEGIN_MESSAGE_MAP(DrawWnd, CWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// DrawWnd message handlers



void DrawWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_is_clicked = 1;
	m_prev_point = point;
	
	// 마우스 벗어나도 사용
	SetCapture();
	CWnd::OnLButtonDown(nFlags, point);
}


void DrawWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_is_clicked = 0;

	ReleaseCapture();
	CWnd::OnLButtonUp(nFlags, point);
}


void DrawWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked) {
		CClientDC dc(this);

		HDC h_image_dc = m_image.GetDC();
		CDC* p_image_dc = CDC::FromHandle(h_image_dc);

		p_image_dc->MoveTo(m_prev_point);			// 시작점(이전점)
		p_image_dc->LineTo(point);			// 끝점

		m_image.ReleaseDC();

		m_image.Draw(dc, 0, 0);
		m_prev_point = point;

	}

	CWnd::OnMouseMove(nFlags, point);
}


int DrawWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CRect r;
	GetClientRect(r);

	m_image.Create(r.Width(), r.Height(), 32);

	CDC *p_image_dc = CDC::FromHandle(m_image.GetDC());
	p_image_dc->Rectangle(r);
	m_image.ReleaseDC();

	return 0;
}


void DrawWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CWnd::OnPaint() for painting messages
	m_image.Draw(dc, 0, 0);
}
