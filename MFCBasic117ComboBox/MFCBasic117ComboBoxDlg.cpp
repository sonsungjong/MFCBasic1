
// MFCBasic117ComboBoxDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic117ComboBox.h"
#include "MFCBasic117ComboBoxDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic117ComboBoxDlg dialog



CMFCBasic117ComboBoxDlg::CMFCBasic117ComboBoxDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC117COMBOBOX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic117ComboBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic117ComboBoxDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SHOW_BTN, &CMFCBasic117ComboBoxDlg::OnBnClickedShowBtn)
END_MESSAGE_MAP()


// CMFCBasic117ComboBoxDlg message handlers

BOOL CMFCBasic117ComboBoxDlg::OnInitDialog()
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

void CMFCBasic117ComboBoxDlg::OnPaint()
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
HCURSOR CMFCBasic117ComboBoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic117ComboBoxDlg::OnBnClickedShowBtn()
{
	// TODO: Add your control notification handler code here
	int num[11];
	CString str, total_str;

	for(int i = 0; i< sizeof(num)/sizeof(int); i++){
		num[i] = GetDlgItemInt(IDC_EDIT1 +i);

		str.Format(L"%d, ", num[i]);
		total_str += str;
	}

	SetDlgItemText(IDC_NUM_EDIT, total_str);
}
