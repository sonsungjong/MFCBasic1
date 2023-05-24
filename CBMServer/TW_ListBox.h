#pragma once


// TW_ListBox

class TW_ListBox : public CListBox
{
	DECLARE_DYNAMIC(TW_ListBox)
protected:
	// ����
	HBRUSH mh_list_bk_brush;
	// ��Ȳ�� �귯�û�
	COLORREF m_select_brush_color;
	COLORREF m_focus_brush_color;
	COLORREF m_bk_brush_color;
	// ��Ȳ�� ���
	COLORREF m_select_pen_color;
	COLORREF m_focus_pen_color;
	COLORREF m_bk_pen_color;
	// ���� ó�� ���� Owner-Draw ����
	LPDRAWITEMSTRUCT mp_last_lpds;
	// ����Ʈ�ڽ� ���� Ŭ���� �� ��ǥ
	CPoint m_last_dblclk_pos;

public:
	TW_ListBox();
	virtual ~TW_ListBox();

	// WM_CREATE ���� ����Ʈ �ڽ��� �����ɶ� �۾�
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


