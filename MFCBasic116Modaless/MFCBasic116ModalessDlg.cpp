
// MFCBasic116ModalessDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic116Modaless.h"
#include "MFCBasic116ModalessDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic116ModalessDlg dialog



CMFCBasic116ModalessDlg::CMFCBasic116ModalessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC116MODALESS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic116ModalessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic116ModalessDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SHOW, &CMFCBasic116ModalessDlg::OnBnClickedBtnShow)
	ON_WM_DESTROY()
	ON_MESSAGE(44444, &CMFCBasic116ModalessDlg::On44444)
	ON_BN_CLICKED(IDC_BTN_START, &CMFCBasic116ModalessDlg::OnBnClickedBtnStart)
END_MESSAGE_MAP()


// CMFCBasic116ModalessDlg message handlers

BOOL CMFCBasic116ModalessDlg::OnInitDialog()
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

void CMFCBasic116ModalessDlg::OnPaint()
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
HCURSOR CMFCBasic116ModalessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic116ModalessDlg::OnBnClickedBtnShow()
{
	// TODO: Add your control notification handler code here
	if (mp_dialog1 == NULL) {
		mp_dialog1 = new Dialog1;
		mp_dialog1->Create(IDD_DIALOG1, this);
	}
}


void CMFCBasic116ModalessDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	if (mp_dialog1 != NULL) {
		delete mp_dialog1;
	}
}

// ???? ?????????????? ????
afx_msg LRESULT CMFCBasic116ModalessDlg::On44444(WPARAM wParam, LPARAM lParam)
{
	delete mp_dialog1;
	mp_dialog1 = NULL;
	return 0;
}

// ???????????? ?????? ????
void CMFCBasic116ModalessDlg::OnBnClickedBtnStart()
{
	// TODO: Add your control notification handler code here
	if (mp_dialog1 != NULL) {
		int num = GetDlgItemInt(IDC_EDIT_START);
		mp_dialog1->SetDlgItemInt(IDC_EDIT_NUM, num);
	}
}
