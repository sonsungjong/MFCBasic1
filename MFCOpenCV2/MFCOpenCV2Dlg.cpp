
// MFCOpenCV2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCOpenCV2.h"
#include "MFCOpenCV2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCOpenCV2Dlg dialog



CMFCOpenCV2Dlg::CMFCOpenCV2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCOPENCV2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCOpenCV2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCOpenCV2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCOpenCV2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCOpenCV2Dlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_FLIP_BTN, &CMFCOpenCV2Dlg::OnBnClickedFlipBtn)
END_MESSAGE_MAP()


// CMFCOpenCV2Dlg message handlers

BOOL CMFCOpenCV2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	::SetWindowPos(m_hWnd, HWND_TOP, 0, 0, 1920, 1080, NULL);
	m_picture = (CStatic*)GetDlgItem(IDC_PICTURE);

	m_capture = new cv::VideoCapture(0);
	if (!m_capture->isOpened())
	{
		AfxMessageBox(_T("Webcam not found"));
	}

	//m_picture->MoveWindow(0, 0, 1280, 1024);

	m_capture->set(cv::CAP_PROP_FRAME_WIDTH, 1280);				// 가로
	m_capture->set(cv::CAP_PROP_FRAME_HEIGHT, 1024);				// 세로
	SetTimer(1, 5, NULL);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCOpenCV2Dlg::OnPaint()
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
HCURSOR CMFCOpenCV2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCOpenCV2Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCOpenCV2Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCOpenCV2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1)
	{
		// 캠읽기
		m_capture->read(m_mat_frame);
		if (m_flip == 0) {
			cv::flip(m_mat_frame, m_mat_frame, 1);				// 좌우반전
		}

		// 비트맵 생성
		BITMAPINFO bitmapInfo = { 0 };
		bitmapInfo.bmiHeader.biBitCount = 24;
		bitmapInfo.bmiHeader.biWidth = m_mat_frame.cols;
		bitmapInfo.bmiHeader.biHeight = -m_mat_frame.rows;
		bitmapInfo.bmiHeader.biPlanes = 1;
		bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

		// Picture Control의 DC를 가져와서 비트맵 그리기
		HDC hdc = ::GetDC(m_picture->m_hWnd);

		// 그림 크기 조정
		::StretchDIBits(hdc, 0, 0, m_mat_frame.cols*1, m_mat_frame.rows+256, 0, 0, m_mat_frame.cols, m_mat_frame.rows, m_mat_frame.data, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
		::ReleaseDC(m_picture->m_hWnd, hdc);
	}


	CDialogEx::OnTimer(nIDEvent);
}


void CMFCOpenCV2Dlg::OnBnClickedFlipBtn()
{
	if (m_flip == 0) {
		m_flip = 1;
	}
	else {
		m_flip = 0;
	}
}
