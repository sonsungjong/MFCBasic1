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

	MyDraw();
	return 0;
}

// 이미지 객체에 그림 그리기
void LadderWnd::MyDraw()
{
	::SetDCBrushColor(mh_draw_dc, RGB(0, 0, 0));			// 브러시 색
	::SetDCBrushColor(mh_draw_dc, RGB(0, 0, 0));			// 펜 색

	::Rectangle(mh_draw_dc, 0, 0, m_rect.Width(), m_rect.Height());			// 배경
}

void LadderWnd::OnDestroy()
{
	CWnd::OnDestroy();

	m_draw_image.ReleaseDC();				// 메모리DC 반납
	m_draw_image.Destroy();					// 이미지 객체 제거
}

void LadderWnd::OnPaint()
{
	CPaintDC dc(this);
	m_draw_image.Draw(dc, m_rect);
}
