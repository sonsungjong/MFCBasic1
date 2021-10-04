
// MFCImageProcessingDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCImageProcessing.h"
#include "MFCImageProcessingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCImageProcessingDlg dialog



CMFCImageProcessingDlg::CMFCImageProcessingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCIMAGEPROCESSING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCImageProcessingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MIN_SLIDER, m_min_slider);
	DDX_Control(pDX, IDC_MAX_SLIDER, m_max_slider);
}

BEGIN_MESSAGE_MAP(CMFCImageProcessingDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCImageProcessingDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCImageProcessingDlg::OnBnClickedCancel)
	ON_WM_HSCROLL()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCImageProcessingDlg message handlers
void CMFCImageProcessingDlg::ModifyGrayPattern()
{
	UINT8* p_start_image = mp_cur_image, * p_end_image = mp_cur_image + m_line_size;
	int temp;
	while (p_start_image < p_end_image) {
		temp = *p_start_image + *(p_start_image + 1) + *(p_start_image + 2);
		temp = temp / 3;

		if (temp < m_min || temp > m_max) {
			*(UINT32*)p_start_image = 0xFF000000;			// unsigned int 4바이트
			p_start_image += 4;
		}
		else {
			*p_start_image++ = temp;
			*p_start_image++ = temp;
			*p_start_image++ = temp;
			p_start_image++;
		}
	}
}

BOOL CMFCImageProcessingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_min_slider.SetRange(0, 255);
	m_max_slider.SetRange(0, 255);
	m_max_slider.SetPos(m_max);
	SetDlgItemInt(IDC_MIN_EDIT, m_min);
	SetDlgItemInt(IDC_MAX_EDIT, m_max);
	m_img.Load(L"img.png");

	BITMAP bmp_info;
	GetObject((HBITMAP)m_img, sizeof(BITMAP), &bmp_info);
	
	m_image_cx = bmp_info.bmWidth;
	m_image_cy = bmp_info.bmHeight;
	m_line_size = bmp_info.bmWidthBytes;
	m_image_size = bmp_info.bmHeight * bmp_info.bmWidthBytes;

	// 바이트순서: BGRA, 4바이트값 : 0xAARRGGBB
	mp_cur_image = (unsigned char*)m_img.GetBits();
	mp_cur_image -= (m_image_cy - 1) * m_line_size;

	mp_org_image = new UINT8[m_image_size];
	memcpy(mp_org_image, mp_cur_image, m_image_size);
	ModifyGrayPattern();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCImageProcessingDlg::OnPaint()
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
		m_img.Draw(dc, 0, 0);
		ModifyGrayPattern();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCImageProcessingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCImageProcessingDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCImageProcessingDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCImageProcessingDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar != NULL && (nSBCode == SB_THUMBTRACK || nSBCode == SB_ENDSCROLL)) {
		if (pScrollBar->GetDlgCtrlID() == IDC_MIN_SLIDER) {
			m_min = m_min_slider.GetPos();
			SetDlgItemInt(IDC_MIN_EDIT, m_min);
		}
		else if (pScrollBar->GetDlgCtrlID() == IDC_MAX_SLIDER) {
			m_min = m_max_slider.GetPos();
			SetDlgItemInt(IDC_MAX_EDIT, m_max);
		}
		if (m_min < m_max) {
			memcpy(mp_cur_image, mp_org_image, m_image_size);
			ModifyGrayPattern();
			Invalidate(0);
		}
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CMFCImageProcessingDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	delete[] mp_org_image;
}
