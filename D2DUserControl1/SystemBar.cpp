// SystemBar.cpp : implementation file
//

#include "pch.h"
#include "D2DUserControl1.h"
#include "SystemBar.h"


// SystemBar

IMPLEMENT_DYNAMIC(SystemBar, CWnd)

SystemBar::SystemBar()
{

}

SystemBar::~SystemBar()
{
}


BEGIN_MESSAGE_MAP(SystemBar, CWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// SystemBar message handlers




void SystemBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	GetParent()->DestroyWindow();

	CWnd::OnLButtonDown(nFlags, point);
}


int SystemBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}
