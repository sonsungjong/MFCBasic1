// BinDataView.cpp : implementation file
//

#include "pch.h"
#include "MFCL232BinaryViewerUp.h"
#include "BinDataView.h"


// BinDataView

IMPLEMENT_DYNAMIC(BinDataView, CWnd)

BinDataView::BinDataView()
{

}

BinDataView::~BinDataView()
{
}


BEGIN_MESSAGE_MAP(BinDataView, CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()



// BinDataView message handlers




int BinDataView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	GetClientRect(&m_view_rect);					// �ڽ��� �簢�� ������ ����
	m_view_cx = m_view_rect.Width();				// ���� ���
	m_view_cy = m_view_rect.Height();			// ���� ���

	// �� ȭ�鿡 ���� �ִ� ����
	m_item_view_count = m_view_cy / ITEM_HEIGHT;				// ���̸� ��ȭ�鿡�� ������ �హ���� ����
	if (m_view_cy % ITEM_HEIGHT) { m_item_view_count++; }				// �������� ����� �హ�� 1�� �߰�
	
	// �̹����� �����ϰ� DC�� ��Ī (����������)
	m_draw_image.Create(m_view_rect.Width(), m_view_rect.Height(), 32);
	m_draw_dc.Attach(m_draw_image.GetDC());				// ȭ�鿡 ������ �ʰ� m_draw_dc ��ü�� ��Ʈ�� �ȿ� �׷����� ��

	// �ش� Ŭ������ ��Ʈ ���� (ü�� �־�� �ڰ��� �Ȱ���) ũ��12
	m_font.CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("����ü"));

	// �귯��(����)
	m_bk_brush.CreateSolidBrush(RGB(61, 77, 103));
	// ��(���ڻ�)
	m_bk_pen.CreatePen(PS_SOLID, 1, RGB(61, 77, 103));
	// ��(����)
	m_grid_pen.CreatePen(PS_SOLID, 1, RGB(71, 97, 123));

	DrawData();

	return 0;
}

void BinDataView::DrawOneLine(int a_line_index, int a_scroll_pos, int a_show_count)
{
	// �ε��� ��ȣ, ��ũ�� ��ġ, �������� ����
	// �� ��ȣ ���
	int len = _stprintf_s(m_temp_string, 128, _T("%06d :"), a_line_index + a_scroll_pos + 1);							// ���� ���μ��� 1����
	int element_len = 2;

	m_draw_dc.SetTextColor(RGB(168, 168, 168));
	m_draw_dc.TextOut(5, a_line_index * ITEM_HEIGHT + 5, m_temp_string, len);

	// ���̳ʸ� 24�� 2�ھ� ���ٿ� ���
	unsigned char* p = mp_bin_data + (a_line_index + a_scroll_pos) * m_data_count_per_line;
	m_draw_dc.SetTextColor(RGB(255, 255, 255));
	for (int i = 0; i < a_show_count; i++) {
		element_len = _stprintf_s(m_temp_string, 128, _T("%02X"), *p);
		m_draw_dc.TextOut(60 + i * 24, a_line_index * ITEM_HEIGHT + 5, m_temp_string, element_len);
		p++;
	}

	// ���м� �׸���
	m_draw_dc.MoveTo(3, (a_line_index + 1) * ITEM_HEIGHT - 2);
	m_draw_dc.LineTo(m_view_cx - 3, (a_line_index + 1) * ITEM_HEIGHT - 2);
}

void BinDataView::DrawData()
{
	// ��� ����
	m_draw_dc.SelectObject(&m_bk_brush);					// �귯�� ����
	m_draw_dc.SelectObject(&m_bk_pen);					// �� ����
	m_draw_dc.Rectangle(m_view_rect);						// ���� ����

	// �۲� ����
	m_draw_dc.SetBkColor(RGB(61, 77, 103));				// �ؽ�Ʈ ��� ����
	m_draw_dc.SetTextColor(RGB(0, 200, 255));				// �ؽ�Ʈ�� ����
	
	// ������ ���� �������� ����
	if (!m_line_count) { return; }

	// ���� ��ũ�� ��ġ�� ���´�
	int scroll_pos = GetScrollPos(SB_VERT);
	int count = 0;
	int last_flag = 0;
	int i = 0;

	// ���� ������ �� ȭ�鿡 ������ �� �ִ� ������ ������
	if (m_item_view_count < m_line_count) {
		count = m_item_view_count;
		if (count + scroll_pos >= m_line_count) { count--; }				// ������ ���� ���� ���� ���;���
	}
	else {
		// �� ȭ�鿡 ������ ���� ������ ȭ�麸�� ���� ���
		count = m_line_count;
	}

	// ������ ���� ����ؾ��ϴ� ���
	// ������ ���� �����Ͱ� m_data_count_per_line�� ä���� ���ϴ��� üũ�Ͽ� �ݺ������� �׸����ʰ���
	if ((scroll_pos + count) == m_line_count && m_last_count != 0) {
		// ������ ������ ������ ���̶�� �ݺ������� �׸��� �ʰ� ���� if������ �׸���
		last_flag = 1;
		count--;
	}

	m_draw_dc.SelectObject(&m_grid_pen);
	m_draw_dc.SelectObject(&m_font);

	for (i = 0; i < count; i++) {
		DrawOneLine(i, scroll_pos, m_data_count_per_line);
	}

	// �ݺ������� ���ǹ� �Ȼ���Ϸ��� ���� ���������� ������ ��
	if (last_flag != 0) {
		DrawOneLine(i, scroll_pos, m_last_count);
	}
}

