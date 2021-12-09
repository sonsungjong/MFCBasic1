// Ŭ���� ���� : �輺�� (tipsware@naver.com)
// 2021�� 4�� 11�� �Ͽ���
// ���� Ŭ�����ÿ��� �ʱ�ȭ�� �� ����ǵ��� PreSubclassWindow �Լ� �߰�

#pragma once
class User_ListBox : public CListBox
{
	DECLARE_DYNAMIC(User_ListBox)
protected:
	// ����Ʈ �ڽ� �������� ����� �귯�� ��ü
	HBRUSH mh_list_bk_brush;
	// ��Ȳ�� �귯�� ������ ����� ������
	COLORREF m_select_brush_color, m_focus_brush_color, m_bk_brush_color;
	// ��Ȳ�� �� ������ ����� ������
	COLORREF m_select_pen_color, m_focus_pen_color, m_bk_pen_color;
	// ���� ó������ Owner-Draw ����ü ����, �Ű� ������ ��� �ȳѱ���� 
	// ����ü �ּҸ� �����ؼ� ���. ���߿� ����ϸ� �ּҰ� ��ȿ���� 
	// ������ ������ �����ؾ� ��!
	LPDRAWITEMSTRUCT mp_last_lpds;

	// ����Ʈ �ڽ��� �������� ��� ���� ����� �̹��� ��ü
	CImage m_draw_image;
	// �̹��� ��ü�� �۹��� �׸��� ����� DC ��ü
	HDC mh_draw_dc;
	// ���� �����츦 ������ �� ����� �Լ�(������)
	void Invalidate(BOOL bErase =0);
	void CreateMemoryDC();

public:
	User_ListBox();
	virtual ~User_ListBox();

	// WM_CREATE�� ������� �ʰ� ����Ʈ �ڽ��� �����ɶ� �Բ� �۾��ؾ� ��
	// ������ �߰��ϱ� ���ؼ� �� �Լ��� ������
	virtual void CreateUserObject() {}
	// WM_DESTROY�� ������� �ʰ� ����Ʈ �ڽ��� ���ŵɶ� �Բ� �۾��ؾ� ��
	// ������ �߰��ϱ� ���ؼ� �� �Լ��� ������
	virtual void DeleteUserObject() {}
	// �� �׸��� ����� �׸��� ���� ����� �Լ� (�⺻ �ڵ� ����)
	virtual void BaseDraw(HDC ah_dc, RECT *ap_rect);
	// �� �׸� ��µ� ������ �׸��� �Լ�
	virtual void UserDraw(HDC ah_dc, RECT *ap_rect, void *ap_data) { }
	// ����Ʈ �ڽ��� Ư�� �׸� ��ġ�� �����ϴ� �Լ�
	void UpdateItemInfo(int a_index, int a_count);
	// �׸��� ���� Ŭ������ �� ȣ��Ǵ� �Լ�
	virtual void ProcessDoubleClicked(int a_index) { }
	// ��� ��Ʈ�ѿ��� �����ϴ� �޽����� ó���� �Լ�
	virtual void SetBuddyMessage(int a_count, void* ap_data) {}

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH CtlColor(CDC * /*pDC*/, UINT /*nCtlColor*/);
	afx_msg void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	virtual void PreSubclassWindow();
	afx_msg void OnLbnDblclk();
protected:
	afx_msg LRESULT On44001(WPARAM wParam, LPARAM lParam);
};