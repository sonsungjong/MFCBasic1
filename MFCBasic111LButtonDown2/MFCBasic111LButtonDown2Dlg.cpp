
// MFCBasic111LButtonDown2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic111LButtonDown2.h"
#include "MFCBasic111LButtonDown2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic111LButtonDown2Dlg dialog



CMFCBasic111LButtonDown2Dlg::CMFCBasic111LButtonDown2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC111LBUTTONDOWN2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	POINT star_pos[11] = {
		{101, 0}, {77, 77}, {0, 77}, {62, 125},
		{39, 201}, {101, 153}, {163, 201}, {138, 125},
		{201, 77}, {124, 77}, {101, 0}
	};

	m_star_rgn.CreatePolygonRgn(star_pos, 11, ALTERNATE);
	m_fill_brush.CreateSolidBrush(RGB(0, 0, 0));
}

void CMFCBasic111LButtonDown2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic111LButtonDown2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMFCBasic111LButtonDown2Dlg message handlers

BOOL CMFCBasic111LButtonDown2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic111LButtonDown2Dlg::OnPaint()
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
		dc.PaintRgn(&m_star_rgn);			// 도형
		dc.FrameRgn(&m_star_rgn, &m_fill_brush, 3, 3);		// 테두리
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic111LButtonDown2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic111LButtonDown2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_star_rgn.PtInRegion(point)) {
		m_is_clicked = 1;

		if (m_is_clicked) {
			m_prev_pos = point;
			SetCapture();
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCBasic111LButtonDown2Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked) {
		m_is_clicked = 0;
		ReleaseCapture();
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCBasic111LButtonDown2Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked) {
		CPoint move_pos = point - m_prev_pos;
		m_star_rgn.OffsetRgn(move_pos);

		m_prev_pos = point;
		Invalidate();		// Paint 강제발동
	}
	CDialogEx::OnMouseMove(nFlags, point);
}
