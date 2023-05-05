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

	// �۲�
	m_font = ::CreateFont(18, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH || FF_SWISS, _T("���� ���"));
	::SelectObject(mh_draw_dc, m_font);										// �۲��� �޸�DC�� �ݿ�
	::SetTextColor(mh_draw_dc, RGB(128, 202, 128));					// ����� ���ڿ��� ����
	::SetBkMode(mh_draw_dc, TRANSPARENT);								// ���ڹ�� ����

	MyDraw();
	return 0;
}

const TCHAR* gp_name_table[MEMBER_COUNT] = { _T("ù��°"), _T("�ι�°"), _T("����°"), _T("�׹�°"), _T("�ټ���°")};
const UINT8 g_name_table_len[MEMBER_COUNT] = { 3, 3, 3, 3, 4 };
const TCHAR* gp_result_table[MEMBER_COUNT] = { _T("��"), _T("ġŲ"), _T("����"), _T("��"), _T("�ݶ�")};
const UINT8 g_result_table_len[MEMBER_COUNT] = { 1,2,2,1,2 };

// �̹��� ��ü�� �׸� �׸���
void LadderWnd::MyDraw()
{
	::SetDCBrushColor(mh_draw_dc, RGB(82, 97, 124));			// �귯�� ��
	::SetDCBrushColor(mh_draw_dc, RGB(82, 97, 124));			// �� ��

	::Rectangle(mh_draw_dc, 0, 0, m_rect.Width(), m_rect.Height());			// ��� �簢��

	::SetDCBrushColor(mh_draw_dc, RGB(72, 87, 114));			// �귯�� ��
	::SetDCPenColor(mh_draw_dc, RGB(122, 137, 164));			// �� ��

	RECT name_rect = {20, 20, 80, 50};				// ���� �̸� �簢���� ��ġ
	RECT result_rect = { 20, 350, 80, 380 };				// ��ħ ��ġ

	// ������ �̵��ϸ鼭 �簢�� �� 5�� �׸�
	for (int i = 0; i < MEMBER_COUNT; i++)
	{
		// ���� �ڽ�
		::Rectangle(mh_draw_dc, name_rect.left, name_rect.top, name_rect.right, name_rect.bottom);
		::DrawText(mh_draw_dc, gp_name_table[i], g_name_table_len[i], &name_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);			// ���� �߾�
		name_rect.left += 85;
		name_rect.right += 85;

		// ��ħ �ڽ�
		::Rectangle(mh_draw_dc, result_rect.left, result_rect.top, result_rect.right, result_rect.bottom);
		::DrawText(mh_draw_dc, gp_result_table[i], g_result_table_len[i], &result_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);			// ���� �߾�
		result_rect.left += 85;
		result_rect.right += 85;
	}

	// ��ٸ� �� 5��
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

	m_draw_image.ReleaseDC();				// �޸�DC �ݳ�
	m_draw_image.Destroy();					// �̹��� ��ü ����
	
	::DeleteObject(m_font);						// �۲� ����
}

void LadderWnd::OnPaint()
{
	CPaintDC dc(this);
	m_draw_image.Draw(dc, m_rect);
}
