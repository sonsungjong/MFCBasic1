
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
	srand((unsigned int)time(NULL));
	mp = m_circleList;

	for (int i = 0; i < MAX_COUNT; ++i, ++mp) {
		mp->x = rand() % w;
		mp->y = rand() % h;
		mp->r = (rand() % maxR) + minR;
		mp->color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}

	SetTimer(1, 200, NULL);

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
		mp = m_circleList;
		p_oldBrush = dc.GetCurrentBrush();
		for (int i = 0; i < MAX_COUNT; i++, mp++) {
			fill_brush.CreateSolidBrush(mp->color);
			dc.SelectObject(&fill_brush);

			dc.Ellipse(mp->x - mp->r, mp->y - mp->r, mp->x + mp->r, mp->y + mp->r);
			fill_brush.DeleteObject();
		}
		dc.SelectObject(p_oldBrush);
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
		w = r.Width();
		h = r.Height();
		mp = m_circleList;
		for (int i = 0; i < MAX_COUNT; ++i, ++mp) {
			mp->r--;
			if (mp->r == 0) {
				mp->x = rand() % w;
				mp->y = rand() % h;
				mp->r = (rand() % maxR) + minR;
				mp->color = RGB(rand() % 256, rand() % 256, rand() % 256);
			}
		}
		Invalidate();
	}
	//CDialogEx::OnTimer(nIDEvent);
}


void CMFCBasic124MemoryDCDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);
}
