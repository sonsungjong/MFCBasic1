
// MFCL113SetPixelDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL113SetPixel.h"
#include "MFCL113SetPixelDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL113SetPixelDlg dialog



CMFCL113SetPixelDlg::CMFCL113SetPixelDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL113SETPIXEL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL113SetPixelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST, m_msg_list);
}

BEGIN_MESSAGE_MAP(CMFCL113SetPixelDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL113SetPixelDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_PIXEL_BTN, &CMFCL113SetPixelDlg::OnBnClickedPixelBtn)
	ON_BN_CLICKED(IDC_PIXELV_BTN, &CMFCL113SetPixelDlg::OnBnClickedPixelvBtn)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_MEM_PIXEL_BTN, &CMFCL113SetPixelDlg::OnBnClickedMemPixelBtn)
	ON_BN_CLICKED(IDC_MEM_PIXELV_BTN, &CMFCL113SetPixelDlg::OnBnClickedMemPixelvBtn)
	ON_BN_CLICKED(IDC_MEM_DIRECT_BTN, &CMFCL113SetPixelDlg::OnBnClickedMemDirectBtn)
	ON_BN_CLICKED(IDC_R_PIXEL_BTN, &CMFCL113SetPixelDlg::OnBnClickedRPixelBtn)
	ON_BN_CLICKED(IDC_R_MEM_PIXEL_BTN, &CMFCL113SetPixelDlg::OnBnClickedRMemPixelBtn)
	ON_BN_CLICKED(IDC_R_MEM_DIRECT_BTN, &CMFCL113SetPixelDlg::OnBnClickedRMemDirectBtn)
	ON_BN_CLICKED(IDC_NOISE_START_BTN, &CMFCL113SetPixelDlg::OnBnClickedNoiseStartBtn)
	ON_BN_CLICKED(IDC_NOISE_STOP_BTN, &CMFCL113SetPixelDlg::OnBnClickedNoiseStopBtn)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCL113SetPixelDlg message handlers

BOOL CMFCL113SetPixelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_image.Create(450, 400, 32);						// 450*400, 32bit색상
	HDC h_dc = m_image.GetDC();
	m_dc.Attach(h_dc);				// WinAPI hdc를 MFC cdc로 변환

	GetObject((HBITMAP)m_image, sizeof(BITMAP), &m_bmp_info);
	mp_image_data = (unsigned int*)m_image.GetBits();
	// 도형의 오른쪽 최하단으로 이동
	mp_image_data += m_bmp_info.bmWidthBytes / sizeof(unsigned int) -1;

	srand((unsigned int)time(nullptr));					// 난수 초기화

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL113SetPixelDlg::OnPaint()
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
HCURSOR CMFCL113SetPixelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL113SetPixelDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}

void CMFCL113SetPixelDlg::AddTimeToList(const TCHAR* ap_msg, int a_time_value)
{
	CString str;
	str.Format(_T("%s : %d"), ap_msg, a_time_value);
	int index = m_msg_list.InsertString(-1, str);
	m_msg_list.SetCurSel(index);
}

void CMFCL113SetPixelDlg::OnBnClickedPixelBtn()
{
	// TODO: Add your control notification handler code here
	CClientDC dc(this);
	int start_tick = GetTickCount();				// 밀리세컨드 단위 시간기록

	for (int y = 0; y < m_bmp_info.bmHeight; y++) {
		for (int x = 0; x < m_bmp_info.bmWidth; x++) {
			dc.SetPixel(x, y, RGB(0, 0, 255));
		}
	}

	//GetTickCount() - start_tick;					// 시간차이 계산
	AddTimeToList(_T("SetPixel 사용"), GetTickCount() - start_tick);
}

void CMFCL113SetPixelDlg::OnBnClickedPixelvBtn()
{
	// TODO: Add your control notification handler code here
	CClientDC dc(this);
	int start_tick = GetTickCount();				// 밀리세컨드 단위 시간기록

	for (int y = 0; y < m_bmp_info.bmHeight; y++) {
		for (int x = 0; x < m_bmp_info.bmWidth; x++) {
			dc.SetPixelV(x, y, RGB(0, 255, 0));
		}
	}

	//GetTickCount() - start_tick;					// 시간차이 계산
	AddTimeToList(_T("SetPixelV 사용"), GetTickCount() - start_tick);
}


void CMFCL113SetPixelDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	m_dc.Detach();
	m_image.ReleaseDC();
}


void CMFCL113SetPixelDlg::OnBnClickedMemPixelBtn()
{
	// TODO: Add your control notification handler code here
	CClientDC dc(this);

	int start_tick = GetTickCount();

	for (int y = 0; y < m_bmp_info.bmHeight; y++) {
		for (int x = 0; x < m_bmp_info.bmWidth; x++) {
			m_dc.SetPixel(x, y, RGB(0, 255, 255));
		}
	}
	m_image.Draw(dc, 0, 0);
	AddTimeToList(_T("CImage + SetPixel 사용"), GetTickCount() - start_tick);
}


