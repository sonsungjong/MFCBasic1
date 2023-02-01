// TW_ToolBar.cpp : implementation file
#include "pch.h"
#include "XRayViewer.h"
#include "TW_ToolBar.h"

IMPLEMENT_DYNAMIC(TW_ToolBar, CWnd)

TW_ToolBar::TW_ToolBar()
{
	m_bk_color = RGB(39, 43, 47);
	m_border_color = RGB(59, 63, 67);
	m_in_border_color = RGB(109, 113, 117);
	m_push_btn_color = RGB(59, 63, 67);
	m_text_color = RGB(255, 255, 255);
}

TW_ToolBar::~TW_ToolBar()
{
}

void TW_ToolBar::CreateToolBar(int a_rect_id, CWnd* ap_parent, int a_ctrl_id)
{
	CRect rect;

	// Picture Control ��ġ�� ���
	ap_parent->GetDlgItem(a_rect_id)->GetWindowRect(rect);
	// Ŭ���̾�Ʈ ���̾�α� �������� ��ǥ�� ����
	ap_parent->ScreenToClient(rect);

	// ���������� �ణ�� ������ ����� ������ ���������� ���� �� ũ�� �����Ѵ�
	rect.right += 2;
	// ����
	Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rect, ap_parent, a_ctrl_id);
}

void TW_ToolBar::AddButton(const TCHAR* ap_name, int a_command_id, int a_bmp_up_id, int a_bmp_down_id)
{
	if (m_btn_count < MAX_BUTTON_COUNT) {
		int len = _tcslen(ap_name);
		m_btn_list[m_btn_count].name_len = len;				// NULL�� ������ ���ڱ��̸� �Ҵ�
		len++;					// len�� NULL�� ������ ũ��� ����
		m_btn_list[m_btn_count].p_name = new TCHAR[len];					// �̸��� ������ �޸𸮸� �Ҵ�
		memcpy(m_btn_list[m_btn_count].p_name, ap_name, len * sizeof(TCHAR));				// �Ű������� �̸��� ����
		
		// ��ư�� ������ �� ����� �޽���ID�� ����
		m_btn_list[m_btn_count].command_id = a_command_id;
		m_btn_list[m_btn_count].bmp_up_id = a_bmp_up_id;
		m_btn_list[m_btn_count].bmp_down_id = a_bmp_down_id;

		// ��Ʈ�� ���ҽ� ���̵� 0�� �ƴ϶��
		if (m_btn_list[m_btn_count].bmp_up_id != 0) {
			// ���ҽ��� bmp�� �о CBitmap �� ����
			m_btn_list[m_btn_count].p_up_bitmap = new CBitmap;
			m_btn_list[m_btn_count].p_up_bitmap->LoadBitmap(a_bmp_up_id);

			m_btn_list[m_btn_count].p_down_bitmap = new CBitmap;
			m_btn_list[m_btn_count].p_down_bitmap->LoadBitmap(a_bmp_down_id);
		}
		else {
			m_btn_list[m_btn_count].p_up_bitmap = NULL;
			m_btn_list[m_btn_count].p_down_bitmap = NULL;
		}
		m_btn_count++;				// ��ϵ� ��ư�� ���� ������Ų��
	}
}

void TW_ToolBar::UpdateButtonInfo()
{
	CClientDC dc(this);

	// ���ٿ� ��ϵ� ��ư�� �� ù ��°�� ����Ų��
	TipsCommandData* p_btn = m_btn_list;
	dc.SelectObject(&m_tool_font);				// �۲� ����
	int position = 5;
	int i = 0;

	for (i = 0; i < m_btn_count; i++, p_btn++) {
		// ó�� ���� ��ġ
		p_btn->x = position;

		// ��ư �̸� ũ�⸦ ����Ͽ� ��ư ũ�⸦ ����
		p_btn->width = dc.GetTextExtent(p_btn->p_name, p_btn->name_len).cx + 20;

		// ���� ��ư�� ���� ��ġ�� ����
		position += p_btn->width;
	}
}

