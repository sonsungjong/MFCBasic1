#pragma once


// BinDataView
#define ITEM_HEIGHT 22

class BinDataView : public CWnd
{
	DECLARE_DYNAMIC(BinDataView)
private:
	// 깜빡임 제거
	CImage m_draw_image;
	CDC m_draw_dc;

	// GetClientRect() 좌표
	CRect m_view_rect;

	// 다이얼로그에서 사용할 폰트
	CFont m_font;
	CBrush m_bk_brush;
	CPen m_bk_pen, m_grid_pen;

	int m_view_cx;					// 가로 길이
	int m_view_cy;					// 세로 길이
	int m_item_view_count;				// 한 화면에 보여줄 행 갯수
	int m_data_count_per_line = 24;					// 한 행에 기록할 데이터 갯수
	TCHAR m_temp_string[1024];					// 정수값을 문자열로 바꿔서 출력하고자함

	int m_bin_data_size = 0;				// 파일 크기
	int m_line_count = 0;						// 총 라인 수
	int m_last_count = 0;						// 마지막 줄은 24개가 안될 수 있기 때문에 마지막 줄의 데이터 갯수를 카운팅
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


