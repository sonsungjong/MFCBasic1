// 자식 Inner 윈도우 생성 코드

#ifndef LADDER_WND_H_
#define LADDER_WND_H_

class LadderWnd : public CWnd
{
	DECLARE_DYNAMIC(LadderWnd)
protected:
	CImage m_draw_image;
	HDC mh_draw_dc;
	CRect m_rect;

public:
	explicit LadderWnd();						// 생성자
	virtual ~LadderWnd();			// 파괴자

	void MyDraw();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
};

#endif