#pragma once
class UserProgress
{
public:
	UserProgress();
	~UserProgress();
	void Create(CWnd* ap_parent, int a_guide_ctrl);
	void Create(CRect a_rect);
	CRect GetRect();
	void Update(CWnd* ap_parent);
	void SetRange(int a_min, int a_max);
	void SetPos(int a_pos);
	int GetPos();
	void SetColor(COLORREF a_bk_color, COLORREF a_fore_color);
	void Draw(CDC* ap_dc);

protected:
	int m_pos, m_min, m_max;
	COLORREF m_bk_color, m_fore_color;
	CRect m_rect;
};

