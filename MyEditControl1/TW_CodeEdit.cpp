// TW_CodeEdit.cpp : implementation file
//

#include "pch.h"
#include "MyEditControl1.h"
#include "TW_CodeEdit.h"


// TW_CodeEdit

IMPLEMENT_DYNAMIC(TW_CodeEdit, CWnd)

TW_CodeEdit::TW_CodeEdit()
{

}

TW_CodeEdit::~TW_CodeEdit()
{
}


BEGIN_MESSAGE_MAP(TW_CodeEdit, CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// TW_CodeEdit message handlers




int TW_CodeEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	mh_font = ::CreateFont(0xFFFFFFEB, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Consolas"));

	RECT r;
	::GetClientRect(m_hWnd, &r);
	m_mem_image.Create(r.right-r.left, r.bottom-r.top, 32);
	mh_mem_dc = m_mem_image.GetDC();

	SetBkMode(mh_mem_dc, TRANSPARENT);
	SelectObject(mh_mem_dc, GetStockObject(DC_BRUSH));
	SelectObject(mh_mem_dc, GetStockObject(DC_PEN));
	SetDCBrushColor(mh_mem_dc, RGB(0, 0, 0));
	SelectObject(mh_mem_dc, mh_font);

	return 0;
}


void TW_CodeEdit::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: Add your message handler code here
	m_mem_image.ReleaseDC();
	m_mem_image.Destroy();
	DeleteObject(mh_font);
}


void TW_CodeEdit::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CWnd::OnPaint() for painting messages
	m_mem_image.Draw(dc, 0, 0);
}


void TW_CodeEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	WORD key_data = 0;
	GetKeyboardState(m_key_state);					// 현재 입력한 키보드 상태를 집어넣음
	ToAscii(nChar, MAKELPARAM(nRepCnt, nFlags), m_key_state, &key_data, 0);
	if (key_data) {
		Rectangle(mh_mem_dc, 0, 0, m_mem_image.GetWidth(), m_mem_image.GetHeight());
		CString str;
		str.Format(_T("%c"), (int)key_data);
		m_str += str;
		SetTextColor(mh_mem_dc, RGB(255, 255, 0));
		TextOut(mh_mem_dc, 3, 2, m_str, m_str.GetLength());
		Invalidate(0);
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
