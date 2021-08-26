
// MFCBasic113ALPHADlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic113ALPHA.h"
#include "MFCBasic113ALPHADlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic113ALPHADlg dialog



CMFCBasic113ALPHADlg::CMFCBasic113ALPHADlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC113ALPHA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic113ALPHADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic113ALPHADlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMFCBasic113ALPHADlg message handlers

BOOL CMFCBasic113ALPHADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// Layered 속성을 True로 변경한 후 작업
	SetLayeredWindowAttributes(0, 255, LWA_ALPHA);			// 투명도 조절
	// SetLayeredWindowAttributes(RGB(255, 1, 7), 0, LWA_COLORKEY);			// 해당 색상을 투명화

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic113ALPHADlg::OnPaint()
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
		dc.FillSolidRect(10, 10, 200, 200, RGB(255, 1, 7));
		
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic113ALPHADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic113ALPHADlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	int wnd_style = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if (!(wnd_style & WS_EX_LAYERED)) {
		::SetWindowLong(m_hWnd, GWL_EXSTYLE, wnd_style | WS_EX_LAYERED);
	}

	SetLayeredWindowAttributes(RGB(255, 1, 7), 0, LWA_COLORKEY);

	CDialogEx::OnLButtonDown(nFlags, point);
}
