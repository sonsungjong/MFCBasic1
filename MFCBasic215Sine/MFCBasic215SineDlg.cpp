
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
	ON_WM_TIMER()
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

	// 메모리DC
	m_image.Create(m_rect.Width(), m_rect.Height(), 32, 0);
	m_image_dc.Attach(m_image.GetDC());					// HDC 핸들 -> CDC 객체
	// 모든 dc를 m_image_dc로 바꿔주면 됨
	// dc에 그리지않고 CImage에 그림

	// 색깔
	SetBackgroundColor(RGB(0, 0, 0));
	m_grid_pen.CreatePen(PS_DOT, 1, RGB(168, 168, 168));
	m_sine_pen.CreatePen(PS_SOLID, 2, RGB(0, 200, 255));
	m_red_brush.CreateSolidBrush(RGB(255, 0, 0));
	m_image_dc.SelectObject(&m_red_brush);

	SetTimer(1, 10, NULL);

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
		

		// dc에 출력
		m_image.Draw(dc, 0, 0);
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
	KillTimer(1);
	m_grid_pen.DeleteObject();
	m_sine_pen.DeleteObject();
	m_red_brush.DeleteObject();

	// 메모리DC 해제
	m_image_dc.Detach();
	m_image.ReleaseDC();
}


void CMFCBasic215SineDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		if (m_step < m_rect.right) m_step++;
		else m_step = 1;

		m_image_dc.FillSolidRect(m_rect, RGB(0, 0, 0));

		CPen* p_old_pen = m_image_dc.SelectObject(&m_grid_pen);
		m_image_dc.SetBkMode(TRANSPARENT);

		m_image_dc.MoveTo(m_center.x, 0);																// 시작점
		m_image_dc.LineTo(m_center.x, m_rect.bottom);											// 끝점

		m_image_dc.MoveTo(0, m_center.y);											// 시작점
		m_image_dc.LineTo(m_rect.right, m_center.y);							// 끝점

		m_image_dc.SelectObject(&m_sine_pen);

		int degree, x, y;
		double radian;
		//for (x = 0; x < m_rect.right; x++) 
		for (x = 0; x < m_step; x++)
		{
			degree = x - m_center.x;
			radian = degree * (PI / 180);						// degree를 radian으로 변경하는 공식

			y = (int)(sin(radian) * -100) + m_center.y;							// 눈에 잘보이게 100배 증폭

			if (x) m_image_dc.LineTo(x, y);
			else m_image_dc.MoveTo(x, y);				// x == 0 : 시작점
		}

		m_image_dc.Ellipse(x - 10, y - 10, x + 10, y + 10);

		m_image_dc.SelectObject(p_old_pen);

		Invalidate(FALSE);
	}

	else CDialogEx::OnTimer(nIDEvent);
}