void TW_ToolBar::CheckButtonInToolBar(CPoint point)
{
	// ���ٿ� ��ϵ� ��ư�� �� ù ��°�� ����Ų��
	TipsCommandData* p_btn = m_btn_list;
	CRect r;
	int i = 0;
	int old_index = m_select_index;

	// ���콺�� ���� ��ġ�� ����ؼ� ������ � ��ư ������ ��ġ�ߴ��� üũ
	for (i = 0; i < m_btn_count; i++, p_btn++) {
		// ���� ��ư�� ��ġ ������ ����
		r.SetRect(p_btn->x + 3, 3, p_btn->x + p_btn->width - 3, m_rect.bottom - 3);

		// ���콺�� ��ư ���� ��ġ�� ���
		if (r.PtInRect(point)) {
			// �ش� ��ư�� ���õ� ��ư���� ����
			m_select_index = i;
			break;
		}
	}

	// ���� i ���� m_btn_count�� �����ϸ� ���콺�� ���� ��ư ���� ���ٴ� ��
	if (i == m_btn_count) { m_select_index = -1; }

	// ������ ���� ���°� ����Ǹ�
	if (old_index != m_select_index) {
		CClientDC dc(this);
		dc.SelectStockObject(DC_PEN);					// ���� �����ؼ� ����ϴ� Pen
		dc.SelectStockObject(NULL_BRUSH);			// �귯�� ����

		if (old_index != -1) {
			// ������ ���õ� ��ư�� ���¸� ����
			p_btn = m_btn_list + old_index;
			dc.SetDCPenColor(m_bk_color);
			dc.Rectangle(p_btn->x + 3, 3, p_btn->x + p_btn->width - 3, m_rect.bottom - 3);
			dc.Rectangle(p_btn->x + 4, 4, p_btn->x + p_btn->width - 4, m_rect.bottom - 4);
		}

		if (m_select_index != -1) {
			// ���� ���õ� ��ư�� �׸���
			p_btn = m_btn_list + m_select_index;
			dc.SetDCPenColor(m_border_color);				// Pen ���� ����
			dc.Rectangle(p_btn->x + 3, 3, p_btn->x + p_btn->width - 3, m_rect.bottom - 3);

			dc.SetDCPenColor(m_in_border_color);			// Pen ���� ����
			dc.Rectangle(p_btn->x + 4, 4, p_btn->x + p_btn->width - 4, m_rect.bottom - 4);
		}
	}
}

