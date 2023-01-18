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

void BinDataView::DrawOneLine(int a_line_index, int a_scroll_pos, int a_show_count)
{
	// 인덱스 번호, 스크롤 위치, 마지막줄 갯수
	// 줄 번호 출력
	int len = _stprintf_s(m_temp_string, 128, _T("%06d :"), a_line_index + a_scroll_pos + 1);							// 현재 라인수는 1부터
	int element_len = 2;

	m_draw_dc.SetTextColor(RGB(168, 168, 168));
	m_draw_dc.TextOut(5, a_line_index * ITEM_HEIGHT + 5, m_temp_string, len);

	// 바이너리 24개 2자씩 한줄에 찍기
	unsigned char* p = mp_bin_data + (a_line_index + a_scroll_pos) * m_data_count_per_line;
	m_draw_dc.SetTextColor(RGB(255, 255, 255));
	for (int i = 0; i < a_show_count; i++) {
		element_len = _stprintf_s(m_temp_string, 128, _T("%02X"), *p);
		m_draw_dc.TextOut(60 + i * 24, a_line_index * ITEM_HEIGHT + 5, m_temp_string, element_len);
		p++;
	}

	// 구분선 그리기
	m_draw_dc.MoveTo(3, (a_line_index + 1) * ITEM_HEIGHT - 2);
	m_draw_dc.LineTo(m_view_cx - 3, (a_line_index + 1) * ITEM_HEIGHT - 2);
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

	// 현재 스크롤 위치를 얻어온다
	int scroll_pos = GetScrollPos(SB_VERT);
	int count = 0;
	int last_flag = 0;
	int i = 0;

	// 행의 갯수가 한 화면에 보여줄 수 있는 수보다 많으면
	if (m_item_view_count < m_line_count) {
		count = m_item_view_count;
		if (count + scroll_pos >= m_line_count) { count--; }				// 마지막 줄은 한줄 적게 나와야함
	}
	else {
		// 한 화면에 보여줄 행의 갯수가 화면보다 적을 경우
		count = m_line_count;
	}

	// 마지막 행을 출력해야하는 경우
	// 마지막 행은 데이터가 m_data_count_per_line을 채우지 못하는지 체크하여 반복문에서 그리지않게함
	if ((scroll_pos + count) == m_line_count && m_last_count != 0) {
		// 갯수가 부족한 마지막 행이라면 반복문에서 그리지 않고 따로 if문으로 그린다
		last_flag = 1;
		count--;
	}

	m_draw_dc.SelectObject(&m_grid_pen);
	m_draw_dc.SelectObject(&m_font);

	for (i = 0; i < count; i++) {
		DrawOneLine(i, scroll_pos, m_data_count_per_line);
	}

	// 반복문에서 조건문 안사용하려고 따로 나머지행은 밖으로 뺌
	if (last_flag != 0) {
		DrawOneLine(i, scroll_pos, m_last_count);
	}
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
	if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK) {
		// SetScrollPos(a_scroll_type, nPos);						// 기본 스크롤바는 3만을 넘어가면 동작하지 않음 (과거int)

		// 수직 스크롤 위치 셋팅
		SCROLLINFO si = { sizeof(SCROLLINFO), SIF_TRACKPOS, };
		GetScrollInfo(SB_VERT, &si);								// 스크롤 위치 정보를 받아와서
		SetScrollPos(a_scroll_type, si.nTrackPos);				// 스크롤에 위치를 직접 넣음
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
	if (mp_bin_data != NULL) 
		{ ::HeapFree(::GetProcessHeap(), 0, mp_bin_data); }					// free(mp_bin_data);

	FILE* p_file = NULL;
	errno_t err;
	
	err = _tfopen_s(&p_file, ap_path, _T("rb"));					// 바이너리 형태로 파일을 열겠다
	if (err == 0 && p_file != NULL)			// 파일 열기 성공 (0 반환)
	{
		fseek(p_file, 0, SEEK_END);				// 파일 포인터를 끝으로 이동하기
		m_bin_data_size = ftell(p_file);				// 파일의 가리키는 현재 위치값을 얻음
		mp_bin_data = (unsigned char*)::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, m_bin_data_size);				// new unsigned char[m_bin_data_size];
		fseek(p_file, 0, SEEK_SET);						// 파일 포인터를 처음으로 이동
		fread(mp_bin_data, m_bin_data_size, 1, p_file);						// 할당한 메모리에 파일을 1번만 읽어서 저장
		fclose(p_file);						// 파일 닫기

		m_line_count = m_bin_data_size / m_data_count_per_line;						// 24로 나눈 몫이 줄 수가 되고
		m_last_count = m_bin_data_size % m_data_count_per_line;					// 24로 나눈 나머지가 마지막 줄의 갯수가 됨
		if (m_last_count) { m_line_count++; }				// 나머지가 0이 아니었을 경우 마지막 한줄이 더 있다는 것을 알려줌 (갯수 +1)
	}
	else {
		// 파일 열기 실패시
		mp_bin_data = NULL;
		m_bin_data_size = 0;
		m_last_count = 0;
	}

	// 화면보다 보여줘야하는 갯수가 더 많으면 스크롤을 활성화
	if (m_line_count > m_item_view_count) {
		ModifyStyle(0, WS_VSCROLL, SWP_DRAWFRAME);								// 윈도우 속성변경 : 제거할 것은 없고, VSCROLL 추가, 
		SetScrollRange(SB_VERT, 0, m_line_count - m_item_view_count + 1, 0);				// 한 줄씩 이동
	}
	else {
		ModifyStyle(WS_VSCROLL, 0, SWP_DRAWFRAME);						// VSCROLL 제거, 추가할 것 없음, 
	}

	SetScrollPos(SB_VERT, 0, 1);				// 스크롤 제일 위로
	ReDraw();
}
