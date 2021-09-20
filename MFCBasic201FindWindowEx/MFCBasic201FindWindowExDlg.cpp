
// MFCBasic201FindWindowExDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic201FindWindowEx.h"
#include "MFCBasic201FindWindowExDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic201FindWindowExDlg dialog



CMFCBasic201FindWindowExDlg::CMFCBasic201FindWindowExDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC201FINDWINDOWEX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic201FindWindowExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic201FindWindowExDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FIND_EDIT, &CMFCBasic201FindWindowExDlg::OnBnClickedFindEdit)
END_MESSAGE_MAP()


// CMFCBasic201FindWindowExDlg message handlers

BOOL CMFCBasic201FindWindowExDlg::OnInitDialog()
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

void CMFCBasic201FindWindowExDlg::OnPaint()
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
HCURSOR CMFCBasic201FindWindowExDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic201FindWindowExDlg::OnBnClickedFindEdit()
{
	// API
	HWND h_find_wnd = NULL;
	//h_find_wnd = ::FindWindowEx(m_hWnd, h_find_wnd, L"edit", NULL);
	while (h_find_wnd = ::FindWindowEx(m_hWnd, h_find_wnd, L"edit", NULL)) {
		::SetWindowText(h_find_wnd, L"Hello!");
	}

	// MFC
	CWnd find_wnd;
	HWND h_find_wnd2 = NULL;
	while (h_find_wnd2 = ::FindWindowEx(m_hWnd, h_find_wnd2, L"button", NULL)) {
		find_wnd.Attach(h_find_wnd2);
		find_wnd.SetWindowText(L"HeHe");
		find_wnd.Detach();
	}

}
