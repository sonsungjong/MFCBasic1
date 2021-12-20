
// ELCProjectDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ELCProject.h"
#include "ELCProjectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void TWAPI_MakeGateImage(TW_DCP* ap_dcp);

// CELCProjectDlg dialog
CELCProjectDlg::CELCProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ELCPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CELCProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CELCProjectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CELCProjectDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CELCProjectDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CELCProjectDlg message handlers

BOOL CELCProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetClientRect(m_rect);
	//GDI+ : 회로
	m_dcp.CreateDCP(m_rect.Width(), m_rect.Height());
	//GDI+ : 게이트 이미지
	m_gate_dcp.CreateDCP(700, 280);

	// 어두운 회색
	m_dcp.Clear(RGB24(18, 21, 29));
	m_gate_dcp.Clear(RGB24(18, 21, 29));

	TWAPI_MakeGateImage(&m_gate_dcp);
	m_dcp.Draw(m_gate_dcp, 0, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CELCProjectDlg::OnPaint()
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
		m_dcp.Draw(dc, m_rect.left, m_rect.top);
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CELCProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CELCProjectDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CELCProjectDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
