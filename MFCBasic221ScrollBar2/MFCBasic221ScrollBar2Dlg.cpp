
// MFCBasic221ScrollBar2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic221ScrollBar2.h"
#include "MFCBasic221ScrollBar2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic221ScrollBar2Dlg dialog



CMFCBasic221ScrollBar2Dlg::CMFCBasic221ScrollBar2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC221SCROLLBAR2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic221ScrollBar2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic221ScrollBar2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCBasic221ScrollBar2Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCBasic221ScrollBar2Dlg message handlers

BOOL CMFCBasic221ScrollBar2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetClientRect(m_rect);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic221ScrollBar2Dlg::OnPaint()
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
		if (!m_img.IsNull()) { 
			int scroll_x_pos = GetScrollPos(SB_HORZ);
			int scroll_y_pos = GetScrollPos(SB_VERT);

			//m_img.Draw(dc, -scroll_x_pos, -scroll_y_pos);					// 스크롤 영역까지 출력
			m_img.Draw(dc, 0, 0, m_rect.Width(), m_rect.Height(), scroll_x_pos, scroll_y_pos, m_rect.Width(), m_rect.Height());					// 스크롤 영역 中 윈도우 영역만큼만 출력
		}
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic221ScrollBar2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic221ScrollBar2Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar == NULL) {
		if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK) {
			SetScrollPos(SB_HORZ, nPos);
		}
		else {
			int scroll_pos = GetScrollPos(SB_HORZ), min = 0, max = 0;
			GetScrollRange(SB_HORZ, &min, &max);
			switch (nSBCode) {
			case SB_LINERIGHT:
				if (scroll_pos < max) SetScrollPos(SB_HORZ, ++scroll_pos);
				break;
			case SB_LINELEFT:
				if (scroll_pos > min) SetScrollPos(SB_HORZ, --scroll_pos);
				break;
			case SB_PAGERIGHT:
				if (scroll_pos + 24 < max) SetScrollPos(SB_HORZ, scroll_pos + 24);
				break;
			case SB_PAGELEFT:
				if (scroll_pos - 24 > min) SetScrollPos(SB_HORZ, scroll_pos - 24);
				break;
			}
		}
		Invalidate(FALSE);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CMFCBasic221ScrollBar2Dlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar == NULL) {
		if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK) {
			SetScrollPos(SB_VERT, nPos);
		}
		else {
			int scroll_pos = GetScrollPos(SB_VERT), min = 0, max = 0;
			GetScrollRange(SB_VERT, &min, &max);
			switch (nSBCode) {
				case SB_LINEDOWN:
					if (scroll_pos < max) SetScrollPos(SB_VERT, ++scroll_pos);
					break;
				case SB_LINEUP:
					if (scroll_pos > min) SetScrollPos(SB_VERT, --scroll_pos);
					break;
				case SB_PAGEDOWN:
					if (scroll_pos + 24 < max) SetScrollPos(SB_VERT, scroll_pos + 24);
					break;
				case SB_PAGEUP:
					if (scroll_pos - 24 > min) SetScrollPos(SB_VERT, scroll_pos - 24);
					break;
			}
		}
		Invalidate(FALSE);
	}
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CMFCBasic221ScrollBar2Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_rect.right = cx;
	m_rect.bottom = cy;

	if(!m_img.IsNull()){						// 창크기가 바뀌어도 스크롤 업데이트
		SetScrollRange(SB_HORZ, 0, m_img.GetWidth() - m_rect.right, 0);					// 그림크기 - 클라이언트사이즈
		SetScrollRange(SB_VERT, 0, m_img.GetHeight() - m_rect.bottom, 0);				// 그림크기 - 클라이언트사이즈
	}
	Invalidate(FALSE);
}


void CMFCBasic221ScrollBar2Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	TCHAR name_filter[] = _T("모든 파일 (*.*)|*.*|Jpeg 파일 (*.jpg)|*.jpg|PNG 파일 (*.png)|*.png||");
	CFileDialog ins_dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_NOCHANGEDIR, name_filter);
	ins_dlg.m_ofn.nFilterIndex = 2;

	if (IDOK == ins_dlg.DoModal()) {
		if (!m_img.IsNull()) { m_img.Destroy(); }
		m_img.Load(ins_dlg.GetPathName());

		SetScrollRange(SB_HORZ, 0, m_img.GetWidth() - m_rect.right, 0);					// 그림크기 - 클라이언트사이즈
		SetScrollRange(SB_VERT, 0, m_img.GetHeight() - m_rect.bottom, 0);				// 그림크기 - 클라이언트사이즈

		Invalidate(FALSE);
	}
}