void CMFCL113SetPixelDlg::OnBnClickedMemPixelvBtn()
{
	// TODO: Add your control notification handler code here
	CClientDC dc(this);

	int start_tick = GetTickCount();

	for (int y = 0; y < m_bmp_info.bmHeight; y++) {
		for (int x = 0; x < m_bmp_info.bmWidth; x++) {
			m_dc.SetPixelV(x, y, RGB(255, 0, 255));
		}
	}
	m_image.Draw(dc, 0, 0);
	AddTimeToList(_T("CImage + SetPixelV 사용"), GetTickCount() - start_tick);
}

void CMFCL113SetPixelDlg::OnBnClickedMemDirectBtn()
{
	// TODO: Add your control notification handler code here
	CClientDC dc(this);

	unsigned int* p = mp_image_data;
	int count = m_bmp_info.bmWidth * m_bmp_info.bmHeight;
	int start_tick = GetTickCount();			// 시간 계산

	for (int i = 0; i < count; i++) {
		*p = 0x00FF0000;
		p--;
	}

	m_image.Draw(dc, 0, 0);
	AddTimeToList(_T("직접 출력"), GetTickCount() - start_tick);				// 걸린 시간 측정
}


void CMFCL113SetPixelDlg::OnBnClickedRPixelBtn()
{
	// TODO: Add your control notification handler code here
	CClientDC dc(this);

	int start_tick = GetTickCount(), pos, x, y;

	for (int i = 0; i < 100000; i++) {
		x = rand() % m_bmp_info.bmWidth;
		y = rand() % m_bmp_info.bmHeight;
		dc.SetPixel(x, y, RGB(rand()%255, rand() % 255, rand() % 255));
	}

	AddTimeToList(_T("난수 : SetPixel 사용"), GetTickCount() - start_tick);
}


void CMFCL113SetPixelDlg::OnBnClickedRMemPixelBtn()
{
	// TODO: Add your control notification handler code here
	CClientDC dc(this);

	int start_tick = GetTickCount(), x, y;

	for (int i = 0; i < 100000; i++) {
		x = rand() % m_bmp_info.bmWidth;
		y = rand() % m_bmp_info.bmHeight;
		m_dc.SetPixel(x, y, RGB(rand() % 255, rand() % 255, rand() % 255));
	}

	m_image.Draw(dc, 0, 0);
	AddTimeToList(_T("(CImage) 난수 : SetPixel 사용"), GetTickCount() - start_tick);
}


void CMFCL113SetPixelDlg::OnBnClickedRMemDirectBtn()
{
	// TODO: Add your control notification handler code here
	CClientDC dc(this);

	unsigned int* p = mp_image_data;
	int start_tick = GetTickCount(), x, y;

	for (int i = 0; i < 100000; i++) {
		x = rand() % m_bmp_info.bmWidth;
		y = rand() % m_bmp_info.bmHeight;
		*(p - (m_bmp_info.bmWidth - x) - y * m_bmp_info.bmWidth) = RGB(rand() % 255, rand() % 255, rand() % 255);
	}

	m_image.Draw(dc, 0, 0);
	AddTimeToList(_T("(CImage) 난수 : 직접출력 사용"), GetTickCount() - start_tick);
}


void CMFCL113SetPixelDlg::OnBnClickedNoiseStartBtn()
{
	// TODO: Add your control notification handler code here
	SetTimer(1, 1, nullptr);
}


void CMFCL113SetPixelDlg::OnBnClickedNoiseStopBtn()
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
}


void CMFCL113SetPixelDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		/*
		CClientDC dc(this);
		int start_tick = GetTickCount(), x, y;

		for (int i = 0; i < 100000; i++) {
			x = rand() % m_bmp_info.bmWidth;
			y = rand() % m_bmp_info.bmHeight;
			m_dc.SetPixel(x, y, RGB(rand() % 255, rand() % 255, rand() % 255));
		}

		m_image.Draw(dc, 0, 0);
		*/

		CClientDC dc(this);

		unsigned int* p = mp_image_data;
		int start_tick = GetTickCount(), x, y;

		for (int i = 0; i < 100000; i++) {
			x = rand() % m_bmp_info.bmWidth;
			y = rand() % m_bmp_info.bmHeight;
			*(p - (m_bmp_info.bmWidth - x) - y * m_bmp_info.bmWidth) = RGB(rand() % 255, rand() % 255, rand() % 255);
		}

		m_image.Draw(dc, 0, 0);

	}else{ CDialogEx::OnTimer(nIDEvent); }
}
