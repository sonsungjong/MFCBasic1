// �ڽ� Inner ������ ���� �ڵ�

#ifndef LADDER_WND_H_
#define LADDER_WND_H_

#define MEMBER_COUNT			5			// ��ٸ� ��

class LadderWnd : public CWnd
{
	DECLARE_DYNAMIC(LadderWnd)
protected:
	CImage m_draw_image;
	HDC mh_draw_dc;
	CRect m_rect;
	HFONT m_font;

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