// �ڽ� Inner ������ ���� �ڵ�

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
	explicit LadderWnd();						// ������
	virtual ~LadderWnd();			// �ı���

	void MyDraw();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
};

#endif