
// MFCBasic104ScreenToClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic104ScreenToClient.h"
#include "MFCBasic104ScreenToClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic104ScreenToClientDlg dialog



CMFCBasic104ScreenToClientDlg::CMFCBasic104ScreenToClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC104SCREENTOCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic104ScreenToClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic104ScreenToClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCBasic104ScreenToClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCBasic104ScreenToClientDlg::OnBnClickedCancel)
	ON_WM_MOVE()
END_MESSAGE_MAP()


// CMFCBasic104ScreenToClientDlg message handlers

BOOL CMFCBasic104ScreenToClientDlg::OnInitDialog()
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

void CMFCBasic104ScreenToClientDlg::OnPaint()
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
HCURSOR CMFCBasic104ScreenToClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic104ScreenToClientDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCBasic104ScreenToClientDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCBasic104ScreenToClientDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: Add your message handler code here
	CRect r;
	CString str;

	GetWindowRect(r);
	str.Format(_T("시작점( %d, %d ), 끝점( %d, %d )"), r.left, r.top, r.right, r.bottom);
	SetDlgItemText(IDC_EDIT1, str);

	GetClientRect(r);
	str.Format(_T("시작점( %d, %d ), 끝점( %d, %d )"), r.left, r.top, r.right, r.bottom);
	SetDlgItemText(IDC_EDIT2, str);

	CWnd* p_btn1 = GetDlgItem(IDC_BUTTON1);
	if (p_btn1 != NULL) {
		p_btn1->GetWindowRect(r);
		str.Format(_T("시작점( %d, %d ), 끝점( %d, %d )"), r.left, r.top, r.right, r.bottom);
		SetDlgItemText(IDC_EDIT3, str);

		ScreenToClient(r);									// 기준점 변경
		str.Format(_T("시작점( %d, %d ), 끝점( %d, %d )"), r.left, r.top, r.right, r.bottom);
		SetDlgItemText(IDC_EDIT4, str);

		p_btn1->GetClientRect(r);
		str.Format(_T("시작점( %d, %d ), 끝점( %d, %d )"), r.left, r.top, r.right, r.bottom);
		SetDlgItemText(IDC_EDIT5, str);
	}
}
