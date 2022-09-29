
// MFCBasic104ControlPositionDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic104ControlPosition.h"
#include "MFCBasic104ControlPositionDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic104ControlPositionDlg dialog



CMFCBasic104ControlPositionDlg::CMFCBasic104ControlPositionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC104CONTROLPOSITION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic104ControlPositionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic104ControlPositionDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMFCBasic104ControlPositionDlg message handlers

BOOL CMFCBasic104ControlPositionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetDlgItem(IDC_PICTURE1)->GetWindowRect(m_btn_rect2);
	ScreenToClient(m_btn_rect2);						// 화면좌표계 -> 클라이언트 좌표계

	GetDlgItem(IDOK)->GetWindowRect(m_btn_rect);
	ScreenToClient(m_btn_rect);						// 화면좌표계 -> 클라이언트 좌표계

	int h = m_btn_rect.Height();
	m_btn_rect.top += h + 10;
	m_btn_rect.bottom += h + 10;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic104ControlPositionDlg::OnPaint()
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
		dc.Rectangle(m_btn_rect2);
		dc.Rectangle(m_btn_rect);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic104ControlPositionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

