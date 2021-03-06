
// MFCBasic110LButtonDownDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic110LButtonDown.h"
#include "MFCBasic110LButtonDownDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic110LButtonDownDlg dialog


// 梓端 持失切
CMFCBasic110LButtonDownDlg::CMFCBasic110LButtonDownDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC110LBUTTONDOWN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_rect.SetRect(10, 10, 100, 100);
}

void CMFCBasic110LButtonDownDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic110LButtonDownDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMFCBasic110LButtonDownDlg message handlers

BOOL CMFCBasic110LButtonDownDlg::OnInitDialog()
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

void CMFCBasic110LButtonDownDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if (IsIconic())			// 置社鉢
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
HCURSOR CMFCBasic110LButtonDownDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic110LButtonDownDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// if(m_rect.PtInRect(point))
	if (point.x >= m_rect.left && point.y >= m_rect.top &&
		point.x <= m_rect.right && point.y <= m_rect.bottom) 
	{
		m_is_clicked = 1;
		m_prev_pos = point;
		SetCapture();			// 原酔什亜 込嬢蟹亀 五獣走研 域紗 左鎧捜
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCBasic110LButtonDownDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked == 1) {
		m_is_clicked = 0;
		ReleaseCapture();		// SetCapture 敗呪研 背薦
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCBasic110LButtonDownDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked == 1) {
		// CPoint move_pos = point - m_prev_pos;
		CPoint move_pos;
		move_pos.x = point.x - m_prev_pos.x;
		move_pos.y = point.y - m_prev_pos.y;
		
		m_rect.left += move_pos.x;
		m_rect.top += move_pos.y;
		m_rect.right += move_pos.x;
		m_rect.bottom += move_pos.y;

		m_prev_pos = point;

		Invalidate();
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
