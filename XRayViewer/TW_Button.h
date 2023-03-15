#pragma once

class TW_Button : public CButton
{
	DECLARE_DYNAMIC(TW_Button)
private:
	COLORREF m_btn_color;						// 버튼 배경색
	COLORREF m_border_color;				// 버튼 테두리색
	COLORREF m_focus_btn_color;				// 포커스된 버튼의 배경색
	COLORREF m_focus_border_color;				// 포커스된 버튼의 테두리색
	COLORREF m_in_border_color;					// 버튼 내부장식 테두리색
	COLORREF m_text_color;							// 버튼 글자색

public:
	TW_Button();
	virtual ~TW_Button();

	// 버튼 색상을 변경하는 함수
	void ChangeColor(COLORREF a_focus_btn_color, COLORREF a_focus_border_color, COLORREF a_btn_color, COLORREF a_border_color, COLORREF a_in_border_color, COLORREF a_text_color);

protected:
	DECLARE_MESSAGE_MAP()
public:
	// MFC 가상함수
	virtual void DrawItem(LPDRAWITEMSTRUCT lpds);
};


