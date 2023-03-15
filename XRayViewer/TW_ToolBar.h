#pragma once

// Picture Control �Ӽ�
// Visible : False, 

// ���ٿ� ��밡���� �ִ� ��ư ��
#define MAX_BUTTON_COUNT				24

// ���� ��ư ����ü
struct TipsCommandData {
	TCHAR* p_name;			// �̸�
	int name_len;				// �̸� ���� (NULL ���� ����)
	int command_id;			// WM_COMMAND�� wParam ��
	int x;					// ���� ��ǥ
	int width;			// ��ư ����ũ��
	int bmp_up_id;				// ��ư �̹���
	int bmp_down_id;			// ��ư �̹���
	CBitmap* p_up_bitmap;				// ���ҽ��� �߰��� ��Ʈ���� �б�
	CBitmap* p_down_bitmap;			// ���ҽ��� �߰��� ��Ʈ���� �б�
};

class TW_ToolBar : public CWnd
{
	DECLARE_DYNAMIC(TW_ToolBar)
private:
	CRect m_rect;				// ���ٰ� �׷��� ����
	CFont m_tool_font;				// ���� �۲�
	TipsCommandData m_btn_list[MAX_BUTTON_COUNT];				// ��ư ������ (����ü �迭)
	int m_btn_count = 0;					// ���� ��ư ����
	int m_select_index = -1;				// ������ ��ư�� ��ȣ
	char m_clicked_flag = 0;				// 0:Ŭ��X, 1:Ŭ��, 2:Ŭ���Ǿ����� ��ư���� �ۿ� ����
	CRect m_select_rect;				// Ŭ���� ��ư�� ���� ����
	CDC m_mem_dc;						// CBitmap�� ȭ�����
	COLORREF m_bk_color;				// ���� ����
	COLORREF m_border_color;				// ���� �׵θ���
	COLORREF m_in_border_color;				// ���� �����׵θ� ��
	COLORREF m_push_btn_color;				// ���� ��ư ����
	COLORREF m_text_color;					// ��ư ���� ����

public:
	TW_ToolBar();
	virtual ~TW_ToolBar();
	// ���� ����
	void CreateToolBar(int a_rect_id, CWnd* ap_parent, int a_ctrl_id);
	// ���ٿ� ��ư ������� (CreateToolBar �Լ� ȣ�� ���� ����ؾ���)
	void AddButton(const TCHAR* ap_name, int a_command_id, int a_bmp_up_id = 0, int a_bmp_down_id = 0);
	// ��ư ��ġ ����
	void UpdateButtonInfo();
	// ���콺�� ��ġ�� ���� ��ư�� ǥ��
	void CheckButtonInToolBar(CPoint point);
	// ��ư�� ������ ���¸� ���
	void DrawPushButton(TipsCommandData* ap_btn);
	// ��ư�� ���ȴٰ� ������ ���¸� ���
	void DrawPopButton(TipsCommandData* ap_btn);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};


