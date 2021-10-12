
// MFCBasic206DotEditorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic206DotEditor.h"
#include "MFCBasic206DotEditorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic206DotEditorDlg dialog



CMFCBasic206DotEditorDlg::CMFCBasic206DotEditorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC206DOTEDITOR_DIALOG, pParent)
	, m_grid_pen(PS_SOLID, 1, RGB(220, 220, 220))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	for (int y = 0; y < Y_COUNT; y++)
	{
		for (int x = 0; x < X_COUNT; x++)
		{
			m_dot_color[y][x] = RGB(255, 255, 255);
		}
	}

	m_left_color = RGB(0, 0, 255);
	m_right_color = RGB(255, 255, 255);
}

void CMFCBasic206DotEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic206DotEditorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCBasic206DotEditorDlg::OnBnClickedOk)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_LEFT_COLOR_BTN, &CMFCBasic206DotEditorDlg::OnBnClickedLeftColorBtn)
	ON_BN_CLICKED(IDC_RIGHT_COLOR_BTN, &CMFCBasic206DotEditorDlg::OnBnClickedRightColorBtn)
END_MESSAGE_MAP()


// CMFCBasic206DotEditorDlg message handlers

BOOL CMFCBasic206DotEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetDlgItem(IDC_LEFT_COLOR_BTN)->GetWindowRect(m_left_rect);
	ScreenToClient(m_left_rect);
	m_left_rect.left -= 10;
	m_left_rect.right = m_left_rect.left + 5;

	GetDlgItem(IDC_RIGHT_COLOR_BTN)->GetWindowRect(m_right_rect);
	ScreenToClient(m_right_rect);
	m_right_rect.left -= 10;
	m_right_rect.right = m_right_rect.left + 5;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic206DotEditorDlg::OnPaint()
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
		CPen* p_old_pen = dc.SelectObject(&m_grid_pen);
		CBrush* p_old_brush = dc.GetCurrentBrush();
		dc.SelectStockObject(DC_BRUSH);

		for (int y = 0; y < Y_COUNT; y++){
			for (int x = 0; x < X_COUNT; x++) {
				dc.SetDCBrushColor(m_dot_color[y][x]);
				dc.Rectangle(0 + x * RECT_INTERVAL, 0 + y * RECT_INTERVAL, 1+ RECT_INTERVAL + x * RECT_INTERVAL, 1+ RECT_INTERVAL + y * RECT_INTERVAL);
			}
		}

		dc.SetDCBrushColor(m_left_color);
		dc.Rectangle(m_left_rect);
		dc.SetDCBrushColor(m_right_color);
		dc.Rectangle(m_right_rect);

		dc.SelectObject(p_old_brush);
		dc.SelectObject(p_old_pen);
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic206DotEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic206DotEditorDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCBasic206DotEditorDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (nFlags & (MK_LBUTTON | MK_RBUTTON))
	{
		int x = point.x / RECT_INTERVAL;
		int y = point.y / RECT_INTERVAL;

		if (x < X_COUNT && y < Y_COUNT) {
			if (nFlags & MK_LBUTTON) m_dot_color[y][x] = m_left_color;
			else m_dot_color[y][x] = m_right_color;

			CClientDC dc(this);
			CPen* p_old_pen = dc.SelectObject(&m_grid_pen);
			CGdiObject* p_old_brush = dc.SelectStockObject(DC_BRUSH);
			dc.SetDCBrushColor(m_dot_color[y][x]);
			dc.Rectangle(0 + x * RECT_INTERVAL, 0 + y * RECT_INTERVAL, 1 + RECT_INTERVAL + x * RECT_INTERVAL, 1 + RECT_INTERVAL + y * RECT_INTERVAL);

			dc.SelectObject(p_old_brush);
			dc.SelectObject(p_old_pen);
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CMFCBasic206DotEditorDlg::OnBnClickedLeftColorBtn()
{
	// TODO: Add your control notification handler code here
	CColorDialog ins_dlg;
	ins_dlg.m_cc.Flags = ins_dlg.m_cc.Flags | CC_FULLOPEN | CC_RGBINIT;
	ins_dlg.m_cc.rgbResult = m_left_color;
	
	if (IDOK == ins_dlg.DoModal()) {
		m_left_color = ins_dlg.GetColor();
		InvalidateRect(m_left_rect, FALSE);
	}
}


void CMFCBasic206DotEditorDlg::OnBnClickedRightColorBtn()
{
	// TODO: Add your control notification handler code here
	CColorDialog ins_dlg;
	ins_dlg.m_cc.Flags = ins_dlg.m_cc.Flags | CC_FULLOPEN | CC_RGBINIT;
	ins_dlg.m_cc.rgbResult = m_right_color;
	if (IDOK == ins_dlg.DoModal()) {
		m_right_color = ins_dlg.GetColor();
		InvalidateRect(m_right_rect, FALSE);
	}
}
