#pragma once


// MY_GridListCtrl

class MY_GridListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(MY_GridListCtrl)

public:
	MY_GridListCtrl();
	virtual ~MY_GridListCtrl();

	void SetGridLine();
protected:
	DECLARE_MESSAGE_MAP()

protected:
	HFONT m_font;
	LPDRAWITEMSTRUCT m_last_lpds;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};


