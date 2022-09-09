#pragma once


// SJ_Edit

class SJ_Edit : public CEdit
{
	DECLARE_DYNAMIC(SJ_Edit)
private:
	HBRUSH mh_edit_bk_brush;
	COLORREF m_edit_focus_text_color;			// 변경 글자색
	COLORREF m_edit_text_color;		// 일반 글자색
	COLORREF m_edit_bk_color;						// 배경색

public:
	SJ_Edit();
	virtual ~SJ_Edit();
	void ChangeColor(COLORREF a_edit_bk_color, COLORREF a_edit_text_color, COLORREF a_edit_focus_text_color);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnEnKillfocus();
};


