#ifndef MY_INNER_WND_H_
#define MY_INNER_WND_H_

class MyInnerWnd : public CWnd
{
	DECLARE_DYNAMIC(MyInnerWnd)
protected:
	CImage m_draw_image;				// 그림이 그려질 이미지 객체
	HDC mh_draw_dc;						// 메모리DC
	CRect m_rect;

public:
	explicit MyInnerWnd();				// 생성자
	virtual ~MyInnerWnd();				// 파괴자

	void MyDraw();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
};

#endif