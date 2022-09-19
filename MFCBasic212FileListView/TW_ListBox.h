#pragma once

class TW_ListBox : public CListBox
{
	DECLARE_DYNAMIC(TW_ListBox)
protected:
	CBrush m_list_box_bk_brush;
	COLORREF m_select_color, m_focus_color, m_bk_color;

public:
	TW_ListBox();
	virtual ~TW_ListBox();

	void SetItemColor(COLORREF a_select_color, COLORREF a_focus_color, COLORREF a_bk_color);
	virtual void DrawListItem(CDC *ap_dc, RECT *ap_rect, int a_index, void *ap_data, unsigned char a_select_flag, unsigned char a_focus_flag);
	virtual void DrawUserItem(CDC *ap_dc, RECT *ap_rect, int a_index, void *ap_data, unsigned char a_select_flag, unsigned char a_focus_flag);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
};


