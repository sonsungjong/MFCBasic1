
// GdipUserControl1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "GdipUserControl1.h"
#include "GdipUserControl1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGdipUserControl1Dlg dialog



CGdipUserControl1Dlg::CGdipUserControl1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GDIPUSERCONTROL1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	memset(m_close_path, 0, MAX_PATH);
	_stprintf_s(m_close_path, MAX_PATH, _T("..\\img\\whiteclose48.png"));
}

void CGdipUserControl1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGdipUserControl1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CGdipUserControl1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGdipUserControl1Dlg::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CGdipUserControl1Dlg message handlers

BOOL CGdipUserControl1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// 전체화면
	m_screen_width = GetSystemMetrics(SM_CXSCREEN);
	m_screen_height = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(NULL, 0, 0, m_screen_width, m_screen_height, SWP_NOZORDER);

	// 영역 설정
	GetClientRect(&m_full_size);
	m_top_system_bar.SetRect(0, 0, m_full_size.Width(), m_full_size.Height() / 27);
	m_menu_bar.SetRect(0, m_top_system_bar.bottom, m_full_size.Width(), m_top_system_bar.bottom+m_full_size.Height()/18);
	m_close_rect.SetRect(m_top_system_bar.right - 35, m_top_system_bar.top + 5, m_top_system_bar.right - 5, m_top_system_bar.bottom - 5);
	for (int idx = 0; idx < sizeof(m_menu_btn_rect) / sizeof(m_menu_btn_rect[0]); ++idx) {
		m_menu_btn_rect[idx].SetRect(0, m_menu_bar.top, m_menu_btn_size*(idx+1), m_menu_bar.bottom);
	}
	
	// GDI+ 설정
	m_dcp.CreateDCP(m_screen_width, m_screen_height);
	m_dcp.DCPTextSetting(_T("맑은 고딕"), 14);
	m_dcp.Clear(RGB24(0, 0, 180));


	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CGdipUserControl1Dlg::OnPaint()
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
		// 영역 표시
		m_dcp.DCPImage(_T("..\\img\\jeju.png"), 0, 0, m_screen_width, m_screen_height);
		m_dcp.Rectangle(0, 0, m_screen_width, m_screen_height, RGB24(0, 84, 165), RGB32(220, 0, 84, 165));
		m_dcp.Rectangle(0, 0, m_top_system_bar.Width(), m_top_system_bar.Height(), RGB24(7, 60, 130), RGB24(7, 60, 130));
		m_dcp.Rectangle(m_menu_bar.left, m_menu_bar.top, m_menu_bar.right, m_menu_bar.bottom, RGB24(255, 255, 255), RGB24(255, 255, 255));
		CRect* p = m_menu_btn_rect;
		for (int idx = 0; idx < sizeof(m_menu_btn_rect) / sizeof(m_menu_btn_rect[0]);++idx) {
			m_dcp.DrawRect(p->left, p->top, p->right, p->bottom, RGB24(255, 0, 0));
			p++;
		}

		// 제목
		m_dcp.DCPText(7, 7, _T("상태정보기반 수명주기예측 통합시스템"), RGB24(190, 190, 190));
		m_dcp.DCPImage(m_close_path, m_close_rect.left, m_close_rect.top, m_close_rect.Width(), m_close_rect.Height());
		// 끝
		m_dcp.Draw(dc);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGdipUserControl1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGdipUserControl1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
	Invalidate();
}


void CGdipUserControl1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();
}

HBRUSH CGdipUserControl1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void CGdipUserControl1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


void CGdipUserControl1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_close_rect.PtInRect(point)) {
		if (m_flag_close_on == 1) {
			OnClose();
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CGdipUserControl1Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CGdipUserControl1Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_close_rect.PtInRect(point)) {
		if (m_flag_close_on == 0) {
			m_flag_close_on = 1;
			memset(m_close_path, 0, MAX_PATH);
			_stprintf_s(m_close_path, MAX_PATH, _T("..\\img\\close48.png"));
			Invalidate(0);
		}
	}
	else {
		if (m_flag_close_on == 1) {
			m_flag_close_on = 0;
			memset(m_close_path, 0, MAX_PATH);
			_stprintf_s(m_close_path, MAX_PATH, _T("..\\img\\whiteclose48.png"));
			Invalidate(0);
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CGdipUserControl1Dlg::OnClose()
{
	int result = ::MessageBox(this->GetSafeHwnd(), _T("프로그램이 종료됩니다."), _T("프로그램 종료"), MB_OKCANCEL | MB_ICONINFORMATION);
	if (result == IDOK) {
		EndDialog(IDCANCEL);					// 모달 다이얼로그 종료
		// DestroyWindow();						// 모달리스 다이얼로그 종료
		// PostMessage(WM_CLOSE);			// WM_CLOSE 메시지 호출
	}

	CDialogEx::OnClose();
}
