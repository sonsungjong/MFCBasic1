#ifndef MY_INNER_WND_H_
#define MY_INNER_WND_H_

class MyInnerWnd : public CWnd
{
	DECLARE_DYNAMIC(MyInnerWnd)
protected:
	CImage m_draw_image;				// �׸��� �׷��� �̹��� ��ü
	HDC mh_draw_dc;						// �޸�DC
	CRect m_rect;

public:
	explicit MyInnerWnd();				// ������
	virtual ~MyInnerWnd();				// �ı���

	void MyDraw();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
};

#endif