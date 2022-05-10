
// MFCL117PaintBrushDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL117PaintBrush.h"

#include "MFCL117PaintBrushDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CMFCL117PaintBrushDlg dialog



CMFCL117PaintBrushDlg::CMFCL117PaintBrushDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL117PAINTBRUSH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL117PaintBrushDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PEN_RADIO, m_pen_radio);
	DDX_Control(pDX, IDC_LINE_RADIO, m_line_radio);
	DDX_Control(pDX, IDC_RECT_RADIO, m_rect_radio);
}

BEGIN_MESSAGE_MAP(CMFCL117PaintBrushDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL117PaintBrushDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL117PaintBrushDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_PEN_RADIO, &CMFCL117PaintBrushDlg::OnBnClickedPenRadio)
	ON_BN_CLICKED(IDC_LINE_RADIO, &CMFCL117PaintBrushDlg::OnBnClickedLineRadio)
	ON_BN_CLICKED(IDC_RECT_RADIO, &CMFCL117PaintBrushDlg::OnBnClickedRectRadio)
END_MESSAGE_MAP()


// CMFCL117PaintBrushDlg message handlers

BOOL CMFCL117PaintBrushDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_pen_radio.SetCheck(1);

	CRect r;
	CWnd* p = GetDlgItem(IDC_PICTURE_CTRL);
	p->GetWindowRect(r);

	ScreenToClient(r);

	m_draw_wnd.Create(nullptr, nullptr, WS_CHILD | WS_VISIBLE | WS_BORDER, r, this, 25000);

	COLORREF color_table[20] = {
		RGB(0,0,0), RGB(0,0,255), RGB(0,255,0), RGB(0,255,255), RGB(255,0,0),
		RGB(255,0,255), RGB(255,255,0), RGB(255,255,255), RGB(0,0,128),
		RGB(0,128,0), RGB(0,128,128), RGB(128,0,0), RGB(128,0,128), 
		RGB(128,128,0), RGB(128,128,128), RGB(192,192,192), RGB(192, 220, 192),
		RGB(166, 202, 240), RGB(255, 251, 240), RGB(160,160,164)
	};

	m_color_list.SubclassDlgItem(IDC_COLOR_LIST, this);
	m_color_list.SetColumnWidth(25);		//각 컬럼 폭 25
	m_color_list.SetItemHeight(0, 25);			// 각 컬럼 높이 25

	for (int i = 0; i < 20; i++) {
		m_color_list.InsertString(i, _T(""));
		m_color_list.SetItemData(i, color_table[i]);
	}

	m_color_list.SetCurSel(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL117PaintBrushDlg::OnPaint()
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
HCURSOR CMFCL117PaintBrushDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL117PaintBrushDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL117PaintBrushDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();
}


void CMFCL117PaintBrushDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	// 다이얼로그 종료 Dlg
	::DestroyWindow(m_hWnd);

	CDialogEx::OnClose();
}


void CMFCL117PaintBrushDlg::OnBnClickedPenRadio()
{
	// TODO: Add your control notification handler code here
	m_draw_wnd.SetDrawType(PEN_MODE);
}


void CMFCL117PaintBrushDlg::OnBnClickedLineRadio()
{
	// TODO: Add your control notification handler code here
	m_draw_wnd.SetDrawType(LINE_MODE);
}


void CMFCL117PaintBrushDlg::OnBnClickedRectRadio()
{
	// TODO: Add your control notification handler code here
	m_draw_wnd.SetDrawType(RECT_MODE);
}
