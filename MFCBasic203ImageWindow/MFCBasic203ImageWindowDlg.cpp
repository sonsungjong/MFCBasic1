
// MFCBasic203ImageWindowDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic203ImageWindow.h"
#include "MFCBasic203ImageWindowDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic203ImageWindowDlg dialog



CMFCBasic203ImageWindowDlg::CMFCBasic203ImageWindowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC203IMAGEWINDOW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic203ImageWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic203ImageWindowDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MUL2, &CMFCBasic203ImageWindowDlg::OnBnClickedMul2)
	ON_BN_CLICKED(IDC_MUL4, &CMFCBasic203ImageWindowDlg::OnBnClickedMul4)
	ON_BN_CLICKED(IDC_MUL8, &CMFCBasic203ImageWindowDlg::OnBnClickedMul8)
END_MESSAGE_MAP()


// CMFCBasic203ImageWindowDlg message handlers

BOOL CMFCBasic203ImageWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	SetBackgroundColor(RGB(168, 168, 0));			// 오차범위 확인을 위한 배경색

	// TODO: Add extra initialization here
	m_img.Load(L"../photo.jpg");			// 이미지 불러오기

	GetWindowRect(m_win_rect);				// 전체 윈도우 영역 폭높이 저장
	GetClientRect(m_client_rect);				// 내부 클라이언트 영역 폭높이 저장

	m_cx_margin = m_win_rect.Width() - m_client_rect.Width() +4;				// 전체 윈도우와 내부 클라이언트간의 폭계산
	m_cy_margin = m_win_rect.Height() - m_client_rect.Height() +4;				// 전체 윈도우와 내부 클라이언트간의 높이계산

	GetDlgItem(IDC_MUL2)->GetWindowRect(m_btn_rect);
	ScreenToClient(m_btn_rect);
	m_top_margin = m_btn_rect.bottom;

	SetWindowPos(NULL, 0, 0, m_img.GetWidth() * m_zoom_level + m_cx_margin, m_img.GetHeight() * m_zoom_level + m_cy_margin + m_top_margin, SWP_NOMOVE);				// 윈도우크기 셋팅

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic203ImageWindowDlg::OnPaint()
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
		dc.SetStretchBltMode(COLORONCOLOR);				// 이미지 깨짐 보정
		m_img.Draw(dc, 2, 2+m_top_margin, m_img.GetWidth() * m_zoom_level, m_img.GetHeight() * m_zoom_level);			// 이미지 그리기
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic203ImageWindowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic203ImageWindowDlg::OnBnClickedMul2()
{
	// TODO: Add your control notification handler code here
	m_zoom_level = 0.125f;
	SetWindowPos(NULL, 0, 0, m_img.GetWidth() * m_zoom_level + m_cx_margin, m_img.GetHeight() * m_zoom_level + m_cy_margin + m_top_margin, SWP_NOMOVE);
	Invalidate();
}


void CMFCBasic203ImageWindowDlg::OnBnClickedMul4()
{
	// TODO: Add your control notification handler code here
	m_zoom_level = 0.25f;
	SetWindowPos(NULL, 0, 0, m_img.GetWidth() * m_zoom_level + m_cx_margin, m_img.GetHeight() * m_zoom_level + m_cy_margin + m_top_margin, SWP_NOMOVE);
	Invalidate();
}


void CMFCBasic203ImageWindowDlg::OnBnClickedMul8()
{
	// TODO: Add your control notification handler code here
	m_zoom_level = 0.5f;
	SetWindowPos(NULL, 0, 0, m_img.GetWidth() * m_zoom_level + m_cx_margin, m_img.GetHeight() * m_zoom_level + m_cy_margin + m_top_margin, SWP_NOMOVE);
	Invalidate();
}
