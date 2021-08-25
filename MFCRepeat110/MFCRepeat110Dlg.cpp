
// MFCRepeat110Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCRepeat110.h"
#include "MFCRepeat110Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCRepeat110Dlg dialog



CMFCRepeat110Dlg::CMFCRepeat110Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCREPEAT110_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_rect.SetRect(10, 10, 100, 100);
}

void CMFCRepeat110Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCRepeat110Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMFCRepeat110Dlg message handlers

BOOL CMFCRepeat110Dlg::OnInitDialog()
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

void CMFCRepeat110Dlg::OnPaint()
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
		dc.Rectangle(m_rect);
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCRepeat110Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCRepeat110Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_rect.PtInRect(point))
	{
		m_clicked_flag = m_clicked_flag ^ 1;
		m_prev_pos = point;
		SetCapture();
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCRepeat110Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_clicked_flag = m_clicked_flag ^ m_clicked_flag;
	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCRepeat110Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_clicked_flag != 0) 
	{
		CPoint move_pos = point - m_prev_pos;

		m_rect.left += move_pos.x;
		m_rect.top += move_pos.y;
		m_rect.right += move_pos.x;
		m_rect.bottom += move_pos.y;

		m_prev_pos = point;

		Invalidate();
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
