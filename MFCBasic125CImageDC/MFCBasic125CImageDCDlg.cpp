
// MFCBasic125CImageDCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic125CImageDC.h"
#include "MFCBasic125CImageDCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic125CImageDCDlg dialog



CMFCBasic125CImageDCDlg::CMFCBasic125CImageDCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC125CIMAGEDC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic125CImageDCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic125CImageDCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMFCBasic125CImageDCDlg message handlers

BOOL CMFCBasic125CImageDCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// 대화상자 크기가져오기
	CRect r;
	GetClientRect(r);
	// CImage를 통해 깜빡거림 제거하기
	m_memView.Create(r.Width(), r.Height(), 32);

	// 랜덤발생
	srand((unsigned int)time(NULL));
	
	for (int i = 0; i < MAX_COUNT; ++i) {
		m_circleList[i].x = rand() % m_memView.GetWidth();
		m_circleList[i].y = rand() % m_memView.GetHeight();
		m_circleList[i].r = (rand() % 40) + 10;
		m_circleList[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}

	SetTimer(1, 50, NULL);				// ID: 1번

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic125CImageDCDlg::OnPaint()
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
		m_memView.Draw(dc, 0, 0);

		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic125CImageDCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic125CImageDCDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		HDC h_dc = m_memView.GetDC();
		CDC* p_dc = CDC::FromHandle(h_dc);

		m_circlePos = m_circleList;
		CBrush fill_brush, *p_oldBrush = p_dc->GetCurrentBrush();
		p_dc->FillSolidRect(0, 0, m_memView.GetWidth(), m_memView.GetHeight(), RGB(220, 220, 220));
		
		for(int i=0; i<MAX_COUNT; i++){
			m_circlePos->r--;
			if (m_circlePos->r == 0) {
				m_circlePos->x = rand() % m_memView.GetWidth();
				m_circlePos->y = rand() % m_memView.GetHeight();
				m_circlePos->r = rand() % 40 + 10;
				m_circlePos->color = RGB(rand() % 256, rand() % 256, rand() % 256);
			}

			fill_brush.CreateSolidBrush(m_circlePos->color);
			p_dc->SelectObject(&fill_brush);
			p_dc->Ellipse(m_circlePos->x - m_circlePos->r, m_circlePos->y - m_circlePos->r, 
				m_circlePos->x + m_circlePos->r, m_circlePos->y + m_circlePos->r);
			fill_brush.DeleteObject();
			m_circlePos++;
		}
		p_dc->SelectObject(p_oldBrush);
		m_memView.ReleaseDC();
		Invalidate(FALSE);
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}
}

void CMFCBasic125CImageDCDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);

}

void CMFCBasic125CImageDCDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (!m_memView.IsNull()) {
		m_memView.Destroy();
		m_memView.Create(cx, cy, 32);
	}
}
