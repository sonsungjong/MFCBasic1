
// GdipUserControl1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "GdipUserControl1.h"

#include "InputData.h"


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

	mp_mqtt = new MqttManager();

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
	ON_BN_CLICKED(30001, &CGdipUserControl1Dlg::OnBnClickedLoadData)
	ON_BN_CLICKED(30002, &CGdipUserControl1Dlg::OnBnClickedSetting)
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
	GetClientRect(&m_full_size);

	// 영역 설정
	m_row1.SetRect(0, 0, m_full_size.Width(), m_full_size.Height() / 27);
	m_row2.SetRect(0, m_full_size.Height() / 27, m_full_size.Width(), m_full_size.Height() / 27 + m_full_size.Height() / 18);
	m_row4.SetRect(0, m_full_size.Height() * 4 / 10, m_full_size.Width(), m_full_size.Height() *7/10);
	m_row5.SetRect(0, m_full_size.Height() * 7 / 10, m_full_size.Width(), m_full_size.Height());
	m_row3.SetRect(0, m_row2.bottom, m_full_size.Width(), m_row4.top);

	m_close_rect.SetRect(m_row1.right - 40, m_row1.top + 5, m_row1.right - 5, m_row1.bottom - 5);
	m_min_rect.SetRect(m_row1.right - 85, m_row1.top + 5, m_row1.right - 55, m_row1.bottom - 5);
	m_search_rect.SetRect(m_full_size.Width() *70/ 100, m_row2.top, m_full_size.Width(), m_row2.bottom);
	m_listctrl_rect.SetRect(0, m_row3.top, m_full_size.Width() * 70 / 100, m_row3.bottom);
	m_listbox_rect.SetRect(m_full_size.Width() * 70 / 100, m_row3.top, m_full_size.Width(), m_row3.bottom);
	m_temp_graph_rect.SetRect(0, m_row4.top, m_full_size.Width() * 70 / 100, m_row4.bottom);
	m_info_rect1.SetRect(m_full_size.Width() * 70 / 100, m_row4.top, m_full_size.Width(), m_row4.bottom);
	m_vib_graph_rect.SetRect(0, m_row5.top, m_full_size.Width() * 70 / 100, m_row5.bottom);
	m_info_rect2.SetRect(m_full_size.Width() * 70 / 100, m_row5.top, m_full_size.Width(), m_row5.bottom);
	for (int idx = 0; idx < sizeof(m_menu_btn_rect) / sizeof(m_menu_btn_rect[0]); ++idx) {
		m_menu_btn_rect[idx].SetRect(m_menu_btn_size*(idx), m_row2.top, m_menu_btn_size * (idx + 1), m_row2.bottom);
	}
	if (m_full_size.Height() < 800) {
		m_font_size = 7;
	}
	else if (m_full_size.Height() < 1200) {
		m_font_size = 14;
	}
	else {
		m_font_size = 21;
	}
	
	// GDI+ 설정
	m_dcp.CreateDCP(m_screen_width, m_screen_height);
	m_dcp.DCPTextSetting(_T("맑은 고딕"), m_font_size);
	m_dcp.DCPImage(_T("..\\img\\천궁2.png"), 0, 0, m_screen_width, m_screen_height);
	m_dcp.FillSolidRect(0, 0, m_screen_width, m_screen_height, RGB32(220, 0, 84, 165));

	// 영역 표시

	// 컨트롤
	//m_font_edit = ::CreateFont(24, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
	//m_edit_ctrl.Create(WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, CRect(m_row2.right - 300, m_row2.top + 25, m_row2.right - 100, m_row2.bottom -25), this, 30001);
	//m_edit_ctrl.SendMessage(WM_SETFONT, (WPARAM)m_font_edit, TRUE);
	m_btn_load_data.Create(_T("유도탄 데이터 입력"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(m_menu_btn_rect[0].left, m_menu_btn_rect[0].top, m_menu_btn_rect[0].right, m_menu_btn_rect[0].bottom), this, 30001);
	m_btn_setting.Create(_T("설정"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(m_menu_btn_rect[1].left, m_menu_btn_rect[1].top, m_menu_btn_rect[1].right, m_menu_btn_rect[1].bottom), this, 30002);



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
		m_dcp.Rectangle(0, 0, m_row1.Width(), m_row1.Height(), RGB24(7, 60, 130), RGB24(7, 60, 130));
		m_dcp.Rectangle(m_row2.left, m_row2.top, m_row2.right, m_row2.bottom, RGB24(192, 192, 192), RGB24(192, 192, 192));
		m_dcp.DrawRect(m_row3.left, m_row3.top, m_row3.right, m_row3.bottom, RGB24(255, 0, 0));
		m_dcp.DrawRect(m_row4.left, m_row4.top, m_row4.right, m_row4.bottom, RGB24(0, 255, 0));
		m_dcp.DrawRect(m_row5.left, m_row5.top, m_row5.right, m_row5.bottom, RGB24(0, 0, 255));

		// 범위테스트
		CRect* p = m_menu_btn_rect;
		for (int idx = 0; idx < sizeof(m_menu_btn_rect) / sizeof(m_menu_btn_rect[0]);++idx, ++p) {
			m_dcp.DrawRect(p->left, p->top, p->right, p->bottom, RGB24(165, 165, 165));
		}
		m_dcp.DCPText(m_search_rect.left, m_search_rect.top, _T("검색란"), RGB24(0,0,0));
		m_dcp.DCPText(m_listctrl_rect.left, m_listctrl_rect.top, _T("통합DB란"));
		m_dcp.DCPText(m_listbox_rect.left, m_listbox_rect.top, _T("리스트박스"));
		m_dcp.Rectangle(m_temp_graph_rect.left + 7, m_temp_graph_rect.top + 7, m_temp_graph_rect.right - 7, m_temp_graph_rect.bottom - 7, RGB24(0, 0, 0), RGB24(255, 255, 255));
		m_dcp.DCPText(m_temp_graph_rect.left, m_temp_graph_rect.top, _T("그래프1"));
		m_dcp.DCPText(m_info_rect1.left, m_info_rect1.top, _T("텍스트1"));
		m_dcp.Rectangle(m_vib_graph_rect.left + 7, m_vib_graph_rect.top + 7, m_vib_graph_rect.right - 7, m_vib_graph_rect.bottom - 7, RGB24(0, 0, 0), RGB24(255, 255, 255));
		m_dcp.DCPText(m_vib_graph_rect.left, m_vib_graph_rect.top, _T("그래프2"));
		m_dcp.DCPText(m_info_rect2.left, m_info_rect2.top, _T("텍스트2"));

		// 제목
		m_dcp.DCPText(7, 7, _T("상태정보기반 수명주기예측 통합시스템"), RGB24(190, 190, 190));
		m_dcp.DCPImage(m_close_path, m_close_rect.left, m_close_rect.top, m_close_rect.Width(), m_close_rect.Height());
		
		if (m_flag_min_on == 0) {
			m_dcp.DrawRect(m_min_rect.left, m_min_rect.top + 15, m_min_rect.right, m_min_rect.bottom - 15, RGB24(0, 0, 0));
		}
		else {
			m_dcp.Rectangle(m_min_rect.left, m_min_rect.top + 15, m_min_rect.right, m_min_rect.bottom - 15, RGB24(0, 0, 255), RGB24(0,0,255));
		}
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
	::DeleteObject(m_font_edit);
}


void CGdipUserControl1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_close_rect.PtInRect(point)) {
		if (m_flag_close_on == 1) {
			OnClose();
		}
	}
	else if (m_min_rect.PtInRect(point)) {
		if (m_flag_min_on == 1) {
			ShowWindow(SW_MINIMIZE);
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
			InvalidateRect(&m_close_rect, 0);
		}
	}
	else {
		if (m_flag_close_on == 1) {
			m_flag_close_on = 0;
			memset(m_close_path, 0, MAX_PATH);
			_stprintf_s(m_close_path, MAX_PATH, _T("..\\img\\whiteclose48.png"));
			InvalidateRect(&m_close_rect, 0);
		}
	}

	if (m_min_rect.PtInRect(point)) {
		if (m_flag_min_on == 0) {
			m_flag_min_on = 1;
			InvalidateRect(&m_min_rect, 0);
		}
	}
	else {
		if (m_flag_min_on == 1) {
			m_flag_min_on = 0;
			InvalidateRect(&m_min_rect, 0);
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


void CGdipUserControl1Dlg::OnBnClickedSetting()
{
	mp_mqtt->SendMsg("ai", "{\"ai\":\"req\"}");
}

void CGdipUserControl1Dlg::OnBnClickedLoadData()
{
	InputData dlg;
	INT_PTR result = dlg.DoModal();
	if (result == IDOK) {
		AfxMessageBox(L"hello");
	}
}

void CGdipUserControl1Dlg::TestMethod()
{
	AfxMessageBox(L"메시지 받음");
}