
// MFCL115PictureFilterDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL115PictureFilter.h"
#include "MFCL115PictureFilterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL115PictureFilterDlg dialog



CMFCL115PictureFilterDlg::CMFCL115PictureFilterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL115PICTUREFILTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL115PictureFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL115PictureFilterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL115PictureFilterDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL115PictureFilterDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_GRAY_BTN, &CMFCL115PictureFilterDlg::OnBnClickedGrayBtn)
	ON_BN_CLICKED(IDC_FILTER1_BTN, &CMFCL115PictureFilterDlg::OnBnClickedFilter1Btn)
	ON_BN_CLICKED(IDC_FILTER2_BTN, &CMFCL115PictureFilterDlg::OnBnClickedFilter2Btn)
	ON_BN_CLICKED(IDC_FILTER3_BTN, &CMFCL115PictureFilterDlg::OnBnClickedFilter3Btn)
	ON_BN_CLICKED(IDC_RESTORE_BTN, &CMFCL115PictureFilterDlg::OnBnClickedRestoreBtn)
	ON_BN_CLICKED(IDC_COMMIT_BTN, &CMFCL115PictureFilterDlg::OnBnClickedCommitBtn)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_FILTER4_BTN, &CMFCL115PictureFilterDlg::OnBnClickedFilter4Btn)
END_MESSAGE_MAP()


// CMFCL115PictureFilterDlg message handlers

BOOL CMFCL115PictureFilterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_image.Load(_T("../photo.jpg"));						// 이미지 불러오기
	GetObject((HBITMAP)m_image, sizeof(BITMAP), &m_bmp_info);

	mp_image_pattern = (unsigned char*)m_image.GetBits();
	mp_image_pattern += m_bmp_info.bmWidthBytes - 3;

	m_commit_image.Create(m_bmp_info.bmWidth, m_bmp_info.bmHeight, 24);
	mp_commit_pattern = (unsigned char*)m_commit_image.GetBits();
	mp_commit_pattern += m_bmp_info.bmWidthBytes - 3;

	int image_size = m_bmp_info.bmWidth * m_bmp_info.bmHeight * 3;
	memcpy(mp_commit_pattern - image_size +3, mp_image_pattern - image_size + 3, image_size);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL115PictureFilterDlg::OnPaint()
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
		dc.SetStretchBltMode(COLORONCOLOR);					// 축소시 깨짐 방지
		m_image.Draw(dc, 0, 0, m_bmp_info.bmWidth / 4, m_bmp_info.bmHeight / 4);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCL115PictureFilterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL115PictureFilterDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL115PictureFilterDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCL115PictureFilterDlg::OnBnClickedGrayBtn()
{
	// TODO: Add your control notification handler code here
	int dot_count = m_bmp_info.bmWidth * m_bmp_info.bmHeight;
	unsigned char* p = mp_image_pattern +3;
	int temp;
	
	for (int i = 0; i < dot_count; i++) {
		// 회색 만들기
		temp = (*p + *(p - 1) + *(p - 2))/3;			// RGB 모두 더해서 평균
		// 3bytes
		*p-- = temp;			// Red
		*p-- = temp;			// Green
		*p-- = temp;					// Blue
	}

	Invalidate(FALSE);					// 배경은 안지움
}

_inline void IncFixColor(unsigned char* ap_color, int a_value)
{
	int temp = *ap_color + a_value;
	if (temp > 255) { *ap_color = 255; }
	else { *ap_color = temp; }
}

void CMFCL115PictureFilterDlg::OnBnClickedFilter1Btn()
{
	// TODO: Add your control notification handler code here
	int dot_count = m_bmp_info.bmWidth * m_bmp_info.bmHeight;
	unsigned char* p = mp_image_pattern;

	for (int i = 0; i < dot_count; i++) {
		IncFixColor(p--, 30);
		IncFixColor(p--, 30);
		IncFixColor(p--, 30);
	}

	Invalidate(FALSE);					// 배경은 안지움
}

_inline void IncFixColor2(unsigned char* ap_color, float a_rate)
{
	int index;

	if (*ap_color > *(ap_color - 1)) {
		if (*ap_color > *(ap_color - 2)) {
			index = 0;				// red 가 제일 큼
		}
		else { index = 2; }				// blue 가 제일 큼
	}
	else {
		if (*(ap_color - 1) > *(ap_color - 2)) { index = 1; }			// green이 제일 큼
		else { index = 2; }				// blue가 제일 큼
	}

	if (*(ap_color - index) * a_rate > 255) {
		a_rate = 255.0f / *(ap_color - index);
	}
	*ap_color-- = (int)(*ap_color * a_rate);
	*ap_color-- = (int)(*ap_color * a_rate);
	*ap_color-- = (int)(*ap_color * a_rate);
}


