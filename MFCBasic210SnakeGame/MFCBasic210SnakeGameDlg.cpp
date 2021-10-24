
// MFCBasic210SnakeGameDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic210SnakeGame.h"
#include "MFCBasic210SnakeGameDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic210SnakeGameDlg dialog



CMFCBasic210SnakeGameDlg::CMFCBasic210SnakeGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC210SNAKEGAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic210SnakeGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic210SnakeGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCBasic210SnakeGameDlg message handlers

BOOL CMFCBasic210SnakeGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_draw_image.Create(801, 601, 32);			// 32bit색상
	m_draw_dc.Attach(m_draw_image.GetDC());				// 메모리DC

	srand((unsigned int)time(NULL));				// time이 64bit로 바껴서 unsigned int로 캐스팅하여 32bit
	int x, y;
	for (int i = 0; i < 300; i++) {
		x = rand() % 80;
		y = rand() % 60;
		if (m_table[y][x] == 0) m_table[y][x] = RGB(255, 0, 0);
		else i--;
	}

	m_table[m_pos.y][m_pos.x] = RGB(0, 255, 0);

	m_draw_dc.SelectStockObject(DC_BRUSH);
	m_draw_dc.SelectStockObject(DC_PEN);
	m_draw_dc.SetDCPenColor(RGB(48, 48, 12));			// 어두운 노란색
	//m_draw_dc.SetDCBrushColor(RGB(0,0,0));			// 검은색

	for (int y = 0; y < 60; y++) {
		for (int x = 0; x < 80; x++) {
			m_draw_dc.SetDCBrushColor(m_table[y][x]);			// 색깔
			m_draw_dc.Rectangle(x * 10, y * 10, x * 10 + 11, y * 10 + 11);			// 격자
		}
	}

	SetTimer(1, 200, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic210SnakeGameDlg::OnPaint()
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
HCURSOR CMFCBasic210SnakeGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic210SnakeGameDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);
	m_draw_dc.Detach();
	m_draw_image.ReleaseDC();			// 메모리DC 해제
}


void CMFCBasic210SnakeGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {

	}else CDialogEx::OnTimer(nIDEvent);
}
