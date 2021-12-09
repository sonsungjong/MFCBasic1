#ifndef _HEADER_GRID_H_
#define _HEADER_GRID_H_
// HeaderGrid

#define MAX_HEADER_ITEM_COUNT			10

typedef struct HeaderItemData
{
	TCHAR m_item_name[32];
	short m_len;			// 2byte (30000)
	short width;			// �ִ�ũ��� �ּ�ũ�⿡ ���� ���� �����ϰ� �ؾ���
} HID;

class HeaderGrid : public CWnd
{
	DECLARE_DYNAMIC(HeaderGrid)
protected:
	CImage m_draw_image;							// ��� �׸��� ��Ʈ���� �׸� �̹�����ü(�����ӹ��� �޸�DC)
	HDC mh_draw_dc;									// �̹��� ��ü�� �׸��� �׸��� ����� DC�ڵ鰪
	CRect m_rect;										// ������ ����

	HID m_item_data[MAX_HEADER_ITEM_COUNT];
	int m_count = 0;
	HFONT mh_font;

	// ���콺 �÷���
	char m_is_clicked = 0;
	// ���õ� �׸��带 �����ϴ� �ε����÷���
	char m_select_grid_index = 0;

	POINT m_click_position;
	// ���� ������ ������ �ڵ鰪
	HWND mh_buddy_wnd = nullptr;
	HCURSOR mh_resize_we_cursor;

public:
	HeaderGrid();
	virtual ~HeaderGrid();

	// ��� �׸��忡 �׸��� �߰��ϴ� �Լ�
	void AddItemData(const TCHAR* ap_name, short a_width);
	// �׸��� �ٽ� �׸��� ����� �Լ�
	void RedrawItemData();
	// �̹��� ��ü�� ����׸������� ����ؼ� �׸��� �׸��� �Լ�
	void DrawHeaderItem();
	// ���� ������ ������ �ڵ鰪�� �����ϴ��Լ�
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