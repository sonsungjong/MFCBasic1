#pragma once


// GDI_View
#define MAX_GDI_COUNT			200

struct CircleData {
	int x;
	int y;
	int r;
	COLORREF color;
};

class GDI_View : public CWnd
{
	DECLARE_DYNAMIC(GDI_View)
private:
	CircleData m_list[MAX_GDI_COUNT];
	CRect m_rect;

public:
	GDI_View();
	virtual ~GDI_View();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


