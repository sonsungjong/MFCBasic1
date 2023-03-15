#pragma once

// 상속용 리스트박스
class TW_ListBox : public CListBox
{
	DECLARE_DYNAMIC(TW_ListBox)
protected:
	CBrush m_list_box_bk_brush;
	COLORREF m_select_color;
	COLORREF m_focus_color;
	COLORREF m_bk_color;

public:
	TW_ListBox();
	virtual ~TW_ListBox();

	void SetItemColor(COLORREF a_select_color, COLORREF a_focus_color, COLORREF a_bk_color);
	virtual void DrawListItem(CDC* ap_dc, RECT* ap_rect, int a_index, void* ap_data, unsigned char a_select_flag, unsigned char a_focus_flag);
	virtual void DrawUserItem(CDC* ap_dc, RECT* ap_rect, int a_index, void* ap_data, unsigned char a_select_flag, unsigned char a_focus_flag);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void DrawItem(LPDRAWITEMSTRUCT lpds);			// =WM_DRAWITEM
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);				// =WM_CTLCOLOR
};


