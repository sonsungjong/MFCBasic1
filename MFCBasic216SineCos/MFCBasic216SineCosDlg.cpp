
// MFCBasic216SineCosDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic216SineCos.h"
#include "MFCBasic216SineCosDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic216SineCosDlg dialog



CMFCBasic216SineCosDlg::CMFCBasic216SineCosDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC216SINECOS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic216SineCosDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic216SineCosDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCBasic216SineCosDlg message handlers

BOOL CMFCBasic216SineCosDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetClientRect(m_rect);
	m_center_pos = m_rect.CenterPoint();

	m_image.Create(m_rect.Width(), m_rect.Height(), 32, 0);
	m_image_dc.Attach(m_image.GetDC());				// HDC -> CDC

	SetBackgroundColor(RGB(0, 0, 0));

	m_grid_pen.CreatePen(PS_DOT, 1, RGB(168, 168, 168));
	m_sine_pen.CreatePen(PS_SOLID, 2, RGB(0, 200, 255));
	m_cos_pen.CreatePen(PS_SOLID, 2, RGB(100, 255, 100));

	m_red_brush.CreateSolidBrush(RGB(255, 0, 0));
	m_green_brush.CreateSolidBrush(RGB(0, 200, 0));
	m_image_dc.SelectObject(&m_red_brush);

	SetTimer(1, 10, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic216SineCosDlg::OnPaint()
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
HCURSOR CMFCBasic216SineCosDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCBasic216SineCosDlg::ShowGrid()
{
	m_image_dc.SelectObject(&m_grid_pen);

	m_image_dc.MoveTo(m_center_pos.x, 0);
	m_image_dc.LineTo(m_center_pos.x, m_rect.bottom);

	m_image_dc.MoveTo(0, m_center_pos.y);
	m_image_dc.LineTo(m_rect.right, m_center_pos.y);
}

void CMFCBasic216SineCosDlg::ShowSine()
{
	m_image_dc.SelectObject(&m_sine_pen);

	int degree, x, y;
	double radian;
	for (x = 0; x < m_step; x++) {
		degree = x - m_center_pos.x;
		radian = degree * PI / 180;
		y = (int)(sin(radian) * -100) + m_center_pos.y;
		if (x) m_image_dc.LineTo(x, y);
		else m_image_dc.MoveTo(x, y);
	}
	m_image_dc.SelectObject(&m_red_brush);
	m_image_dc.Ellipse(x - 20, y - 20, x + 20, y + 20);
}

void CMFCBasic216SineCosDlg::ShowCos()
{
	m_image_dc.SelectObject(&m_cos_pen);

	int degree, x, y;
	double radian;
	for (x = 0; x < m_step; x++) {
		degree = x - m_center_pos.x;
		radian = degree * PI / 180;
		y = (int)(cos(radian) * -100) + m_center_pos.y;
		if (x) m_image_dc.LineTo(x, y);
		else m_image_dc.MoveTo(x, y);
	}
	m_image_dc.SelectObject(&m_green_brush);
	m_image_dc.Ellipse(x - 20, y - 20, x + 20, y + 20);
}

void CMFCBasic216SineCosDlg::ShowYCos()
{
	m_image_dc.SelectObject(&m_cos_pen);

	int degree, x, y;
	double radian;
	for (y = 0; y < m_step; y++) {
		degree = y - m_center_pos.y;
		radian = degree * PI / 180;
		x = (int)(cos(radian) * 100) + m_center_pos.x;
		if (y) m_image_dc.LineTo(x, y);
		else m_image_dc.MoveTo(x, y);
	}
	m_image_dc.SelectObject(&m_green_brush);
	m_image_dc.Ellipse(x - 20, y - 20, x + 20, y + 20);
}

void CMFCBasic216SineCosDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1)
	{
		if (m_step < m_rect.right) m_step++;
		else m_step = 1;

		m_image_dc.FillSolidRect(m_rect, RGB(0, 0, 0));

		ShowGrid();
		ShowSine();
		//ShowCos();
		ShowYCos();

		Invalidate(FALSE);
	}
	else CDialogEx::OnTimer(nIDEvent);
}


void CMFCBasic216SineCosDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);

	m_grid_pen.DeleteObject();
	m_sine_pen.DeleteObject();
	m_red_brush.DeleteObject();

	m_image_dc.Detach();
	m_image.ReleaseDC();
}
