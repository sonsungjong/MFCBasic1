
// MFCL114TrueColorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL114TrueColor.h"
#include "MFCL114TrueColorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL114TrueColorDlg dialog


// 생성자에서 m_view_rect 초기화
CMFCL114TrueColorDlg::CMFCL114TrueColorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL114TRUECOLOR_DIALOG, pParent), m_view_rect(0, 0, 160, 128)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL114TrueColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL114TrueColorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL114TrueColorDlg::OnBnClickedOk)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMFCL114TrueColorDlg message handlers

BOOL CMFCL114TrueColorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_color_image.Create(4096, 4096, 32);							// 4096*4096, 한 점이 4byte로 32bit

	BITMAP bmp_info;
	GetObject((HBITMAP)m_color_image, sizeof(BITMAP), &bmp_info);
	mp_color_pattern = (unsigned int*)m_color_image.GetBits();
	mp_color_pattern += bmp_info.bmWidthBytes/sizeof(unsigned int) -1;

	unsigned int* p = mp_color_pattern;
	int x = 0, y = 0, step = 0;

	for (int i = 0; i < 4096 * 4096; i++) {
		*(p - y * 4096 - x - step*256) = i;
		x = (x + 1) % 256;
		if (!x) {y++;}
		if (y >= 4096) { 
			y = 0; 
			step++;
		}
		// *p-- = i;
	}

	// 최대화면으로
	ShowWindow(SW_SHOWMAXIMIZED);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL114TrueColorDlg::OnPaint()
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
		m_color_image.Draw(dc, 0, 0, 512, 512);						// 0,0 위치에 출력
		m_color_image.Draw(dc, 512, 0, 256*5, 256*4, 0, 0, 256*5, 256*4);
		
		dc.SelectStockObject(NULL_BRUSH);
		dc.SelectStockObject(WHITE_PEN);
		dc.Rectangle(m_view_rect);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCL114TrueColorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL114TrueColorDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL114TrueColorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCL114TrueColorDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCL114TrueColorDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnMouseMove(nFlags, point);
}
