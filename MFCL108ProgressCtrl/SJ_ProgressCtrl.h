#pragma once


// 메모리DC 클래스
class SJ_MemDC
{
protected:
	CDC m_memDC;
	CBitmap m_memBmp;
	int m_width;
	int m_height;

public:
	SJ_MemDC()
	{
		m_width = 0;
		m_height = 0;
	}
	~SJ_MemDC()
	{
		if (m_memDC.m_hDC != NULL) {
			m_memBmp.DeleteObject();
			m_memDC.DeleteDC();
		}
	}

	void _CreateDC(CWnd* ap_wnd, int a_width, int a_height) {
		CClientDC dc(ap_wnd);
		m_width = a_width;
		m_height = a_height;
		m_memDC.CreateCompatibleDC(&dc);
		m_memBmp.CreateCompatibleBitmap(&dc, a_width, a_height);
		m_memDC.SelectObject(&m_memBmp);
	}
	void Resize(CWnd* ap_wnd, int a_width, int a_height)
	{
		m_memBmp.DeleteObject();
		m_width = a_width;
		m_height = a_height;
		CClientDC dc(ap_wnd);
		m_memBmp.CreateCompatibleBitmap(&dc, m_width, m_height);
		m_memDC.SelectObject(&m_memBmp);
	}

	inline CDC* GetDC()			// 자주쓰니깐 inline써서 스택프레임 없애기
	{
		return &m_memDC;
	}
	inline int GetWidth()
	{
		return m_width;
	}
	inline int GetHeight()
	{
		return m_height;
	}

	void Draw(CDC* ap_dc, int a_x, int a_y)
	{
		ap_dc->BitBlt(0, 0, m_width, m_height, &m_memDC, 0, 0, SRCCOPY);
	}
};

// Progress컨트롤 Wnd클래스
class SJ_ProgressCtrl : public CWnd
{
	DECLARE_DYNAMIC(SJ_ProgressCtrl)

public:
	SJ_ProgressCtrl();
	virtual ~SJ_ProgressCtrl();

	void CreateProgress(CWnd* ap_parent, CRect a_rect, int a_ctrl_id);
	void CreateProgress(CWnd* ap_parent, int a_guide_ctrl_id, int a_ctrl_id);
	
	void SetRange(int a_min, int a_max);
	void SetPos(int a_pos);
	inline void UpdatePos(int a_pos)
	{
		SetPos(a_pos);
		Invalidate(0);
	}
	int GetPos();

	void SetColor(COLORREF a_bk_color, COLORREF a_fore_color);

protected:
	DECLARE_MESSAGE_MAP()

	int m_pos, m_min, m_max;
	int m_width, m_height;
	COLORREF m_bk_color, m_fore_color;
	SJ_MemDC m_mem_image;

public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


