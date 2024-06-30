
// MFCS003CTaskDialog3ProgressBarDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCS003CTaskDialog3ProgressBar.h"
#include "MFCS003CTaskDialog3ProgressBarDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCS003CTaskDialog3ProgressBarDlg dialog



CMFCS003CTaskDialog3ProgressBarDlg::CMFCS003CTaskDialog3ProgressBarDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCS003CTASKDIALOG3PROGRESSBAR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCS003CTaskDialog3ProgressBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCS003CTaskDialog3ProgressBarDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCS003CTaskDialog3ProgressBarDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCS003CTaskDialog3ProgressBarDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMFCS003CTaskDialog3ProgressBarDlg message handlers

BOOL CMFCS003CTaskDialog3ProgressBarDlg::OnInitDialog()
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

void CMFCS003CTaskDialog3ProgressBarDlg::OnPaint()
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
HCURSOR CMFCS003CTaskDialog3ProgressBarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCS003CTaskDialog3ProgressBarDlg::OnBnClickedOk()
{
	TaskDialogProgressBar task_dlg;
	task_dlg.DoModal();
}


void CMFCS003CTaskDialog3ProgressBarDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}
