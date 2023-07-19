
// GraphBoxDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "GraphBox.h"


#include "GraphBoxDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphBoxDlg dialog



CGraphBoxDlg::CGraphBoxDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRAPHBOX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_ex = new Ex[100000];
	srand(GetTickCount64());
	Ex* p = m_ex;
	for (int i = 0; i < 100000; i++, p++) {
		p->temp = (float)(rand() % 2000 - 1000 / 100.0);
		p->humi = rand() % 51+20;
	}
}

void CGraphBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGraphBoxDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CGraphBoxDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGraphBoxDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CGraphBoxDlg message handlers

BOOL CGraphBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetDlgItem(IDC_GRAPH_RECT)->GetWindowRect(m_rect1);
	GetDlgItem(IDC_SUB_GRAPH_RECT)->GetWindowRect(m_rect2);
	GetDlgItem(IDC_PIE_GRAPH_RECT)->GetWindowRect(m_pie_rect);
	ScreenToClient(m_rect1);
	ScreenToClient(m_rect2);
	ScreenToClient(m_pie_rect);

	SetBackgroundColor(RGB(100, 120, 140));

	SetWindowPos(NULL, 0, 0, 1920, 1080, NULL);

	m_dcp.DCPTextSetting(_T("¸¼Àº °íµñ"), 14);
	m_dcp.CreateDCP(1920, 1080);

	m_dcp.SetPenStyle(Gdiplus::DashStyleDash, 5);

	int x = 0;
	int prev_y = 100 - ((m_ex + 99999)->temp);
	for (int i = 0; i < 100; i++) {

	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGraphBoxDlg::OnPaint()
{
		CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{

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
		//CDialogEx::OnPaint();
		m_dcp.Draw(dc);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGraphBoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGraphBoxDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CGraphBoxDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
