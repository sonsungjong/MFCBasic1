
// MFCS004LineGraphDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCS004LineGraph.h"
#include "MFCS004LineGraphDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCS004LineGraphDlg dialog



CMFCS004LineGraphDlg::CMFCS004LineGraphDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCS004LINEGRAPH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Gdiplus::GdiplusStartup(&m_gdiplus_token, &m_gdiplus_startup_input, NULL);
}

void CMFCS004LineGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCS004LineGraphDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCS004LineGraphDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCS004LineGraphDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMFCS004LineGraphDlg message handlers

BOOL CMFCS004LineGraphDlg::OnInitDialog()
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

void CMFCS004LineGraphDlg::OnPaint()
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
		Gdiplus::Graphics graphics(dc.m_hDC);
		graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

		// 좌표
		Gdiplus::PointF points[] = {
			Gdiplus::PointF(10.0f, 100.0f),
			Gdiplus::PointF(50.0f, 50.0f),
			Gdiplus::PointF(100.0f, 150.0f),
			Gdiplus::PointF(150.0f, 30.0f),
			Gdiplus::PointF(200.0f, 100.0f)
		};

		// 배경채우기
		Gdiplus::GraphicsPath path;
		path.AddCurve(points, 5);
		path.AddLine(Gdiplus::PointF(200.0f, 100.0f), Gdiplus::PointF(200.0f, 200.0f));		// Right vertical line to the bottom
		path.AddLine(Gdiplus::PointF(200.0f, 200.0f), Gdiplus::PointF(10.0f, 200.0f));			// Bottom horizontal line
		path.AddLine(Gdiplus::PointF(10.0f, 200.0f), Gdiplus::PointF(10.0f, 100.0f));			// Left vertical line back to the start
		path.CloseFigure();
		Gdiplus::SolidBrush backgroundBrush(Gdiplus::Color(128, 200, 200, 255));
		graphics.FillPath(&backgroundBrush, &path);
		
		// 둥근 선그리기
		Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 255), 2.0f);
		graphics.DrawCurve(&pen, points, 5);			// 스플라인 곡선을 5개의 포인트를 펜으로 그림



		// 일반 꺾은선 그래프
		Gdiplus::Pen pen2(Gdiplus::Color(255, 255, 0, 0), 3.0f);
		Gdiplus::PointF points2[] = {
			Gdiplus::PointF(10.0f, 50.0f),
			Gdiplus::PointF(50.0f, 70.0f),
			Gdiplus::PointF(100.0f, 130.0f),
			Gdiplus::PointF(150.0f, 120.0f),
			Gdiplus::PointF(200.0f, 100.0f)
		};
		for (int i = 0; i < sizeof(points2) / sizeof(points2[0]) - 1; i++) {
			graphics.DrawLine(&pen2, points2[i], points2[i + 1]);
		}




	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCS004LineGraphDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCS004LineGraphDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCS004LineGraphDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CMFCS004LineGraphDlg::OnDestroy()
{
	Gdiplus::GdiplusShutdown(m_gdiplus_token);
	CDialogEx::OnDestroy();
}
