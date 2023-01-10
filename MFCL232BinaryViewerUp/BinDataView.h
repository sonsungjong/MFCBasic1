#pragma once


// BinDataView
#define ITEM_HEIGHT 22

class BinDataView : public CWnd
{
	DECLARE_DYNAMIC(BinDataView)
private:
	// ������ ����
	CImage m_draw_image;
	CDC m_draw_dc;

	// GetClientRect() ��ǥ
	CRect m_view_rect;

	// ���̾�α׿��� ����� ��Ʈ
	CFont m_font;
	CBrush m_bk_brush;
	CPen m_bk_pen, m_grid_pen;

	int m_view_cx;					// ���� ����
	int m_view_cy;					// ���� ����
	int m_item_view_count;				// �� ȭ�鿡 ������ �� ����
	int m_data_count_per_line = 24;					// �� �࿡ ����� ������ ����
	TCHAR m_temp_string[1024];					// �������� ���ڿ��� �ٲ㼭 ����ϰ�����

	int m_bin_data_size = 0;				// ���� ũ��
	int m_line_count = 0;						// �� ���� ��
	int m_last_count = 0;						// ������ ���� 24���� �ȵ� �� �ֱ� ������ ������ ���� ������ ������ ī����
	unsigned char* mp_bin_data = NULL;

public:
	BinDataView();
	virtual ~BinDataView();
	void DrawData();
	void ProcessScroll(UINT nSBCode, UINT nPos, int a_scroll_type);
	void ReDraw();
	void LoadFile(const TCHAR* ap_path);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};


