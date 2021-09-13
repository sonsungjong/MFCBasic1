
// MFCBasic123Timer2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic123Timer2.h"
#include "MFCBasic123Timer2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic123Timer2Dlg dialog



CMFCBasic123Timer2Dlg::CMFCBasic123Timer2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC123TIMER2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic123Timer2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic123Timer2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCBasic123Timer2Dlg message handlers

BOOL CMFCBasic123Timer2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// 대화상자의 좌표를 얻기
	CRect r;
	GetClientRect(r);
	w = r.Width();
	h = r.Height();
	srand((unsigned int)time(NULL));

	for (int i = 0; i < MAX_COUNT; i++) {
		m_circleList[i].x = rand() % w;
		m_circleList[i].y = rand() % h;
		m_circleList[i].r = rand() % 40 + 10;			// 최대크기를 49, 최소크기를 10
		m_circleList[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}

	SetTimer(1, 200, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic123Timer2Dlg::OnPaint()
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
		CBrush fill_brush;
		CBrush* p_oldBrush = dc.GetCurrentBrush();
		//CircleData* p = m_circleList;
		for (int i = 0; i < MAX_COUNT; i++) {
			fill_brush.CreateSolidBrush(m_circleList[i].color);
			dc.SelectObject(&fill_brush);
			//p_oldBrush = dc.SelectObject(&fill_brush);

			dc.Ellipse(m_circleList[i].x - m_circleList[i].r, m_circleList[i].y - m_circleList[i].r,
				m_circleList[i].x + m_circleList[i].r, m_circleList[i].y + m_circleList[i].r);
			//dc.Ellipse(p->x - p->r, p->y - p->r, p->x + p->r, p->y + p->r);
			//p++;

			//dc.SelectObject(p_oldBrush);
			fill_brush.DeleteObject();
		}
		dc.SelectObject(p_oldBrush);
		//CDialogEx::OnPaint();			 중복제거
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic123Timer2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic123Timer2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		CRect r;
		GetClientRect(r);
		int w = r.Width(), h = r.Height();
		for (int i = 0; i < MAX_COUNT; ++i) {
			m_circleList[i].r--;
			if (m_circleList[i].r == 0) {
				m_circleList[i].x = rand() % w;
				m_circleList[i].y = rand() % h;
				m_circleList[i].r = rand() % 40 + 10;
				m_circleList[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
			}
		}
		Invalidate();
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}
}



void CMFCBasic123Timer2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);
}
