#pragma once


// SJ_Edit

class SJ_Edit : public CEdit
{
	DECLARE_DYNAMIC(SJ_Edit)
private:
	HBRUSH mh_edit_bk_brush;
	COLORREF m_edit_focus_text_color;			// ���� ���ڻ�
	COLORREF m_edit_text_color;		// �Ϲ� ���ڻ�
	COLORREF m_edit_bk_color;						// ����

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


