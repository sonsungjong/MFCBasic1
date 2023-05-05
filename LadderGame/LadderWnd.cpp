#include "pch.h"
#include "LadderGameDlg.h"				// 부모 다이얼로그 포함하기
#include "LadderWnd.h"						// 자신의 헤더

IMPLEMENT_DYNAMIC(LadderWnd, CWnd)

LadderWnd::LadderWnd()
{
}

LadderWnd::~LadderWnd()
{

}

BEGIN_MESSAGE_MAP(LadderWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// 메시지 처리기
int LadderWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) { return -1; }
	GetClientRect(m_rect);			// 그림을 그릴 영역

	// 이미지 객체 생성
	m_draw_image.Create(m_rect.Width(), m_rect.Height(), 32);
	mh_draw_dc = m_draw_image.GetDC();				// 메모리 DC

	// 색상 변경하여 펜과 브러시 지정
	::SelectObject(mh_draw_dc, ::GetStockObject(DC_BRUSH));
	::SelectObject(mh_draw_dc, ::GetStockObject(DC_PEN));

	// 글꼴
	m_font = ::CreateFont(18, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH || FF_SWISS, _T("맑은 고딕"));
	::SelectObject(mh_draw_dc, m_font);										// 글꼴을 메모리DC에 반영
	::SetTextColor(mh_draw_dc, RGB(128, 202, 128));					// 출력할 문자열의 색상
	::SetBkMode(mh_draw_dc, TRANSPARENT);								// 글자배경 투명

	MyDraw();
	return 0;
}

const TCHAR* gp_name_table[MEMBER_COUNT] = { _T("첫번째"), _T("두번째"), _T("세번째"), _T("네번째"), _T("다섯번째")};
const UINT8 g_name_table_len[MEMBER_COUNT] = { 3, 3, 3, 3, 4 };
const TCHAR* gp_result_table[MEMBER_COUNT] = { _T("꽝"), _T("치킨"), _T("피자"), _T("꽝"), _T("콜라")};
const UINT8 g_result_table_len[MEMBER_COUNT] = { 1,2,2,1,2 };

// 이미지 객체에 그림 그리기
void LadderWnd::MyDraw()
{
	::SetDCBrushColor(mh_draw_dc, RGB(82, 97, 124));			// 브러시 색
	::SetDCBrushColor(mh_draw_dc, RGB(82, 97, 124));			// 펜 색

	::Rectangle(mh_draw_dc, 0, 0, m_rect.Width(), m_rect.Height());			// 배경 사각형

	::SetDCBrushColor(mh_draw_dc, RGB(72, 87, 114));			// 브러시 색
	::SetDCPenColor(mh_draw_dc, RGB(122, 137, 164));			// 펜 색

	RECT name_rect = {20, 20, 80, 50};				// 시작 이름 사각형의 위치
	RECT result_rect = { 20, 350, 80, 380 };				// 마침 위치

	// 옆으로 이동하면서 사각형 총 5개 그림
	for (int i = 0; i < MEMBER_COUNT; i++)
	{
		// 시작 박스
		::Rectangle(mh_draw_dc, name_rect.left, name_rect.top, name_rect.right, name_rect.bottom);
		::DrawText(mh_draw_dc, gp_name_table[i], g_name_table_len[i], &name_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);			// 글자 중앙
		name_rect.left += 85;
		name_rect.right += 85;

		// 마침 박스
		::Rectangle(mh_draw_dc, result_rect.left, result_rect.top, result_rect.right, result_rect.bottom);
		::DrawText(mh_draw_dc, gp_result_table[i], g_result_table_len[i], &result_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);			// 글자 중앙
		result_rect.left += 85;
		result_rect.right += 85;
	}

	// 사다리 선 5개
	int line_x = 50;
	for (int i = 0; i < MEMBER_COUNT; ++i)
	{
		::MoveToEx(mh_draw_dc, line_x, 55, NULL);
		::LineTo(mh_draw_dc, line_x, 345);
		line_x += 85;
	}
}

void LadderWnd::OnDestroy()
{
	CWnd::OnDestroy();

	m_draw_image.ReleaseDC();				// 메모리DC 반납
	m_draw_image.Destroy();					// 이미지 객체 제거
	
	::DeleteObject(m_font);						// 글꼴 해제
}

void LadderWnd::OnPaint()
{
	CPaintDC dc(this);
	m_draw_image.Draw(dc, m_rect);
}
