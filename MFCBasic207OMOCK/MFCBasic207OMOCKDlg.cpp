
// MFCBasic207OMOCKDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic207OMOCK.h"
#include "MFCBasic207OMOCKDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic207OMOCKDlg dialog



CMFCBasic207OMOCKDlg::CMFCBasic207OMOCKDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC207OMOCK_DIALOG, pParent), m_grid_pen(PS_SOLID, 1, RGB(144, 90, 40))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic207OMOCKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic207OMOCKDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCBasic207OMOCKDlg::OnBnClickedOk)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMFCBasic207OMOCKDlg message handlers

BOOL CMFCBasic207OMOCKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetBackgroundColor(RGB(244, 176, 77));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic207OMOCKDlg::OnPaint()
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
		CPen* p_old_pen = dc.SelectObject(&m_grid_pen);
		for (int i = 0; i < Y_COUNT; i++)
		{
			// 수직선
			dc.MoveTo(GRID_LEN /2+i*GRID_LEN, GRID_LEN/2);
			dc.LineTo(GRID_LEN /2+i* GRID_LEN, GRID_LEN /2+(Y_COUNT-1) * GRID_LEN);
		}
		for (int i = 0; i < X_COUNT; i++)
		{
			// 수평선
			dc.MoveTo(GRID_LEN/2, GRID_LEN /2+i* GRID_LEN);
			dc.LineTo(GRID_LEN /2+(X_COUNT-1) * GRID_LEN, GRID_LEN /2+i * GRID_LEN);
		}

		dc.SelectObject(p_old_pen);
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic207OMOCKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic207OMOCKDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCBasic207OMOCKDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	int x = point.x / GRID_LEN;
	int y = point.y / GRID_LEN;		// 간격만큼 나누면 인덱스가 나옴

	if (x < X_COUNT && y < Y_COUNT) {
		CClientDC dc(this);

		CGdiObject* p_old_brush;
		CPen* p_old_pen = dc.SelectObject(&m_grid_pen);

		if (m_step == 0) p_old_brush=dc.SelectStockObject(BLACK_BRUSH);
		else p_old_brush=dc.SelectStockObject(WHITE_BRUSH);

		dc.Ellipse(x* GRID_LEN, y* GRID_LEN, x* GRID_LEN + GRID_LEN, y* GRID_LEN + GRID_LEN);
		dc.SelectObject(p_old_brush);
		dc.SelectObject(p_old_pen);
		m_step = !m_step;
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}
