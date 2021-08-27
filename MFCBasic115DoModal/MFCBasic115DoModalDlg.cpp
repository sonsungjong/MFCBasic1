
// MFCBasic115DoModalDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic115DoModal.h"
#include "MFCBasic115DoModalDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic115DoModalDlg dialog



CMFCBasic115DoModalDlg::CMFCBasic115DoModalDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC115DOMODAL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic115DoModalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic115DoModalDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SHOW_DLG_BTN, &CMFCBasic115DoModalDlg::OnBnClickedShowDlgBtn)
	ON_BN_CLICKED(IDC_SHOW_NUM_DLG, &CMFCBasic115DoModalDlg::OnBnClickedShowNumDlg)
END_MESSAGE_MAP()


// CMFCBasic115DoModalDlg message handlers

BOOL CMFCBasic115DoModalDlg::OnInitDialog()
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

void CMFCBasic115DoModalDlg::OnPaint()
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
HCURSOR CMFCBasic115DoModalDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 대화상자 오픈
void CMFCBasic115DoModalDlg::OnBnClickedShowDlgBtn()
{
	Dialog1 dialog1;			// 리소스에서 다이얼로그 추가 후 클래스 추가하여 제작
	dialog1.DoModal();		// 정형대화상자 실행
}

// 대화상자간 데이터 전달
void CMFCBasic115DoModalDlg::OnBnClickedShowNumDlg()
{
	int num = GetDlgItemInt(IDC_PARENT_EDIT);
	Dialog2 dialog2;
	dialog2.SetNum(num);			// dialog2의 변수에 백업
	int result = dialog2.DoModal();

	if (result == IDOK) {
		num = dialog2.GetNum();
		SetDlgItemInt(IDC_PARENT_EDIT, num);
	}
}
