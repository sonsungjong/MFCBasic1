
// MFCBasic223DonutWindowDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic223DonutWindow.h"
#include "MFCBasic223DonutWindowDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic223DonutWindowDlg dialog



CMFCBasic223DonutWindowDlg::CMFCBasic223DonutWindowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC223DONUTWINDOW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic223DonutWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic223DonutWindowDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMFCBasic223DonutWindowDlg message handlers

BOOL CMFCBasic223DonutWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRgn region;
	region.CreateEllipticRgn(0, 0, 200, 200);
	SetWindowRgn(region, TRUE);

	SetBackgroundColor(RGB(255, 200, 0));

	SetLayeredWindowAttributes(RGB(255, 1, 1), 80, LWA_ALPHA|LWA_COLORKEY);				// 80의 불투명도

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic223DonutWindowDlg::OnPaint()
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
		dc.SelectStockObject(DC_BRUSH);
		dc.SetDCBrushColor(RGB(255, 1, 1));
		dc.SelectStockObject(NULL_PEN);
		dc.Ellipse(30, 30, 170, 170);

		CPen grid_pen(PS_DOT, 1, RGB(0, 0, 128));
		CPen* p_oldPen = dc.SelectObject(&grid_pen);
		dc.SetBkMode(TRANSPARENT);			// 배경색을 제거
		dc.MoveTo(100, 30);
		dc.LineTo(100, 170);
		dc.MoveTo(30, 100);
		dc.LineTo(170, 100);
		dc.SelectObject(p_oldPen);
		grid_pen.DeleteObject();

		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic223DonutWindowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic223DonutWindowDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_clickFlag) {
		m_clickFlag = 1;
		GetCursorPos(&m_prevPosition);
		SetCapture();
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCBasic223DonutWindowDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_clickFlag) {
		m_clickFlag = 0;
		ReleaseCapture();
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCBasic223DonutWindowDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_clickFlag) {
		CRect rect;
		GetWindowRect(&rect);
		
		CPoint curPosition;
		GetCursorPos(&curPosition);
		SetWindowPos(NULL, rect.left + curPosition.x - m_prevPosition.x, rect.top + curPosition.y - m_prevPosition.y, 0, 0, SWP_NOSIZE);
		m_prevPosition = curPosition;
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