void BinDataView::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: Add your message handler code here

	// dc�� Detach
	m_draw_dc.Detach();
	// CImage ����
	m_draw_image.ReleaseDC();
	m_draw_image.Destroy();

	// Create ��ȯ
	m_bk_brush.DeleteObject();
	m_bk_pen.DeleteObject();
	m_grid_pen.DeleteObject();

	// ���� ���������� �޸�����
	if (mp_bin_data != NULL) { ::HeapFree(GetProcessHeap(), 0, mp_bin_data); }
}

void BinDataView::OnPaint()
{
	CPaintDC dc(this);

	// CImage�� �׷����� ��Ʈ���� (0, 0)�� �׸�
	m_draw_image.Draw(dc, 0, 0);
}

// ���� ��ũ�� ���۽� �۵���Ű�� �Լ�
void BinDataView::ProcessScroll(UINT nSBCode, UINT nPos, int a_scroll_type)
{
	if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK) {
		// SetScrollPos(a_scroll_type, nPos);						// �⺻ ��ũ�ѹٴ� 3���� �Ѿ�� �������� ���� (����int)

		// ���� ��ũ�� ��ġ ����
		SCROLLINFO si = { sizeof(SCROLLINFO), SIF_TRACKPOS, };
		GetScrollInfo(SB_VERT, &si);								// ��ũ�� ��ġ ������ �޾ƿͼ�
		SetScrollPos(a_scroll_type, si.nTrackPos);				// ��ũ�ѿ� ��ġ�� ���� ����
	}
	else {
		int scroll_pos = GetScrollPos(a_scroll_type);
		int min = 0;
		int max = 0;
		GetScrollRange(a_scroll_type, &min, &max);

		switch (nSBCode) {
		case SB_LINEDOWN:
			if (scroll_pos < max) { SetScrollPos(a_scroll_type, scroll_pos + 1); }
			break;
		case SB_LINEUP:
			if (scroll_pos > min) { SetScrollPos(a_scroll_type, scroll_pos - 1); }
			break;
		case SB_PAGEDOWN:
			if (scroll_pos + 10 < max) { SetScrollPos(a_scroll_type, scroll_pos + 10); }
			break;
		case SB_PAGEUP:
			if (scroll_pos - 10 > min) { SetScrollPos(a_scroll_type, scroll_pos - 10); }
			break;
		}
	}
}

// ������ũ�� ���α׷��� (VScroll)
void BinDataView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar == NULL)				// �⺻ ���� ��ũ�ѹ��� ��� NULL
	{
		ProcessScroll(nSBCode, nPos, SB_VERT);				// ��ũ�� ��ġ�̵�

		// WM_PAINT Ȱ�� (���ϰ� ���ϸ� ������ �� ���� --> ReDraw�� ��ü�ϸ� �ذ�)
		DrawData();				// ����� �ٽ� �׸�����
		Invalidate(FALSE);				// ȭ�� ����
	}

	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

// OnPaint ���� �ٷ� �����ϰ����� ���
void BinDataView::ReDraw()
{
	DrawData();

	CClientDC dc(this);
	m_draw_image.Draw(dc, 0, 0);
}

// �ش� ����� ������ ����
void BinDataView::LoadFile(const TCHAR* ap_path)
{
	// �̹� ���������� �޸� ����
	if (mp_bin_data != NULL) 
		{ ::HeapFree(::GetProcessHeap(), 0, mp_bin_data); }					// free(mp_bin_data);

	FILE* p_file = NULL;
	errno_t err;
	
	err = _tfopen_s(&p_file, ap_path, _T("rb"));					// ���̳ʸ� ���·� ������ ���ڴ�
	if (err == 0 && p_file != NULL)			// ���� ���� ���� (0 ��ȯ)
	{
		fseek(p_file, 0, SEEK_END);				// ���� �����͸� ������ �̵��ϱ�
		m_bin_data_size = ftell(p_file);				// ������ ����Ű�� ���� ��ġ���� ����
		mp_bin_data = (unsigned char*)::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, m_bin_data_size);				// new unsigned char[m_bin_data_size];
		fseek(p_file, 0, SEEK_SET);						// ���� �����͸� ó������ �̵�
		fread(mp_bin_data, m_bin_data_size, 1, p_file);						// �Ҵ��� �޸𸮿� ������ 1���� �о ����
		fclose(p_file);						// ���� �ݱ�

		m_line_count = m_bin_data_size / m_data_count_per_line;						// 24�� ���� ���� �� ���� �ǰ�
		m_last_count = m_bin_data_size % m_data_count_per_line;					// 24�� ���� �������� ������ ���� ������ ��
		if (m_last_count) { m_line_count++; }				// �������� 0�� �ƴϾ��� ��� ������ ������ �� �ִٴ� ���� �˷��� (���� +1)
	}
	else {
		// ���� ���� ���н�
		mp_bin_data = NULL;
		m_bin_data_size = 0;
		m_last_count = 0;
	}

	// ȭ�麸�� ��������ϴ� ������ �� ������ ��ũ���� Ȱ��ȭ
	if (m_line_count > m_item_view_count) {
		ModifyStyle(0, WS_VSCROLL, SWP_DRAWFRAME);								// ������ �Ӽ����� : ������ ���� ����, VSCROLL �߰�, 
		SetScrollRange(SB_VERT, 0, m_line_count - m_item_view_count + 1, 0);				// �� �پ� �̵�
	}
	else {
		ModifyStyle(WS_VSCROLL, 0, SWP_DRAWFRAME);						// VSCROLL ����, �߰��� �� ����, 
	}

	SetScrollPos(SB_VERT, 0, 1);				// ��ũ�� ���� ����
	ReDraw();
}
