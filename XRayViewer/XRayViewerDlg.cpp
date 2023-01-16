
// XRayViewerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "XRayViewer.h"
#include "XRayViewerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CXRayViewerDlg::CXRayViewerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_XRAYVIEWER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXRayViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CXRayViewerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CXRayViewerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CXRayViewerDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CXRayViewerDlg message handlers

BOOL CXRayViewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CClientDC dc(this);
	m_mem_dc.CreateCompatibleDC(&dc);
	m_mem_bmp.CreateCompatibleBitmap(&dc, IMG_WIDTH, IMG_HEIGHT);
	m_mem_dc.SelectObject(&m_mem_bmp);

	FILE* p_file = NULL;
	// test1.img를 읽기 모드로 연다
	if (fopen_s(&p_file, "test1.img", "rb") == 0) {
		fseek(p_file, 0, SEEK_END);				// 파일의 끝으로 이동
		int image_size = ftell(p_file);				// 크기 얻음
		fseek(p_file, 0, SEEK_SET);					// 다시 처음으로 이동

		unsigned short* p_16bit_data = new unsigned short[image_size];				// 파일 크기만큼 메모리 할당
		fread(p_16bit_data, 1, image_size, p_file);					// 파일 1번 복사
		fclose(p_file);

		// 이미지 패턴 구성
		unsigned char* p_image_pattern = new unsigned char[IMG_WIDTH * IMG_HEIGHT * 4];
		unsigned short* p_src = p_16bit_data, color;
		unsigned char* p_dest = p_image_pattern;
		unsigned short int min = 0xFFFF, max = 0x0000, range;

		// 16비트 이미지를 탐색하면서 색상의 최솟값과 최댓값 계산
		for (int i = 0; i < image_size / 2; i++, p_src++) {
			if (*p_src >= 50000) { *p_src = 250; }

			if (min > *p_src) { min = *p_src; }
			else if (max < *p_src) { max = *p_src; }
		}
		range = max - min;
		p_src = (unsigned short*)p_16bit_data;

		for (int i = 0; i < image_size / 2; i++, p_src++) {
			color = (*p_src - min)*255 / range;
			*p_dest++ = (unsigned char)color;					// blue
			*p_dest++ = (unsigned char)color;					// green
			*p_dest++ = (unsigned char)color;					// red
			*p_dest++ = 0xFF;										// alpha
		}

		// 패턴을 비트맵에 저장
		m_mem_bmp.SetBitmapBits(IMG_WIDTH * IMG_HEIGHT * 4, p_image_pattern);
		delete[] p_16bit_data;
		delete[] p_image_pattern;
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXRayViewerDlg::OnPaint()
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
		CRect r;
		GetClientRect(r);
		dc.SetStretchBltMode(COLORONCOLOR);
		// 이미지를 화면에 맞게 축소해서 출력
		dc.StretchBlt(0, 0, r.Width(), r.Height(), &m_mem_dc, 0, 0, IMG_WIDTH, IMG_HEIGHT, SRCCOPY);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CXRayViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CXRayViewerDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CXRayViewerDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CXRayViewerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	m_mem_bmp.DeleteObject();
	m_mem_dc.DeleteDC();
}
