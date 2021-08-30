
// MFCBasic116ModalessInnerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic116ModalessInner.h"
#include "MFCBasic116ModalessInnerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic116ModalessInnerDlg dialog



CMFCBasic116ModalessInnerDlg::CMFCBasic116ModalessInnerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC116MODALESSINNER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic116ModalessInnerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic116ModalessInnerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CMFCBasic116ModalessInnerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_PARENT, &CMFCBasic116ModalessInnerDlg::OnBnClickedBtnParent)
END_MESSAGE_MAP()


// CMFCBasic116ModalessInnerDlg message handlers

BOOL CMFCBasic116ModalessInnerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	mp_innerDlg1 = new InnerDlg1;
	mp_innerDlg1->Create(IDD_INNER_DLG1, this);
	mp_innerDlg1->SetWindowPos(NULL, 0, 80, 0, 0, SWP_NOSIZE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic116ModalessInnerDlg::OnPaint()
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
HCURSOR CMFCBasic116ModalessInnerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic116ModalessInnerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	if (mp_innerDlg1 != NULL) {
		delete mp_innerDlg1;
	}
}


void CMFCBasic116ModalessInnerDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCBasic116ModalessInnerDlg::OnBnClickedBtnParent()
{
	// TODO: Add your control notification handler code here
	int num = GetDlgItemInt(IDC_EDIT_PARENT);
	mp_innerDlg1->SetDlgItemInt(IDC_EDIT_CHILD, num);
}
