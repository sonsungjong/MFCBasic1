#include "pch.h"
#include "MFCL117PaintBrush.h"
#include "DrawWnd.h"

//DrawWnd
IMPLEMENT_DYNAMIC(DrawWnd, CWnd)

DrawWnd::DrawWnd()
{

}

DrawWnd::~DrawWnd()
{

}

BEGIN_MESSAGE_MAP(DrawWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



int DrawWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CRect r;
	GetClientRect(r);

	m_image.Create(r.Width(), r.Height(), 32);
	m_temp_image.Create(r.Width(), r.Height(), 32);

	CDC* p_image_dc = CDC::FromHandle(m_image.GetDC());
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


void DrawWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_is_clicked = 1;
	m_prev_point = point;

	SetCapture();

	CWnd::OnLButtonDown(nFlags, point);
}


void DrawWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked) {
		if (m_draw_type == LINE_MODE) {
			// 마우스를 떼는 순간 CImage에 그림을 그려 남김
			HDC h_image_dc = m_image.GetDC();
			CDC* p_image_dc = CDC::FromHandle(m_image.GetDC());
			
			p_image_dc->MoveTo(m_prev_point);
			p_image_dc->LineTo(point);
			m_image.ReleaseDC();
		}
		else if (m_draw_type == RECT_MODE) {
			HDC h_image_dc = m_image.GetDC();
			CDC* p_image_dc = CDC::FromHandle(m_image.GetDC());

			// 테두리만 있는 사각형
			CGdiObject* p_old_brush = p_image_dc->SelectStockObject(NULL_BRUSH);
			p_image_dc->Rectangle(m_prev_point.x, m_prev_point.y, point.x, point.y);
			p_image_dc->SelectObject(p_old_brush);
		}
		m_is_clicked = 0;

		ReleaseCapture();
	}


	CWnd::OnLButtonUp(nFlags, point);
}


void DrawWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked) {
		CClientDC dc(this);

		if (m_draw_type == PEN_MODE) {
			HDC h_image_dc = m_image.GetDC();
			CDC* p_image_dc = CDC::FromHandle(h_image_dc);
			p_image_dc->MoveTo(m_prev_point);			// 이전점(시작)
			p_image_dc->LineTo(point);				// 현재점(끝)
			m_prev_point = point;
			m_image.ReleaseDC();
			m_image.Draw(dc, 0, 0);
		}
		else if (m_draw_type == LINE_MODE) {
			CDC* p_temp_dc = CDC::FromHandle(m_temp_image.GetDC());
			m_image.Draw(dc, 0, 0);				// 그림을 계속 덮어씀

			p_temp_dc->MoveTo(m_prev_point);			// 바로 그려서 이미지에 남아있지않게함
			p_temp_dc->LineTo(point);
			m_temp_image.ReleaseDC();
			m_temp_image.Draw(dc, 0, 0);
		}
		else if (m_draw_type == RECT_MODE) {
			CDC* p_temp_dc = CDC::FromHandle(m_temp_image.GetDC());

			m_image.Draw(*p_temp_dc, 0, 0);
			// 테두리만 있는 사각형
			CGdiObject* p_old_brush = p_temp_dc->SelectStockObject(NULL_BRUSH);
			p_temp_dc->Rectangle(m_prev_point.x, m_prev_point.y, point.x, point.y);
			p_temp_dc->SelectObject(p_old_brush);

			m_temp_image.ReleaseDC();
			m_temp_image.Draw(dc, 0, 0);
		}


	}

	CWnd::OnMouseMove(nFlags, point);
}
