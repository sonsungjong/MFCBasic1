
// MFCBasic219Circle3Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic219Circle3.h"
#include "MFCBasic219Circle3Dlg.h"
#include "afxdialogex.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic219Circle3Dlg dialog



CMFCBasic219Circle3Dlg::CMFCBasic219Circle3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC219CIRCLE3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic219Circle3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic219Circle3Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMFCBasic219Circle3Dlg message handlers

BOOL CMFCBasic219Circle3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetClientRect(m_rect);
	m_image.Create(m_rect.Width(), m_rect.Height(), 32);
	m_image_dc.Attach(m_image.GetDC());

	m_green_pen.CreatePen(PS_SOLID, 1, RGB(100, 255, 100));
	m_green_brush.CreateSolidBrush(RGB(0, 160, 0));
	SetBackgroundColor(RGB(0, 0, 0));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic219Circle3Dlg::OnPaint()
{
		CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();
		m_image.Draw(dc, 0, 0);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic219Circle3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic219Circle3Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	m_image_dc.Detach();
	m_image.ReleaseDC();

	m_green_pen.DeleteObject();
	m_green_brush.DeleteObject();
}


void CMFCBasic219Circle3Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_is_clicked = 1;
	m_start_pos = point;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCBasic219Circle3Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_is_clicked = 0;

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCBasic219Circle3Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked == 1) {
		// 이전꺼 있으면 지우기
		m_image_dc.FillSolidRect(m_rect, RGB(0, 0, 0));

		m_image_dc.SelectObject(&m_green_pen);
		//m_image_dc.SelectStockObject(NULL_BRUSH);
		//m_image_dc.Ellipse(point.x-50, point.y-50, point.x+50, point.y+50);

		m_image_dc.MoveTo(m_start_pos);
		m_image_dc.LineTo(point);

		POINT pos_list[3];
		pos_list[0].x = point.x;
		pos_list[0].y = point.y;

		double radian = atan2(m_start_pos.y - point.y, point.x - m_start_pos.x);

		pos_list[1].x = (int)(cos(radian+5.0/6.0*PI)*50) + point.x;
		pos_list[1].y = (int)(sin(radian + 5.0 / 6.0 * PI) * -50) + point.y;

		pos_list[2].x = (int)(cos(radian + 7.0 / 6.0 * PI) * 50) + point.x;
		pos_list[2].y = (int)(sin(radian + 7.0 / 6.0 * PI) * -50) + point.y;

		m_image_dc.SelectObject(&m_green_brush);
		m_image_dc.Polygon(pos_list, 3);

		::InvalidateRect(m_hWnd, NULL, FALSE);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
