
// MFCL223GdiPlus2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL223GdiPlus2.h"
#include "MFCL223GdiPlus2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL223GdiPlus2Dlg dialog



CMFCL223GdiPlus2Dlg::CMFCL223GdiPlus2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL223GDIPLUS2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL223GdiPlus2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL223GdiPlus2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL223GdiPlus2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL223GdiPlus2Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_ACCEPT_BTN, &CMFCL223GdiPlus2Dlg::OnBnClickedAcceptBtn)
END_MESSAGE_MAP()


// CMFCL223GdiPlus2Dlg message handlers

BOOL CMFCL223GdiPlus2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect r;
	GetDlgItem(IDC_GDI_RECT)->GetWindowRect(r);
	ScreenToClient(r);
	m_gdi_view.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, r, this, 26001);

	GetDlgItem(IDC_GDI_PLUS_RECT)->GetWindowRect(r);
	ScreenToClient(r);
	m_gdi_plus_view.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, r, this, 26002);

	SetDlgItemInt(IDC_RATE_EDIT, 255);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL223GdiPlus2Dlg::OnPaint()
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
HCURSOR CMFCL223GdiPlus2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL223GdiPlus2Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL223GdiPlus2Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCL223GdiPlus2Dlg::OnBnClickedAcceptBtn()
{
	m_gdi_plus_view.ChangeRate((BYTE)GetDlgItemInt(IDC_RATE_EDIT));
}
