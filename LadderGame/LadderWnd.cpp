#include "pch.h"
#include "LadderGameDlg.h"				// �θ� ���̾�α� �����ϱ�
#include "LadderWnd.h"						// �ڽ��� ���

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

// �޽��� ó����
int LadderWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) { return -1; }
	GetClientRect(m_rect);			// �׸��� �׸� ����

	// �̹��� ��ü ����
	m_draw_image.Create(m_rect.Width(), m_rect.Height(), 32);
	mh_draw_dc = m_draw_image.GetDC();				// �޸� DC

	// ���� �����Ͽ� ��� �귯�� ����
	::SelectObject(mh_draw_dc, ::GetStockObject(DC_BRUSH));
	::SelectObject(mh_draw_dc, ::GetStockObject(DC_PEN));

	MyDraw();
	return 0;
}

// �̹��� ��ü�� �׸� �׸���
void LadderWnd::MyDraw()
{
	::SetDCBrushColor(mh_draw_dc, RGB(0, 0, 0));			// �귯�� ��
	::SetDCBrushColor(mh_draw_dc, RGB(0, 0, 0));			// �� ��

	::Rectangle(mh_draw_dc, 0, 0, m_rect.Width(), m_rect.Height());			// ���
}

void LadderWnd::OnDestroy()
{
	CWnd::OnDestroy();

	m_draw_image.ReleaseDC();				// �޸�DC �ݳ�
	m_draw_image.Destroy();					// �̹��� ��ü ����
}

void LadderWnd::OnPaint()
{
	CPaintDC dc(this);
	m_draw_image.Draw(dc, m_rect);
}
