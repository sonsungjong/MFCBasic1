
// MFCL108ProgressCtrlDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL108ProgressCtrl.h"
#include "MFCL108ProgressCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL108ProgressCtrlDlg dialog



CMFCL108ProgressCtrlDlg::CMFCL108ProgressCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL108PROGRESSCTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL108ProgressCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress1);
}

BEGIN_MESSAGE_MAP(CMFCL108ProgressCtrlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCL108ProgressCtrlDlg message handlers

BOOL CMFCL108ProgressCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//GetDlgItem(IDC_USER_RECT)->GetWindowRect(m_user_rect);
	//ScreenToClient(m_user_rect);					// 좌표시작점 변경
	m_my_progress.Create(this, IDC_USER_RECT);
	m_my_progress.SetColor(RGB(160, 50, 0), RGB(255, 220, 0));
	SetTimer(1, 50, nullptr);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL108ProgressCtrlDlg::OnPaint()
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
		//int degree = m_progress1.GetPos() *200/100;
		//dc.FillSolidRect(degree, 0, 200, 30, RGB(0, 80, 160));
		//dc.FillSolidRect(0, 0, degree, 30, RGB(0, 160, 255));

		//degree = m_progress1.GetPos() * m_user_rect.Width()/100;

		//dc.FillSolidRect(m_user_rect.left + degree, m_user_rect.top, m_user_rect.Width(), m_user_rect.Height(), RGB(0, 80, 160));
		//dc.FillSolidRect(m_user_rect.left, m_user_rect.top, degree, m_user_rect.Height(), RGB(0, 160, 255));
		m_my_progress.Draw(&dc);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCL108ProgressCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL108ProgressCtrlDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		int degree = m_progress1.GetPos();
		degree = (degree + 1) % 101;
		m_progress1.SetPos(degree);
		m_my_progress.SetPos(degree);
		//InvalidateRect(CRect(0, 0, 200, 30), 0);
		m_my_progress.Update(this);
	}

	else CDialogEx::OnTimer(nIDEvent);
}


void CMFCL108ProgressCtrlDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);
}
