
// D2DBarGraph3Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "D2DBarGraph3.h"
#include "D2DBarGraph3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CD2DBarGraph3Dlg dialog



CD2DBarGraph3Dlg::CD2DBarGraph3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_D2DBARGRAPH3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CD2DBarGraph3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CD2DBarGraph3Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CD2DBarGraph3Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CD2DBarGraph3Dlg::OnBnClickedCancel)
	
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CD2DBarGraph3Dlg message handlers

BOOL CD2DBarGraph3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetWindowPos(0, 0, 0, 1920, 1080, 0);
	SetBackgroundColor(RGB(50, 70, 90));


	m_d2d_rect[0].SetRect(20, 20, 700, 700);
	m_d2d_rect[1].SetRect(1000, 20, 1500, 700);
	m_d2d_rect[2].SetRect(20, 800, 700, 1200);

	m_d2d_wnd[0].Create(NULL, NULL, WS_CHILD | WS_VISIBLE, m_d2d_rect[0], this, 29001);
	m_d2d_wnd[1].Create(NULL, NULL, WS_CHILD | WS_VISIBLE, m_d2d_rect[1], this, 29002);
	m_d2d_wnd[2].Create(NULL, NULL, WS_CHILD | WS_VISIBLE, m_d2d_rect[2], this, 29003);

	m_d2d[0].SetWndTarget(m_d2d_wnd[0], m_d2d_rect[0]);
	m_d2d[1].SetWndTarget(m_d2d_wnd[1], m_d2d_rect[1]);
	m_d2d[2].SetWndTarget(m_d2d_wnd[2], m_d2d_rect[2]);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CD2DBarGraph3Dlg::OnPaint()
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
		m_d2d[0].D2DRenderBegin();
		m_d2d[0].D2DBackground({ 1.0f, 0.0f, 0.0f, 0.3f });
		m_d2d[0].D2DTextOut(_T("글자쓰기"), 100, 100);
		m_d2d[0].D2DTextOut(_T("show me the money 안녕"), 150, 150);
		m_d2d[0].D2DBarGraph();
		m_d2d[0].D2DRenderEnd();

		m_d2d[1].D2DRenderBegin();
		m_d2d[1].D2DBackground({ 0.0f, 1.0f, 0.0f, 0.3f });
		m_d2d[1].D2DTextOut(_T("안녕하세요 반갑습니다"), 300.0f, 300.0f);
		m_d2d[1].D2DRectangle(300.0f, 300.0f, 350.0f, 350.0f);
		m_d2d[1].D2DBarGraph();
		m_d2d[1].D2DRenderEnd();

		m_d2d[2].D2DRenderBegin();
		m_d2d[2].D2DBackground({0.0f, 0.0f, 1.0f, 0.3f});
		m_d2d[2].D2DBarGraph();
		m_d2d[2].D2DRenderEnd();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CD2DBarGraph3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CD2DBarGraph3Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CD2DBarGraph3Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


HBRUSH CD2DBarGraph3Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	UINT nID = pWnd->GetDlgCtrlID();

	switch (nID) {
	case IDC_STATIC:
		pDC->SetBkMode(TRANSPARENT);
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);
		break;
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
