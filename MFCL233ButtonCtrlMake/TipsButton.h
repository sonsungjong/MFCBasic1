#pragma once

// ���� ������ ��ư

// ��ư�� Ŭ���Ǿ��� �� �߻��ϴ� �޽��� (LM_BTN_CLICKED == 28001)
#define LM_BTN_CLICKED				28001

// MFCŬ����
class TipsButton : public CWnd
{
	DECLARE_DYNAMIC(TipsButton)
protected:
	HDC mh_mem_dc;					// ��ư ��½� ����� �޸�DC
	HBITMAP mh_mem_bmp;				// �޸� DC�� �׸� ��Ʈ��
	HFONT mh_font;						// �޸� DC�� ����� ��Ʈ
	CRect m_rect;							// ��ư�� ����
	CString m_title_str;						// ��ư�� ����� ���ڿ�

	// ��Ŀ���� ��ư��, ��Ŀ���� �׵θ���, �Ϲ� ��ư��, �Ϲ� �׵θ���
	COLORREF m_focus_btn_color;
	COLORREF m_focus_border_color;
	COLORREF m_btn_color;
	COLORREF m_border_color;

	// ��ư ���� �׵θ���, ��ư �ؽ�Ʈ ����
	COLORREF m_in_border_color;
	COLORREF m_text_color;

	// ��ư�� ������ ���¸� ����� ������ ���콺 Ŭ�� ���¸� ����� ����
	char m_push_flag;
	char m_is_clicked;

public:
	TipsButton();
	virtual ~TipsButton();

	// ���̵� ��Ʈ���� ����ؼ� ��ư ����
	int CreateButton(CWnd* ap_parent, const TCHAR* ap_title, int a_ctrl_id, int a_guide_rect);
	// ���� ��ǥ�� �����ؼ� ��ư ����
	int CreateButton(CWnd* ap_parent, const TCHAR* ap_title, int a_ctrl_id, CRect a_rect);
	// ��ư�� �޸�DC�� �׸�
	void DrawButtonImage(char a_push_flag = 0);
	void ChangeColor(COLORREF a_focus_btn_color, COLORREF a_focus_border_color, COLORREF a_btn_color, COLORREF a_border_color, COLORREF a_in_border_color, COLORREF a_text_color);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


