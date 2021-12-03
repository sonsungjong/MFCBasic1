
// MFCL101SubClassingDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL101SubClassing.h"
#include "MFCL101SubClassingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL101SubClassingDlg dialog



CMFCL101SubClassingDlg::CMFCL101SubClassingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL101SUBCLASSING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL101SubClassingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL101SubClassingDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INC_BTN, &CMFCL101SubClassingDlg::OnBnClickedIncBtn)
	ON_BN_CLICKED(IDC_DEC_BTN, &CMFCL101SubClassingDlg::OnBnClickedDecBtn)
END_MESSAGE_MAP()


// CMFCL101SubClassingDlg message handlers

BOOL CMFCL101SubClassingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetDlgItemInt(IDC_VALUE_EDIT, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL101SubClassingDlg::OnPaint()
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
HCURSOR CMFCL101SubClassingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// CButton 을 상속받아 기능을 추가한 새로운 클래스로 교체 == 서브클래싱
void CMFCL101SubClassingDlg::OnBnClickedIncBtn()
{
	// TODO: Add your control notification handler code here
	int value = GetDlgItemInt(IDC_VALUE_EDIT);
	SetDlgItemInt(IDC_VALUE_EDIT, value + 1);
}


void CMFCL101SubClassingDlg::OnBnClickedDecBtn()
{
	// TODO: Add your control notification handler code here
	int value = GetDlgItemInt(IDC_VALUE_EDIT);
	SetDlgItemInt(IDC_VALUE_EDIT, value - 1);
}
