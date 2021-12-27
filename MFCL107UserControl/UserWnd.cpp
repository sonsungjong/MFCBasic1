// UserWnd.cpp : implementation file
//

#include "pch.h"
#include "MFCL107UserControl.h"
#include "UserWnd.h"


// UserWnd

IMPLEMENT_DYNAMIC(UserWnd, CWnd)

UserWnd::UserWnd()
{

}

UserWnd::~UserWnd()
{
}


BEGIN_MESSAGE_MAP(UserWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// UserWnd message handlers




void UserWnd::OnPaint()
{
	CPaintDC dc(this);

	CRect r;
	GetClientRect(r);
	dc.FillSolidRect(r, RGB(0,0,255));
}


void UserWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect r;
	r.SetRect(point.x - 10, point.y - 10, point.x + 10, point.y + 10);

	CClientDC dc(this);
	dc.FillSolidRect(r, RGB(255, 0, 0));

	CWnd::OnLButtonDown(nFlags, point);
}
