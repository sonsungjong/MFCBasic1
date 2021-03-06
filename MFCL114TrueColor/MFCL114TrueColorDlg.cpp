
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
	ON_WM_DESTROY()
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
	m_draw_image.Create(1920, 1080, 32);
	m_pick_image.Create(16, 16, 32);

	m_draw_dc.Attach(m_draw_image.GetDC());

	BITMAP bmp_info;
	GetObject((HBITMAP)m_color_image, sizeof(BITMAP), &bmp_info);
	mp_color_pattern = (unsigned int*)m_color_image.GetBits();
	mp_color_pattern += bmp_info.bmWidthBytes/sizeof(unsigned int) -1;

	GetObject((HBITMAP)m_pick_image, sizeof(BITMAP), &bmp_info);
	mp_pick_pattern = (unsigned int*)m_pick_image.GetBits();
	mp_pick_pattern += bmp_info.bmWidthBytes / sizeof(unsigned int) - 1;

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

	unsigned int* p_src = mp_color_pattern;
	unsigned int* p_dest = mp_pick_pattern;
	for (int i = 0; i < 256; i++) {
		if (i && !(i % 16)) { p_src -= 4096 * 255; }				// 줄바꿈

		*p_dest = *p_src;
		p_src -= 256;
		p_dest--;
	}

	m_color_image.Draw(m_draw_dc, 0, 0, 512, 512);						// 0,0 위치에 출력
	m_color_image.Draw(m_draw_dc, 512, 0, 256 * 5, 256 * 4, 0, 0, 256 * 5, 256 * 4);
	m_pick_image.Draw(m_draw_dc, 0, 512, 512, 512);

	m_draw_dc.SelectStockObject(NULL_BRUSH);
	m_draw_dc.SelectStockObject(WHITE_PEN);
	m_draw_dc.Rectangle(m_view_rect);
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
		m_draw_image.Draw(dc, 0, 0);
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
	if (m_view_rect.PtInRect(point)) {
		m_is_clicked = 1;
		// 현재 클릭한 점을 이전점으로 저장
		m_prev_pos = point;
		SetCapture();
	}
	else if (CRect(512, 0, 512 + 256, 256).PtInRect(point)) {
		m_is_clicked = 2;
	}
	
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCL114TrueColorDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked == 1) {
		ReleaseCapture();
	}
	m_is_clicked = 0;
	
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCL114TrueColorDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked == 1) {
		// 이동거리 = 나중-처음
		CPoint pos = point - m_prev_pos;
		// 이동거리만큼 사각형의 좌표에 더해줌
		m_view_rect += pos;

		m_prev_pos = point;					// 이동하면서 이전점에 현재점을 저장
		//Invalidate(FALSE);

		if (m_view_rect.left < 0) {
			m_view_rect.right -= m_view_rect.left;
			m_view_rect.left = 0;
		}
		else if (m_view_rect.right > 512) {
			m_view_rect.right = 512;
			m_view_rect.left = m_view_rect.right - 160;
		}

		if (m_view_rect.top < 0) {
			m_view_rect.bottom -= m_view_rect.top;
			m_view_rect.top = 0;
		}
		else if (m_view_rect.bottom > 512) {
			m_view_rect.bottom = 512;
			m_view_rect.top = m_view_rect.bottom - 128;
		}

		m_color_image.Draw(m_draw_dc, 0, 0, 512, 512);
		m_color_image.Draw(m_draw_dc, 512, 0, 256 * 5, 256 * 4, m_view_rect.left *8, m_view_rect.top *8, 256 * 5, 256 * 4);
		m_pick_image.Draw(m_draw_dc, 0, 512, 512, 512);
		m_draw_dc.SelectStockObject(NULL_BRUSH);
		m_draw_dc.SelectStockObject(WHITE_PEN);
		m_draw_dc.Rectangle(m_view_rect);

		CClientDC dc(this);
		m_draw_image.Draw(dc, 0, 0);
	}
	else if (m_is_clicked == 2 && CRect(512, 0, 512 + 256, 256).PtInRect(point)) {
		unsigned int *p_src = mp_color_pattern - point.y * 4096 - (255 - (point.x - 512));
		unsigned int* p_dest = mp_pick_pattern;

		for (int i = 0; i < 256; i++) {
			if (i && !(i % 16)) { p_src -= 4096 * 255; }
			*p_dest = *p_src;
			p_src -= 256;
			p_dest--;
		}
		m_pick_image.Draw(m_draw_dc, 0, 512, 512, 512);
		CClientDC dc(this);
		m_draw_image.Draw(dc, 0, 0);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CMFCL114TrueColorDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	m_draw_dc.Detach();
	m_draw_image.ReleaseDC();
}
