#pragma once


// TW_ListBox

class TW_ListBox : public CListBox
{
	DECLARE_DYNAMIC(TW_ListBox)
protected:
	// 배경색
	HBRUSH mh_list_bk_brush;
	// 상황별 브러시색
	COLORREF m_select_brush_color;
	COLORREF m_focus_brush_color;
	COLORREF m_bk_brush_color;
	// 상황별 펜색
	COLORREF m_select_pen_color;
	COLORREF m_focus_pen_color;
	COLORREF m_bk_pen_color;
	// 현재 처리 중인 Owner-Draw 정보
	LPDRAWITEMSTRUCT mp_last_lpds;
	// 리스트박스 더블 클릭시 그 좌표
	CPoint m_last_dblclk_pos;

public:
	TW_ListBox();
	virtual ~TW_ListBox();

	// WM_CREATE 없이 리스트 박스가 생성될때 작업
	virtual void CreateUserObject() {}
	virtual void DeleteUserObject() {}
	virtual void BaseDraw(HDC ah_dc, RECT* ap_rect);
	virtual void UserDraw(HDC ah_dc, RECT* ap_rect, void* ap_data) {}
	void UpdateItemInfo(int a_index, int a_count);
	virtual void ProcessDoubleClicked(int a_index) {}


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	afx_msg void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLbnDblclk();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual void PreSubclassWindow();
};


