
// MFCL127VideoListDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL127VideoList.h"
#include "MFCL127VideoListDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL127VideoListDlg dialog



CMFCL127VideoListDlg::CMFCL127VideoListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL127VIDEOLIST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL127VideoListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIDEO_LIST, m_video_list);
	DDX_Control(pDX, IDC_OCX_PLAYER, m_ocx_player);
}

BEGIN_MESSAGE_MAP(CMFCL127VideoListDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL127VideoListDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL127VideoListDlg::OnBnClickedCancel)
	ON_LBN_DBLCLK(IDC_VIDEO_LIST, &CMFCL127VideoListDlg::OnLbnDblclkVideoList)
END_MESSAGE_MAP()


// CMFCL127VideoListDlg message handlers

BOOL CMFCL127VideoListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//m_ocx_player.SetUrl(_T("C:\\video\\dron.mp4"));
	m_video_list.InsertString(0, _T("C:\\video\\dron.mp4"));
	m_video_list.InsertString(1, _T("C:\\video\\person.mp4"));
	m_video_list.InsertString(2, _T("C:\\video\\human.mp4"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL127VideoListDlg::OnPaint()
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
HCURSOR CMFCL127VideoListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL127VideoListDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL127VideoListDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCL127VideoListDlg::OnLbnDblclkVideoList()
{
	// TODO: Add your control notification handler code here
	int index = m_video_list.GetCurSel();
	if (LB_ERR != index)
	{
		CString str;
		m_video_list.GetText(index, str);
		m_ocx_player.SetUrl(str);
	}
}
