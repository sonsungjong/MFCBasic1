
// MFCBasic215SineDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic215Sine.h"
#include "MFCBasic215SineDlg.h"
#include "afxdialogex.h"
#include <cmath>

#define PI 3.141592

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic215SineDlg dialog



CMFCBasic215SineDlg::CMFCBasic215SineDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC215SINE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic215SineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic215SineDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCBasic215SineDlg message handlers

BOOL CMFCBasic215SineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetClientRect(m_rect);
	m_center = m_rect.CenterPoint();

	// 색깔
	SetBackgroundColor(RGB(0, 0, 0));
	m_grid_pen.CreatePen(PS_DOT, 1, RGB(168, 168, 168));
	m_sine_pen.CreatePen(PS_SOLID, 2, RGB(0, 200, 255));

	// 34:55
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic215SineDlg::OnPaint()
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
//		CDialogEx::OnPaint();
		CPen* p_old_pen = dc.SelectObject(&m_grid_pen);
		dc.SetBkMode(TRANSPARENT);

		dc.MoveTo(m_center.x, 0);																// 시작점
		dc.LineTo(m_center.x, m_rect.bottom);											// 끝점

		dc.MoveTo(0, m_center.y);											// 시작점
		dc.LineTo(m_rect.right, m_center.y);							// 끝점

		dc.SelectObject(&m_sine_pen);

		int degree, x, y;
		double radian;
		for (x = 0; x < m_rect.right; x++) {
			degree = x - m_center.x;
			radian = degree * (PI / 180);						// degree를 radian으로 변경하는 공식

			y = (int)(sin(radian)*-100) + m_center.y;							// 눈에 잘보이게 100배 증폭

			if (x) dc.LineTo(x, y);
			else dc.MoveTo(x, y);				// x == 0 : 시작점

		}
		dc.SelectObject(p_old_pen);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic215SineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic215SineDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	m_grid_pen.DeleteObject();
	m_sine_pen.DeleteObject();
}
