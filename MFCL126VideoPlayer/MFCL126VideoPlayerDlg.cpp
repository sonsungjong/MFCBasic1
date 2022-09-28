
// MFCL126VideoPlayerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL126VideoPlayer.h"
#include "MFCL126VideoPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL126VideoPlayerDlg dialog



CMFCL126VideoPlayerDlg::CMFCL126VideoPlayerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL126VIDEOPLAYER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL126VideoPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL126VideoPlayerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL126VideoPlayerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL126VideoPlayerDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMFCL126VideoPlayerDlg message handlers

BOOL CMFCL126VideoPlayerDlg::OnInitDialog()
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

void CMFCL126VideoPlayerDlg::OnPaint()
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
HCURSOR CMFCL126VideoPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL126VideoPlayerDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL126VideoPlayerDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

// 1. 프로젝트 생성시 ActiveX컨트롤 체크
// 2. #include <afxdisp.h>        // MFC Automation classes
// 3. AfxEnableControlContainer();
// 4. 대화상자에 우클릭하여 ActiveX컨트롤 추가하기
// 5. Window Media Player 선택하여 삽입
// 6. 속성의 URL에 경로 지정해주면 끝 (ocx 컨트롤)