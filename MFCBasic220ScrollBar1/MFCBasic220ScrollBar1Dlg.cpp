
// MFCBasic220ScrollBar1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic220ScrollBar1.h"
#include "MFCBasic220ScrollBar1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic220ScrollBar1Dlg dialog



CMFCBasic220ScrollBar1Dlg::CMFCBasic220ScrollBar1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC220SCROLLBAR1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic220ScrollBar1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic220ScrollBar1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMFCBasic220ScrollBar1Dlg message handlers

BOOL CMFCBasic220ScrollBar1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CRect rect;
	GetClientRect(rect);

	SetScrollRange(SB_VERT, 0, 8*9*24 - rect.Height() +10, 0);							// 스크롤 범위

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic220ScrollBar1Dlg::OnPaint()
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
		CString str;
		int count = 0;
		dc.SetBkMode(TRANSPARENT);						// 배경을 투명으로
		dc.SetTextColor(RGB(0, 0, 200));					// 글자색변경

		int scroll_pos = GetScrollPos(SB_VERT);				// Vertical 스크롤바의 현재 위치

		//CDialogEx::OnPaint();
		for (int dan = 2; dan < 10; dan++){
			for (int i = 1; i < 10; i++){
				str.Format(_T("%d x %d = %d"), dan, i, dan*i);
				dc.TextOut(10, 5 + count * 24 - scroll_pos, str);						// 스크롤 위치에 따라 출력범위 변경
				count++;
			}
		}
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic220ScrollBar1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic220ScrollBar1Dlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar == NULL) {				// 윈도우 속성 스크롤바
		if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK) {
			SetScrollPos(SB_VERT, nPos);
		}
		else {
			int scroll_pos = GetScrollPos(SB_VERT), min=0, max=0;
			GetScrollRange(SB_VERT, &min, &max);

			switch (nSBCode) {
				case SB_LINEDOWN:
					if(scroll_pos < max) SetScrollPos(SB_VERT, ++scroll_pos);
					break;
				case SB_LINEUP:
					if (scroll_pos > min) SetScrollPos(SB_VERT, --scroll_pos);
					break;
				case SB_PAGEDOWN:
					if (scroll_pos +24< max) SetScrollPos(SB_VERT, scroll_pos+24);
					break;
				case SB_PAGEUP:
					if (scroll_pos -24> min) SetScrollPos(SB_VERT, scroll_pos - 24);
					break;
			}
		}
		Invalidate();
	}
	
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CMFCBasic220ScrollBar1Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CRect rect;
	GetClientRect(rect);

	SetScrollRange(SB_VERT, 0, 8 * 9 * 24 - rect.Height() + 10, 0);							// 스크롤 범위
	Invalidate();
}
