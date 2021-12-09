#ifndef _HEADER_GRID_H_
#define _HEADER_GRID_H_
// HeaderGrid

#define MAX_HEADER_ITEM_COUNT			10

typedef struct HeaderItemData
{
	TCHAR m_item_name[32];
	short m_len;			// 2byte (30000)
	short width;			// 최대크기와 최소크기에 대한 값을 설정하게 해야함
} HID;

class HeaderGrid : public CWnd
{
	DECLARE_DYNAMIC(HeaderGrid)
protected:
	CImage m_draw_image;							// 헤더 그리그 컨트롤을 그릴 이미지객체(깜빡임방지 메모리DC)
	HDC mh_draw_dc;									// 이미지 객체에 그림을 그릴때 사용할 DC핸들값
	CRect m_rect;										// 윈도우 영역

	HID m_item_data[MAX_HEADER_ITEM_COUNT];
	int m_count = 0;
	HFONT mh_font;

	// 마우스 플래그
	char m_is_clicked = 0;
	// 선택된 그리드를 구분하는 인덱스플래그
	char m_select_grid_index = 0;

	POINT m_click_position;
	// 같이 연동할 윈도우 핸들값
	HWND mh_buddy_wnd = nullptr;
	HCURSOR mh_resize_we_cursor;

public:
	HeaderGrid();
	virtual ~HeaderGrid();

	// 헤더 그리드에 항목을 추가하는 함수
	void AddItemData(const TCHAR* ap_name, short a_width);
	// 항목을 다시 그릴때 사용할 함수
	void RedrawItemData();
	// 이미지 객체에 헤더항목정보를 사용해서 그림은 그리는 함수
	void DrawHeaderItem();
	// 같이 연동할 윈도우 핸들값을 설정하는함수
	void SetBuddyWnd(HWND ah_wnd)
	{
		mh_buddy_wnd = ah_wnd;
		if (mh_buddy_wnd && ::IsWindow(mh_buddy_wnd)) {
			::PostMessage(mh_buddy_wnd, 44001, m_count, (LPARAM)m_item_data);
		}
	}
	int CheckGridLine(CPoint point);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#endif