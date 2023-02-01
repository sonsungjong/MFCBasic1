#pragma once

class TW_Button : public CButton
{
	DECLARE_DYNAMIC(TW_Button)
private:
	COLORREF m_btn_color;						// ��ư ����
	COLORREF m_border_color;				// ��ư �׵θ���
	COLORREF m_focus_btn_color;				// ��Ŀ���� ��ư�� ����
	COLORREF m_focus_border_color;				// ��Ŀ���� ��ư�� �׵θ���
	COLORREF m_in_border_color;					// ��ư ������� �׵θ���
	COLORREF m_text_color;							// ��ư ���ڻ�

public:
	TW_Button();
	virtual ~TW_Button();

	// ��ư ������ �����ϴ� �Լ�
	void ChangeColor(COLORREF a_focus_btn_color, COLORREF a_focus_border_color, COLORREF a_btn_color, COLORREF a_border_color, COLORREF a_in_border_color, COLORREF a_text_color);

protected:
	DECLARE_MESSAGE_MAP()
public:
	// MFC �����Լ�
	virtual void DrawItem(LPDRAWITEMSTRUCT lpds);
};


