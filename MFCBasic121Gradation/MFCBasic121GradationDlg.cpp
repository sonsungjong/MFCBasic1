
// MFCBasic121GradationDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic121Gradation.h"
#include "MFCBasic121GradationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic121GradationDlg dialog



CMFCBasic121GradationDlg::CMFCBasic121GradationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC121GRADATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic121GradationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic121GradationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMFCBasic121GradationDlg message handlers

BOOL CMFCBasic121GradationDlg::OnInitDialog()
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

void CMFCBasic121GradationDlg::OnPaint()
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
		GRADIENT_RECT rect;
		TRIVERTEX data[2];			// 시작점, 끝점
		data[0].x = 10;			// left
		data[0].y = 10;			// top
		data[1].x = 210;			// right
		data[1].y = 210;			// bottom

		data[0].Red = 0;
		data[0].Green = 128 << 8;
		data[0].Blue = 255 << 8;

		data[1].Red = 0;
		data[1].Green = 255 << 8;
		data[1].Blue = 255 << 8;

		rect.UpperLeft = 0;
		rect.LowerRight = 1;

		dc.GradientFill(data, 2, &rect, 1, GRADIENT_FILL_RECT_H);			// 수평방향 색채우기

		GradationRect(&dc, 220, 10, 420, 210, RGB(0, 128, 255), RGB(0, 255, 255), 1);			// 수직방향 그라데이션
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic121GradationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCBasic121GradationDlg::GradationRect(CDC* dc, int x1, int y1, int x2, int y2, COLORREF start_color, COLORREF end_color, int orientaion = 1)
{
	GRADIENT_RECT rect;
	TRIVERTEX data[2];			// 시작점, 끝점
	data[0].x = x1;			// left
	data[0].y = y1;			// top
	data[1].x = x2;			// right
	data[1].y = y2;			// bottom

	data[0].Red = GetRValue(start_color) << 8;
	data[0].Green = GetGValue(start_color) << 8;
	data[0].Blue = GetBValue(start_color) << 8;

	data[1].Red = GetRValue(end_color) << 8;
	data[1].Green = GetGValue(end_color) << 8;
	data[1].Blue = GetBValue(end_color) << 8;

	rect.UpperLeft = 0;
	rect.LowerRight = 1;

	dc->GradientFill(data, 2, &rect, 1, orientaion);			// orientation : 0 - 수평, 1 - 수직
}