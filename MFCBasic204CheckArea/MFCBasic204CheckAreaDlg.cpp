
// MFCBasic204CheckAreaDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic204CheckArea.h"
#include "MFCBasic204CheckAreaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic204CheckAreaDlg dialog



CMFCBasic204CheckAreaDlg::CMFCBasic204CheckAreaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC204CHECKAREA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_brush.CreateSolidBrush(RGB(0, 80, 200));
	m_select_brush.CreateSolidBrush(RGB(0, 200, 255));
	m_pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 128));
	m_select_pen.CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
}

void CMFCBasic204CheckAreaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic204CheckAreaDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMFCBasic204CheckAreaDlg message handlers

BOOL CMFCBasic204CheckAreaDlg::OnInitDialog()
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

void CMFCBasic204CheckAreaDlg::OnPaint()
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
		//CDialogEx::OnPaint();
		mp_old_brush = dc.SelectObject(&m_brush);
		mp_old_pen = dc.SelectObject(&m_pen);

		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 6; x++)
			{
				dc.Rectangle(x*100, y*100, 101+x*100, 101+y*100);
			}
		}
		
		if (m_idx_x != -1 && m_idx_y != -1) {
			dc.SelectObject(&m_select_brush);
			dc.SelectObject(&m_select_pen);
			dc.Rectangle(m_idx_x * 100, m_idx_y*100, 101 + m_idx_x * 100, 101 + m_idx_y * 100);
		}

		dc.SelectObject(mp_old_brush);		// 복구
		dc.SelectObject(mp_old_pen);			// 복구
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic204CheckAreaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic204CheckAreaDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (point.y >= 300 || point.x >= 600) {
		m_idx_x = -1;
		m_idx_y = -1;
	}

	for (int i = 0; i < 6; i++) {
		if (point.x < 100 + i * 100) {
			m_idx_x = i;
			break;
		}
	}
	for (int j = 0; j < 3; j++) {
		if (point.y < 100 + j * 100) {
			m_idx_y = j;
			break;
		}
	}
		
	Invalidate();
	

	CDialogEx::OnLButtonDown(nFlags, point);
}