void CMFCL115PictureFilterDlg::OnBnClickedFilter2Btn()
{
	// TODO: Add your control notification handler code here
	int dot_count = m_bmp_info.bmWidth * m_bmp_info.bmHeight;
	unsigned char* p = mp_image_pattern;

	for (int i = 0; i < dot_count; i++) {
		IncFixColor2(p, 1.2f);
		p -= 3;
	}
	Invalidate(FALSE);
}



void CMFCL115PictureFilterDlg::OnBnClickedFilter3Btn()
{
	// TODO: Add your control notification handler code here
	int dot_count = m_bmp_info.bmWidth * m_bmp_info.bmHeight, temp;
	unsigned char* p = mp_image_pattern;

	for (int i = 0; i < dot_count; i++) {
		temp = (*p + *(p - 1) + *(p - 2));
		IncFixColor2(p, 1.0f + ((768 - temp)*2)/6000.0f);
		p -= 3;
	}
	Invalidate(FALSE);
}


void CMFCL115PictureFilterDlg::OnBnClickedRestoreBtn()
{
	// TODO: Add your control notification handler code here
	int image_size = m_bmp_info.bmWidth * m_bmp_info.bmHeight * 3;
	memcpy(mp_image_pattern - image_size + 3, mp_commit_pattern - image_size + 3, image_size);

	Invalidate(FALSE);
}


void CMFCL115PictureFilterDlg::OnBnClickedCommitBtn()
{
	// TODO: Add your control notification handler code here
	int image_size = m_bmp_info.bmWidth * m_bmp_info.bmHeight * 3;
	memcpy(mp_commit_pattern - image_size + 3, mp_image_pattern - image_size + 3, image_size);
}


void CMFCL115PictureFilterDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	// 밖을 벗어나지 않게 보정
	if (point.x < 50) { point.x = 50; }
	else if (point.x + 50 >= m_bmp_info.bmWidth / 4) { point.x = m_bmp_info.bmWidth / 4 - 51; }
	if (point.y < 50) { point.y = 50; }
	else if (point.y + 50 >= m_bmp_info.bmHeight / 4) { point.y = m_bmp_info.bmHeight / 4 - 51; }

	// 원본그림에 대한 마우스 위치
	int pos = -(point.y * 4) * m_bmp_info.bmWidth * 3 - (m_bmp_info.bmWidth - (point.x * 4))*3;
	unsigned char* p = mp_image_pattern + pos;
	unsigned char* p_commit = mp_commit_pattern + pos;

	if (*p == *p_commit) { IncFixColor2(p, 1.2f); }				// 원의 중심점

	double radian, x, y;

	for (int degree = 0; degree < 360; degree++) {
		// 라디안 구하기
		radian = degree * 3.141592 / 180.0;
		x = sin(radian);
		y = cos(radian);

		for (int radius = 1; radius < 50; radius++) {
			pos = -(point.y * 4 - (int)(y*radius)) * m_bmp_info.bmWidth * 3 
				- (m_bmp_info.bmWidth - point.x * 4 - (int)(x*radius)) * 3;
			p = mp_image_pattern + pos;
			p_commit = mp_commit_pattern + pos;
			if (*p == *p_commit) { IncFixColor2(p, 1.2f); }
		}
	}
	Invalidate(FALSE);
	//CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCL115PictureFilterDlg::OnBnClickedFilter4Btn()
{
	// TODO: Add your control notification handler code here
	unsigned char* p, *p_temp;
	unsigned int avr_r, avr_g, avr_b;

	for (int y = 1; y < m_bmp_info.bmHeight -2; y++) {
		p = mp_image_pattern - y * m_bmp_info.bmWidth * 3;
		for (int x = 1; x < m_bmp_info.bmWidth - 2; x++) {
			p_temp = p + m_bmp_info.bmWidth * 3 + 3;
			avr_r = *p_temp + *(p_temp - 3) + *(p_temp - 6);
			avr_g = *(p_temp -1) + *(p_temp - 4) + *(p_temp - 7);
			avr_b = *(p_temp -2) + *(p_temp - 5) + *(p_temp - 8);

			p_temp = p + 3;
			avr_r += *p_temp + *(p_temp - 3) + *(p_temp - 6);
			avr_g += *(p_temp - 1) + *(p_temp - 4) + *(p_temp - 7);
			avr_b += *(p_temp - 2) + *(p_temp - 5) + *(p_temp - 8);

			p_temp = p - m_bmp_info.bmWidth *3 +3;
			avr_r += *p_temp + *(p_temp - 3) + *(p_temp - 6);
			avr_g += *(p_temp - 1) + *(p_temp - 4) + *(p_temp - 7);
			avr_b += *(p_temp - 2) + *(p_temp - 5) + *(p_temp - 8);

			*p = avr_r / 9;
			*(p-1) = avr_g / 9;
			*(p-2) = avr_b / 9;
			p -= 3;
		}
	}
	Invalidate(FALSE);
}
