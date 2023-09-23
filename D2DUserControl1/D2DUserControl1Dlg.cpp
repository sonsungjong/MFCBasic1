
// D2DUserControl1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "D2DUserControl1.h"
#include "D2DUserControl1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CD2DUserControl1Dlg dialog



CD2DUserControl1Dlg::CD2DUserControl1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_D2DUSERCONTROL1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CD2DUserControl1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CD2DUserControl1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CD2DUserControl1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CD2DUserControl1Dlg::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CD2DUserControl1Dlg message handlers

BOOL CD2DUserControl1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// 전체화면
	m_screen_width = GetSystemMetrics(SM_CXSCREEN);
	m_screen_height = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(NULL, 0, 0, m_screen_width, m_screen_height, SWP_NOZORDER);
	
	// 배경이미지를 화면에 맞게 사이즈 조정해서 출력
	GetClientRect(&m_full_size);
	m_top_system_bar.SetRect(0, 0, m_full_size.Width(), m_full_size.Height() / 27);

	// D2D 연결
	m_wnd_full.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, m_full_size, this, 29901);
	m_d2d[0].SetWndTarget(m_wnd_full, m_full_size);

	m_wnd_system_bar.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, m_top_system_bar, this, 29002);
	m_d2d[1].SetWndTarget(m_wnd_system_bar, m_top_system_bar);
	 
	m_d2d[0].D2DRenderBegin();
	m_d2d[0].D2DPng(0, 0, m_full_size.Width(), m_full_size.Height(), _T("..\\img\\천궁2.png"));
	m_d2d[0].D2DRenderEnd();



	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CD2DUserControl1Dlg::OnPaint()
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
		m_d2d[0].D2DRenderBegin();
		m_d2d[0].D2DRectangle(0, 0, m_full_size.Width(), m_full_size.Height(), D2D_RGBA(0, 84, 165, 220));
		m_d2d[0].D2DRenderEnd();

		m_d2d[1].D2DRenderBegin();
		m_d2d[1].D2DBackground(D2D_RGBA(7, 60, 130, 255));
		m_d2d[1].D2DTextOut(_T("상태정보데이터기반 수명주기관리 통합시스템"), 7, 7, 24, D2D_RGBA(188, 189, 193, 255), _T("맑은 고딕"));
		//m_d2d[1].D2DRectangle(m_top_system_bar.right - 35, m_top_system_bar.top + 5, m_top_system_bar.right - 5, m_top_system_bar.bottom - 5, D2D_RGBA(255, 0, 0, 255));
		m_d2d[1].D2DPng(m_top_system_bar.right - 35, m_top_system_bar.top + 5, m_top_system_bar.right - 5, m_top_system_bar.bottom - 5, _T("..\\img\\whiteclose48.png"));
		m_d2d[1].D2DRenderEnd();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CD2DUserControl1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CD2DUserControl1Dlg::OnBnClickedOk()
{
	//CDialogEx::OnOK();
}


void CD2DUserControl1Dlg::OnBnClickedCancel()
{
	//CDialogEx::OnCancel();
	EndDialog(IDCANCEL);					// 모달 다이얼로그 종료
	// DestroyWindow();						// 모달리스 다이얼로그 종료
	// PostMessage(WM_CLOSE);			// WM_CLOSE 메시지 호출
}


HBRUSH CD2DUserControl1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

	return hbr;
}


