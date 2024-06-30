
// MFCS002CTaskDialog2AddBtnDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCS002CTaskDialog2AddBtn.h"
#include "MFCS002CTaskDialog2AddBtnDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCS002CTaskDialog2AddBtnDlg dialog

CMFCS002CTaskDialog2AddBtnDlg::CMFCS002CTaskDialog2AddBtnDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCS002CTASKDIALOG2ADDBTN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCS002CTaskDialog2AddBtnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCS002CTaskDialog2AddBtnDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCS002CTaskDialog2AddBtnDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCS002CTaskDialog2AddBtnDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMFCS002CTaskDialog2AddBtnDlg message handlers

BOOL CMFCS002CTaskDialog2AddBtnDlg::OnInitDialog()
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

void CMFCS002CTaskDialog2AddBtnDlg::OnPaint()
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
HCURSOR CMFCS002CTaskDialog2AddBtnDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCS002CTaskDialog2AddBtnDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
	//CTaskDialog dlg();
	MyUserTaskDlg task_dlg;
	task_dlg.DoModal();
}


void CMFCS002CTaskDialog2AddBtnDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
