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
	if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK) { SetScrollPos(a_scroll_type, nPos); }
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
	if (mp_bin_data != NULL) { ::HeapFree(::GetProcessHeap(), 0, mp_bin_data); }					// free(mp_bin_data);

	FILE* p_file = NULL;
	if (_tfopen_s(&p_file, ap_path, _T("rb")) == 0)			// ���� ���� ����
	{
		fseek(p_file, 0, SEEK_END);
		m_bin_data_size = ftell(p_file);
		mp_bin_data = (unsigned char*)::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, m_bin_data_size);				// new unsigned char[m_bin_data_size];
		fseek(p_file, 0, SEEK_SET);
		fread(mp_bin_data, m_bin_data_size, 1, p_file);
		fclose(p_file);

		m_line_count = m_bin_data_size / m_data_count_per_line;
		m_last_count = m_bin_data_size % m_data_count_per_line;
		if (m_last_count) { m_line_count++; }
	}
	else {
		// ���� ���� ���н�
		mp_bin_data = NULL;
		m_bin_data_size = 0;
		m_last_count = 0;
	}
}