#pragma once


// DrawWnd

class DrawWnd : public CWnd
{
	DECLARE_DYNAMIC(DrawWnd)
public:
	DrawWnd();
	virtual ~DrawWnd();

protected:
	DECLARE_MESSAGE_MAP()
	char m_is_clicked = 0;
	CPoint m_prev_point;
	CImage m_image;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
};


