
// MFCBasic115Dialog1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic115Dialog1.h"
#include "MFCBasic115Dialog1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic115Dialog1Dlg dialog



CMFCBasic115Dialog1Dlg::CMFCBasic115Dialog1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC115DIALOG1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic115Dialog1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic115Dialog1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SHOW_DLG_BTN, &CMFCBasic115Dialog1Dlg::OnBnClickedShowDlgBtn)
END_MESSAGE_MAP()


// CMFCBasic115Dialog1Dlg message handlers

BOOL CMFCBasic115Dialog1Dlg::OnInitDialog()
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

void CMFCBasic115Dialog1Dlg::OnPaint()
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
HCURSOR CMFCBasic115Dialog1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include "NewDlg.h"

void CMFCBasic115Dialog1Dlg::OnBnClickedShowDlgBtn()
{
	// 새 대화상자의 클래스 만들기 (새 대화상자 더블클릭) --> include "헤더파일"
	NewDlg ins_dlg;
	ins_dlg.DoModal();
	// 12:30
}
