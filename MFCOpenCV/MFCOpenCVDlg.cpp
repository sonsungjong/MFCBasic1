
// MFCOpenCVDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"

#include "MFCOpenCV.h"
#include "MFCOpenCVDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/*
dll 설정을 위해
Project -> Properties -> Configuration Properties -> Debugging -> Environment 에다가

PATH=C:\opencv\build\x64\vc15\bin;%PATH%;

를 추가해줘야함
*/



CMFCOpenCVDlg::CMFCOpenCVDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCOPENCV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCOpenCVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
}

BEGIN_MESSAGE_MAP(CMFCOpenCVDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCOpenCVDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCOpenCVDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMFCOpenCVDlg message handlers

BOOL CMFCOpenCVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_capture = new cv::VideoCapture(0);
	if (!m_capture->isOpened()) {
		MessageBox(_T("캡처 로딩 실패\n"));
	}
	//::SetWindowPos(m_hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL);
	::SetWindowPos(m_hWnd, HWND_TOP, 0, 0, 1280, 1024, NULL);
	GetDlgItem(IDC_PICTURE)->MoveWindow(0, 0, 1280, 1024);
	m_capture->set(cv::CAP_PROP_FRAME_WIDTH, 1280);
	m_capture->set(cv::CAP_PROP_FRAME_HEIGHT, 1024);

	SetTimer(1000, 10, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCOpenCVDlg::OnPaint()
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
HCURSOR CMFCOpenCVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCOpenCVDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCOpenCVDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CMFCOpenCVDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//DestroyWindow();
	//PostQuitMessage(0);

	CDialogEx::OnClose();
}


void CMFCOpenCVDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	//::PostQuitMessage(0);
}


void CMFCOpenCVDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1000) {
		m_capture->read(m_mat_frame);
		cv::flip(m_mat_frame, m_mat_frame, 1);
		//cvtColor(m_mat_frame, m_mat_frame, cv::COLOR_BGR2GRAY);

		int bpp = 8 * m_mat_frame.elemSize();
		assert(bpp == 8 || bpp == 24 || bpp == 32);

		int padding = 0;
		if (bpp < 32) {
			padding = 4 - (m_mat_frame.cols % 4);
		}
		if (padding == 4) {
			padding = 0;
		}
		int border = 0;
		if (bpp < 32) {
			border = 4 - (m_mat_frame.cols % 4);
		}

		cv::Mat mat_temp;
		if (border > 0 || m_mat_frame.isContinuous() == false) {
			cv::copyMakeBorder(m_mat_frame, mat_temp, 0, 0, 0, border, cv::BORDER_CONSTANT, 0);
		}
		else {
			mat_temp = m_mat_frame;
		}

		RECT r;
		m_picture.GetClientRect(&r);
		cv::Size winSize(r.right, r.bottom);
		m_img.Create(winSize.width, winSize.height, 24);

		BITMAPINFO* bitInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
		bitInfo->bmiHeader.biBitCount = bpp;
		bitInfo->bmiHeader.biWidth = mat_temp.cols;
		bitInfo->bmiHeader.biHeight = -mat_temp.rows;
		bitInfo->bmiHeader.biPlanes = 1;
		bitInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitInfo->bmiHeader.biCompression = BI_RGB;
		bitInfo->bmiHeader.biClrImportant = 0;
		bitInfo->bmiHeader.biClrUsed = 0;
		bitInfo->bmiHeader.biSizeImage = 0;
		bitInfo->bmiHeader.biXPelsPerMeter = 0;
		bitInfo->bmiHeader.biYPelsPerMeter = 0;

		if (bpp == 8) {
			RGBQUAD* palette = bitInfo->bmiColors;
			for (int i = 0; i < 256; i++) {
				palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
				palette[i].rgbReserved = 0;
			}
		}

		if (mat_temp.cols == winSize.width && mat_temp.rows == winSize.height) {
			SetDIBitsToDevice(m_img.GetDC(), 0, 0, winSize.width, winSize.height,
				0, 0, 0, mat_temp.rows, mat_temp.data, bitInfo, DIB_RGB_COLORS);
		}
		else {
			int destx = 0, desty = 0;
			int destw = winSize.width;
			int desth = winSize.height;
			int imgx = 0, imgy = 0;
			int imgWidth = mat_temp.cols - border;
			int imgHeight = mat_temp.rows;

			StretchDIBits(m_img.GetDC(), destx, desty, destw, desth,
				imgx, imgy, imgWidth, imgHeight, mat_temp.data, bitInfo, DIB_RGB_COLORS, SRCCOPY);
		}

		HDC dc = ::GetDC(m_picture.m_hWnd);
		m_img.BitBlt(dc, 0, 0);
		::ReleaseDC(m_picture.m_hWnd, dc);
		m_img.ReleaseDC();
		m_img.Destroy();
	}
	CDialogEx::OnTimer(nIDEvent);
}


