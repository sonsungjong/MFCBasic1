
// MyEditControl1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MyEditControl1.h"
#include "MyEditControl1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyEditControl1Dlg dialog



CMyEditControl1Dlg::CMyEditControl1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYEDITCONTROL1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyEditControl1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyEditControl1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMyEditControl1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMyEditControl1Dlg::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMyEditControl1Dlg message handlers

BOOL CMyEditControl1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	RECT r;
	GetDlgItem(IDC_EDIT_RECT)->GetWindowRect(&r);

	ScreenToClient(&r);

	m_code_edit.CreateEx(WS_EX_STATICEDGE, NULL, NULL, WS_CHILD | WS_VISIBLE, r, this, 23001);
	m_code_edit.SetFocus();

	return FALSE;  // return TRUE  unless you set the focus to a control -> FALSE·Î ¹Ù²ã¾ß Æ÷Ä¿½º¸¦ ¾È»°³¦
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyEditControl1Dlg::OnPaint()
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
HCURSOR CMyEditControl1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyEditControl1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMyEditControl1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();
}


void CMyEditControl1Dlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	DestroyWindow();

	CDialogEx::OnClose();
}


void CMyEditControl1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	m_code_edit.DestroyWindow();
	//MessageBox(_T("he"), _T("he"), MB_OK);
}