void TW_ToolBar::DrawPushButton(TipsCommandData* ap_btn)
{
	CClientDC dc(this);

	dc.SelectObject(&m_tool_font);				// �۲� ����
	dc.SetBkMode(TRANSPARENT);				// ���ڿ� ��� ����ó��

	dc.SelectStockObject(DC_BRUSH);			// ���� �����ؼ� ����ϴ� Brush
	dc.SelectStockObject(DC_PEN);				// ���� �����ؼ� ����ϴ� Pen

	dc.SetDCBrushColor(m_push_btn_color);				// ���� (�귯��)
	dc.SetDCPenColor(m_in_border_color);				// �׵θ� �� (��)

	dc.Rectangle(m_select_rect);			// ��ư�� �׸���

	CRect r = m_select_rect;
	r.bottom -= 4;				// ��ġ ����

	// �̹����� �� �ҷ��Դٸ�
	if (ap_btn->p_down_bitmap != NULL) {
		// �޸�DC�� bitmap�� �����ϰ� �׸���
		m_mem_dc.SelectObject(ap_btn->p_down_bitmap);
		dc.BitBlt(ap_btn->x + ap_btn->width / 2 - 16 + 1, 11, 32, 32, &m_mem_dc, 0, 0, SRCCOPY);
	}

	// ���ڿ� ������� ���
	dc.SetTextColor(m_text_color);
	dc.DrawText(ap_btn->p_name, r + CPoint(1, 1), DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
}

void TW_ToolBar::DrawPopButton(TipsCommandData* ap_btn)
{
	CClientDC dc(this);

	dc.SelectObject(&m_tool_font);				// �۲� ����
	dc.SetBkMode(TRANSPARENT);				// ���ڹ�� ����ó��

	dc.SelectStockObject(DC_BRUSH);				// ���� �����ؼ� ����ϴ� Brush
	dc.SelectStockObject(DC_PEN);					// ���� �����ؼ� ����ϴ� Pen

	dc.SetDCBrushColor(m_bk_color);
	dc.SetDCPenColor(m_in_border_color);

	dc.Rectangle(m_select_rect);

	CRect r = m_select_rect;
	r.bottom -= 4;
	if (ap_btn->p_up_bitmap != NULL) {
		m_mem_dc.SelectObject(ap_btn->p_up_bitmap);
		dc.BitBlt(ap_btn->x + ap_btn->width / 2 - 16, 10, 32, 32, &m_mem_dc, 0, 0, SRCCOPY);
	}

	// ������� ���ڿ� ���
	dc.SetTextColor(m_text_color);
	dc.DrawText(ap_btn->p_name, r, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
}


BEGIN_MESSAGE_MAP(TW_ToolBar, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// TW_ToolBar message handlers
int TW_ToolBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CClientDC dc(this);
	// ��ư�� �޸�DC
	m_mem_dc.CreateCompatibleDC(&dc);

	// �簢�� ��ǥ�� ��´�
	GetClientRect(m_rect);
	// ��Ʈ�� ���Ѵ�
	m_tool_font.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("���� ���"));

	UpdateButtonInfo();					// ��ϵ� ��ư���� ��ġ ���� ����
	return 0;
}




void TW_ToolBar::OnPaint()
{
	CPaintDC dc(this); 

	dc.SelectStockObject(DC_BRUSH);				// ����� ���� �귯��
	dc.SetDCBrushColor(m_bk_color);
	
	dc.SelectStockObject(DC_PEN);					// ����� ���� ��
	dc.SetDCPenColor(m_bk_color);

	dc.Rectangle(m_rect);				// ������ �簢���� �׸���

	dc.SelectStockObject(NULL_BRUSH);				// �귯�� ������
	dc.SetDCPenColor(m_border_color);				// �� �� ����

	// ���� �簢�� (���� �׵θ� �߰�)
	dc.Rectangle(m_rect.left + 1, m_rect.top + 1, m_rect.right - 1, m_rect.bottom - 1);

	CRect rect;
	TipsCommandData* p_btn = m_btn_list;				// ù��° ��ư�� �ּҸ� ����

	dc.SelectObject(&m_tool_font);				// ��Ʈ ����
	dc.SetBkMode(TRANSPARENT);				// ��Ʈ ��� ����ó��

	for (int i = 0; i < m_btn_count; i++, p_btn++) {
		rect.SetRect(p_btn->x, 3, p_btn->x + p_btn->width, m_rect.bottom - 8);				// left,top,right,bottom
		if (p_btn->p_up_bitmap != NULL) {					// �̹����� �ε�� ���¸�
			m_mem_dc.SelectObject(p_btn->p_up_bitmap);				// �޸�DC�� ����
			dc.BitBlt(p_btn->x + p_btn->width / 2 - 16, 10, 32, 32, &m_mem_dc, 0, 0, SRCCOPY);			// ȭ�� ���
		}

		// ���ڿ��� ��ư ��ġ�� ���
		dc.SetTextColor(m_text_color);
		dc.DrawText(p_btn->p_name, rect, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
	}
}


void TW_ToolBar::OnDestroy()
{

	// TODO: Add your message handler code here
	// ��ư �̸��� ������ �޸�����
	for (int i = 0; i < m_btn_count; i++) {
		delete[] m_btn_list[i].p_name;

		if (m_btn_list[i].p_up_bitmap != NULL) {
			m_btn_list[i].p_up_bitmap->DeleteObject();				// ��Ʈ�� ����
			delete m_btn_list[i].p_up_bitmap;

			m_btn_list[i].p_down_bitmap->DeleteObject();
			delete m_btn_list[i].p_down_bitmap;
		}
	}
	m_tool_font.DeleteObject();			// ��Ʈ ����
	m_mem_dc.DeleteDC();					// �޸�DC ����

	CWnd::OnDestroy();
}


void TW_ToolBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_clicked_flag && m_select_index != -1) {
		// Ŭ���� ���°� �ƴ϶�� ���� ����
		m_clicked_flag = 1;				// Ŭ�� ���·� ����
		TipsCommandData* p_btn = m_btn_list + m_select_index;			// ���� ��ư ����

		// ������ ��ư�� ������ ���
		m_select_rect.SetRect(p_btn->x + 4, 4, p_btn->x + p_btn->width - 4, m_rect.bottom - 4);
		// ������ ������� ��ü
		DrawPushButton(p_btn);
		// ���콺�� ������ ����� �۵��� �� �ְ�
		SetCapture();
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void TW_ToolBar::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_clicked_flag) {
		// ���콺�� Ŭ���� �ȵǾ� ������
		CheckButtonInToolBar(point);				// ��ư�� ��ġ��
	}
	else {
		// Ŭ�� ���¸�
		if (m_select_rect.PtInRect(point)) {
			if (m_clicked_flag == 2) {
				m_clicked_flag = 1;				// ���� �ۿ� �ִٰ� ���� ������ ������ Ŭ���÷��� ����
				DrawPushButton(m_btn_list + m_select_index);			// ������ ������� ��ü
			}
		}
		else {
			if (m_clicked_flag == 1) {
				m_clicked_flag = 2;				// Ŭ�� �� ��ư ������ ����� ���
				DrawPopButton(m_btn_list + m_select_index);					// ��ư�� �⺻ ������� ��ü
			}
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}

void TW_ToolBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_clicked_flag) {
		// Ŭ���Ǿ��ٰ� ����� ���
		m_clicked_flag = 0;
		ReleaseCapture();

		TipsCommandData* p_btn = m_btn_list + m_select_index;				// ������ ��ư�� ����
		DrawPopButton(p_btn);					// �⺻ ��ư�� ������� ��ü

		if (m_select_rect.PtInRect(point)) {
			// ��ư ���� ������ ���콺�� ����� ����
			// ��ư�� �����ٴ� �޽����� �θ� �����쿡 WM_COMMAND�� ������
			GetParent()->PostMessage(WM_COMMAND, MAKEWPARAM(p_btn->command_id, 0), 0);
		}
	}

	CWnd::OnLButtonUp(nFlags, point);
}


