
// MFCL213ImageRateDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL213ImageRate.h"
#include "MFCL213ImageRateDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL213ImageRateDlg dialog



CMFCL213ImageRateDlg::CMFCL213ImageRateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL213IMAGERATE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL213ImageRateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_RATE, m_check_rate);
}

BEGIN_MESSAGE_MAP(CMFCL213ImageRateDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL213ImageRateDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL213ImageRateDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK_RATE, &CMFCL213ImageRateDlg::OnBnClickedCheckRate)
END_MESSAGE_MAP()


// CMFCL213ImageRateDlg message handlers

BOOL CMFCL213ImageRateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetDlgItem(IDC_PICTURE1)->GetWindowRect(m_rect);
	ScreenToClient(m_rect);							// 얻은 좌표를 클라이언트 좌표계로 변환

	m_image.Load(_T("../photo.jpg"));
	//m_image.Load(_T("../img/stage_01.png"));
	MakeDisplayImageRect();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL213ImageRateDlg::OnPaint()
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
		dc.SetStretchBltMode(COLORONCOLOR);
		m_image.Draw(dc, m_rate_size);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCL213ImageRateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL213ImageRateDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL213ImageRateDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CMFCL213ImageRateDlg::MakeDisplayImageRect()
{
	int width = m_image.GetWidth();
	int height = m_image.GetHeight();
	if (m_check_rate.GetCheck()) {						// 체크박스 사용
		m_rate_size.left = m_rect.left;
		m_rate_size.top = m_rect.top;
		if (width > height) {						// 가로가 큼
			ResizeByWidth(width, height);
			if (m_rate_size.bottom > m_rect.bottom) {
				// 비율차이가 너무 커서 범위를 오버할 경우
				ResizeByHeight(width, height);
			}
		}
		else {							// 세로가 큼
			ResizeByHeight(width, height);
			if (m_rate_size.right > m_rect.right) {
				// 비율차이가 너무 커서 범위를 오버할 경우
				ResizeByWidth(width, height);
			}
		}
	}
	else {					// 체크박스 해제
		m_rate_size = m_rect;
	}
}

void CMFCL213ImageRateDlg::ResizeByWidth(int a_width, int a_height)
{
	// 가로 유지
	m_rate_size.right = m_rect.right;
	// 높이는 가로를 기준으로 재조정
	m_rate_size.bottom = m_rate_size.top + a_height * m_rect.Width() / a_width;
}

void CMFCL213ImageRateDlg::ResizeByHeight(int a_width, int a_height)
{
	// 세로 유지
	m_rate_size.bottom = m_rect.bottom;
	// 세로를 기준으로 가로를 재조정
	m_rate_size.right = m_rate_size.left + a_width * m_rect.Height() / a_height;
}

void CMFCL213ImageRateDlg::OnBnClickedCheckRate()
{
	// TODO: Add your control notification handler code here
	MakeDisplayImageRect();
	InvalidateRect(m_rect);
}
