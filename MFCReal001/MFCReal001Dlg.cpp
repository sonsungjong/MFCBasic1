
// MFCReal001Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCReal001.h"
#include "MFCReal001Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCReal001Dlg dialog



CMFCReal001Dlg::CMFCReal001Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCREAL001_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCReal001Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCReal001Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMFCReal001Dlg message handlers

BOOL CMFCReal001Dlg::OnInitDialog()
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

void CMFCReal001Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCReal001Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCReal001Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	HDC h_dc = ::GetDC(m_hWnd);

	::SelectObject(h_dc, ::GetStockObject(DC_BRUSH));
	::SetDCBrushColor(h_dc, RGB(0, 255, 0));
	::Rectangle(h_dc, point.x - 20, point.y - 20, point.x + 20 , point.y + 20);

	::ReleaseDC(m_hWnd, h_dc);
	/*CClientDC dc(this);
	dc.SelectStockObject(DC_BRUSH);
	dc.SetDCBrushColor(RGB(0, 255, 0));
	dc.Rectangle(point.x - 20, point.y - 20, point.x+20, point.y+20);

	CDialogEx::OnLButtonDown(nFlags, point);*/
}
