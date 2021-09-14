
// MFCBasic124MemoryDCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic124MemoryDC.h"
#include "MFCBasic124MemoryDCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic124MemoryDCDlg dialog



CMFCBasic124MemoryDCDlg::CMFCBasic124MemoryDCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC124MEMORYDC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic124MemoryDCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic124MemoryDCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMFCBasic124MemoryDCDlg message handlers

BOOL CMFCBasic124MemoryDCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetClientRect(r);
	w = r.Width();
	h = r.Height();
	maxR = 40;
	minR = 10;

	CClientDC dc(this);
	m_mem_dc.CreateCompatibleDC(&dc);
	m_mem_bmp.CreateCompatibleBitmap(&dc, w, h);
	m_mem_dc.SelectObject(&m_mem_bmp);

	srand((unsigned int)time(NULL));
	mp = m_circleList;

	for (int i = 0; i < MAX_COUNT; ++i, ++mp) {
		mp->x = rand() % w;
		mp->y = rand() % h;
		mp->r = (rand() % maxR) + minR;
		mp->color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}

	SetTimer(1, 50, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic124MemoryDCDlg::OnPaint()
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
		
		dc.BitBlt(0, 0, w, h, &m_mem_dc, 0, 0, SRCCOPY);
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic124MemoryDCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic124MemoryDCDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		mp = m_circleList;
		p_oldBrush = m_mem_dc.GetCurrentBrush();

		m_mem_dc.FillSolidRect(0, 0, w, h, RGB(220, 220, 220));

		for (int i = 0; i < MAX_COUNT; ++i, ++mp) {
			mp->r--;
			if (mp->r == 0) {
				mp->x = rand() % w;
				mp->y = rand() % h;
				mp->r = (rand() % maxR) + minR;
				mp->color = RGB(rand() % 256, rand() % 256, rand() % 256);
			}
		fill_brush.CreateSolidBrush(mp->color);
		m_mem_dc.SelectObject(&fill_brush);
		m_mem_dc.Ellipse(mp->x - mp->r, mp->y - mp->r, mp->x + mp->r, mp->y + mp->r);
		fill_brush.DeleteObject();
		}
		m_mem_dc.SelectObject(p_oldBrush);
		Invalidate(FALSE);
	}
	//CDialogEx::OnTimer(nIDEvent);
}


void CMFCBasic124MemoryDCDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);

	m_mem_bmp.DeleteObject();
	m_mem_dc.DeleteDC();
}


// 대화상자 크기변경
void CMFCBasic124MemoryDCDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if ((cx != w || cy != h) && w && h) {
		w = cx;
		h = cy;
		m_mem_bmp.DeleteObject();

		CClientDC dc(this);
		m_mem_bmp.CreateCompatibleBitmap(&dc, w, h);
		m_mem_dc.SelectObject(&m_mem_bmp);
	}
}
