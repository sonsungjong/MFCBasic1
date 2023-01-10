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
	GetClientRect(&m_view_rect);					// 자신의 사각형 범위를 저장
	m_view_cx = m_view_rect.Width();				// 가로 백업
	m_view_cy = m_view_rect.Height();			// 높이 백업

	// 한 화면에 보일 최대 갯수
	m_item_view_count = m_view_cy / ITEM_HEIGHT;				// 높이를 한화면에서 보여줄 행갯수로 나눔
	if (m_view_cy % ITEM_HEIGHT) { m_item_view_count++; }				// 나머지가 생기면 행갯수 1개 추가
	
	// 이미지를 생성하고 DC를 매칭 (깜빡임제거)
	m_draw_image.Create(m_view_rect.Width(), m_view_rect.Height(), 32);
	m_draw_dc.Attach(m_draw_image.GetDC());				// 화면에 나가지 않고 m_draw_dc 객체의 비트맵 안에 그려지게 됨

	// 해당 클래스의 폰트 변경 (체가 있어야 자간이 똑같음) 크기12
	m_font.CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("굴림체"));

	// 브러시(배경색)
	m_bk_brush.CreateSolidBrush(RGB(61, 77, 103));
	// 펜(글자색)
	m_bk_pen.CreatePen(PS_SOLID, 1, RGB(61, 77, 103));
	// 펜(선색)
	m_grid_pen.CreatePen(PS_SOLID, 1, RGB(71, 97, 123));

	DrawData();

	return 0;
}

void BinDataView::DrawData()
{
	// 배경 설정
	m_draw_dc.SelectObject(&m_bk_brush);					// 브러시 설정
	m_draw_dc.SelectObject(&m_bk_pen);					// 펜 설정
	m_draw_dc.Rectangle(m_view_rect);						// 범위 설정

	// 글꼴 설정
	m_draw_dc.SetBkColor(RGB(61, 77, 103));				// 텍스트 배경 설정
	m_draw_dc.SetTextColor(RGB(0, 200, 255));				// 텍스트색 설정
	
	// 파일을 열지 못했으면 종료
	if (!m_line_count) { return; }


}


void BinDataView::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: Add your message handler code here

	// dc를 Detach
	m_draw_dc.Detach();
	// CImage 제거
	m_draw_image.ReleaseDC();
	m_draw_image.Destroy();

	// Create 반환
	m_bk_brush.DeleteObject();
	m_bk_pen.DeleteObject();
	m_grid_pen.DeleteObject();

	// 파일 열려있으면 메모리해제
	if (mp_bin_data != NULL) { ::HeapFree(GetProcessHeap(), 0, mp_bin_data); }
}


void BinDataView::OnPaint()
{
	CPaintDC dc(this);

	// CImage에 그려놓은 비트맵을 (0, 0)에 그림
	m_draw_image.Draw(dc, 0, 0);
}

// 수직 스크롤 동작시 작동시키는 함수
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

// 수직스크롤 프로그래밍 (VScroll)
void BinDataView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar == NULL)				// 기본 생성 스크롤바일 경우 NULL
	{
		ProcessScroll(nSBCode, nPos, SB_VERT);				// 스크롤 위치이동

		// WM_PAINT 활용 (부하가 심하면 지연될 수 있음 --> ReDraw로 대체하면 해결)
		DrawData();				// 배경을 다시 그리게함
		Invalidate(FALSE);				// 화면 갱신
	}

	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

// OnPaint 없이 바로 갱신하고자할 경우
void BinDataView::ReDraw()
{
	DrawData();

	CClientDC dc(this);
	m_draw_image.Draw(dc, 0, 0);
}

// 해당 경로의 파일을 읽음
void BinDataView::LoadFile(const TCHAR* ap_path)
{
	// 이미 열려있으면 메모리 해제
	if (mp_bin_data != NULL) { ::HeapFree(::GetProcessHeap(), 0, mp_bin_data); }					// free(mp_bin_data);

	FILE* p_file = NULL;
	if (_tfopen_s(&p_file, ap_path, _T("rb")) == 0)			// 파일 열기 성공
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
		// 파일 열기 실패시
		mp_bin_data = NULL;
		m_bin_data_size = 0;
		m_last_count = 0;
	}
}