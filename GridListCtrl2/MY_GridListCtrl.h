#pragma once


// MY_GridListCtrl

class MY_GridListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(MY_GridListCtrl)

public:
	MY_GridListCtrl();
	virtual ~MY_GridListCtrl();

	void SetGridLine();
	void SetGridLine2();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	HFONT m_font;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	void MyDraw(LPDRAWITEMSTRUCT lpDrawItemStruct);
	
};


