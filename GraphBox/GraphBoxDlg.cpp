
// GraphBoxDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "GraphBox.h"


#include "GraphBoxDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphBoxDlg dialog



CGraphBoxDlg::CGraphBoxDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRAPHBOX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_ex = new Ex[100000];
	srand(GetTickCount64());
	Ex* p = m_ex;
	for (int i = 0; i < 100000; i++, p++) {
		p->temp = (rand() % 551 - 150) / 10.0f;
		p->humi = rand() % 99 + 1;				// 1 ~ 99
		p->vib = +9.8f + ((float)rand() / RAND_MAX) * (15.6f - 9.8f);			// 9.8 ~ 15.6
	}
}

void CGraphBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}



BEGIN_MESSAGE_MAP(CGraphBoxDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CGraphBoxDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGraphBoxDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CGraphBoxDlg message handlers

BOOL CGraphBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetDlgItem(IDC_GRAPH_RECT)->GetWindowRect(m_rect1);
	GetDlgItem(IDC_SUB_GRAPH_RECT)->GetWindowRect(m_rect2);
	GetDlgItem(IDC_PIE1)->GetWindowRect(m_pie_rect1);
	GetDlgItem(IDC_PIE2)->GetWindowRect(m_pie_rect2);
	ScreenToClient(m_rect1);
	ScreenToClient(m_rect2);
	ScreenToClient(m_pie_rect1);
	ScreenToClient(m_pie_rect2);

	SetBackgroundColor(RGB(100, 120, 140));

	SetWindowPos(NULL, 0, 0, 1920, 1080, NULL);

	m_dcp.CreateDCP(1920, 1080);

	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGraphBoxDlg::OnPaint()
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
		MyPaint();
		VibPaint();
		PiePaint1();
		PiePaint2();

		m_dcp.Draw(dc);
	}
}

void CGraphBoxDlg::MyPaint()
{
	int x_start = m_rect1.left + 40;
	int x_end = m_rect1.right - 30;
	int y_bottom = m_rect1.bottom - 40;
	int interval = 20;

	// 그래프 기본 바탕
	m_dcp.DCPTextSetting(_T("맑은 고딕"), 11);
	m_dcp.Rectangle(m_rect1.left, m_rect1.top, m_rect1.right, m_rect1.bottom, RGB24(245, 245, 245), RGB24(245, 245, 245));				// 그래프 배경색

	// 그래프 선
	m_dcp.SetPenStyle(Gdiplus::DashStyleSolid, 2);
	m_dcp.MoveTo(x_start, y_bottom);
	m_dcp.LineTo(x_end, y_bottom, RGB24(0, 0, 0));
	m_dcp.SetPenStyle(Gdiplus::DashStyleSolid, 1);
	m_dcp.MoveTo(x_start, y_bottom);
	m_dcp.LineTo(x_start, m_rect1.top + 40, RGB24(15, 15, 15));
	//m_dcp.MoveTo(m_rect1.left + 40, )

	// 최근 6개월 (x축)
	m_dcp.DCPText(x_start, y_bottom + 10, _T("7월"), RGB24(0, 0, 0));
	m_dcp.DCPText(x_start + (x_end - x_start) * 1 / 6, y_bottom + 10, _T("8월"), RGB24(0, 0, 0));
	m_dcp.DCPText(x_start + (x_end - x_start) * 2 / 6, y_bottom + 10, _T("9월"), RGB24(0, 0, 0));
	m_dcp.DCPText(x_start + (x_end - x_start) * 3 / 6, y_bottom + 10, _T("10월"), RGB24(0, 0, 0));
	m_dcp.DCPText(x_start + (x_end - x_start) * 4 / 6, y_bottom + 10, _T("11월"), RGB24(0, 0, 0));
	m_dcp.DCPText(x_start + (x_end - x_start) * 5 / 6, y_bottom + 10, _T("12월"), RGB24(0, 0, 0));

	// 온도범위 (y1축)
	m_dcp.DCPText(x_start - 30, y_bottom - 10, _T("-40"), RGB24(255, 0, 0)); 
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval *1), _T("-35"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 2), _T("-30"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 3), _T("-25"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 4), _T("-20"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 5), _T("-15"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 6), _T("-10"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 7), _T("-5"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 8), _T("0"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 9), _T("5"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 10), _T("10"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 11), _T("15"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 12), _T("20"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 13), _T("25"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 14), _T("30"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 15), _T("35"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 16), _T("40"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 17), _T("45"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 18), _T("50"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 19), _T("55"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 20), _T("60"));

	m_dcp.SetPenStyle(Gdiplus::DashStyleSolid, 5);
	m_dcp.DCPText(x_start - 30, y_bottom - 20 - (interval * 21), _T("온도 (℃)"));
	m_dcp.DrawLine(x_start + 40, y_bottom - 10 - (interval * 21), x_start + 75, y_bottom - 10 - (interval * 21), RGB24(255, 0, 255));				// 온도색깔 안내표시 줄

	// 습도값 안내 수치 (y2축)
	m_dcp.DCPText(x_end, y_bottom - 10, _T("0"), RGB24(0, 0, 255));
	m_dcp.DCPText(x_end, y_bottom - 10 - (interval * 4), _T("20"));
	m_dcp.DCPText(x_end, y_bottom - 10 - (interval * 8), _T("40"));
	m_dcp.DCPText(x_end, y_bottom - 10 - (interval * 12), _T("60"));
	m_dcp.DCPText(x_end, y_bottom - 10 - (interval * 16), _T("80"));
	m_dcp.DCPText(x_end, y_bottom - 10 - (interval * 20), _T("100"));

	m_dcp.DCPText(x_end - 80, y_bottom - 20 - (interval * 21), _T("습도 (%)"));
	m_dcp.DrawLine(x_end - 10 , y_bottom - 10 - (interval * 21), x_end + 25, y_bottom - 10 - (interval * 21), RGB24(0, 0, 255));					// 습도색깔 안내 표시 줄

	// y값 안내선
	m_dcp.SetPenStyle(Gdiplus::DashStyleSolid, 1, RGB32(130, 15, 15, 15));
	for (int i = 0; i < 21; i++) {
		m_dcp.MoveTo(x_start, y_bottom - (i* interval));
		m_dcp.LineTo(x_end, y_bottom - (i* interval));
	}
	
	int y_zero = y_bottom - (interval * 8);
	int y_top = y_bottom - 10 - (interval * 20);

	// 온도 그래프 (선)
	m_dcp.mp_pen->SetLineJoin(Gdiplus::LineJoinRound);
	m_dcp.SetPenStyle(Gdiplus::DashStyleSolid, 2);
	Ex* p = m_ex;
	m_dcp.MoveTo(x_start, y_zero);
	for (int i = 1; i <= 150; i++, p++) {
		m_dcp.LineTo(x_start + (i * ((x_end - x_start)/204)), y_zero - (p->temp)*(interval/5), RGB32(255,255, 99, 71));
	}
	
	// 선위에 점찍기
	//p = m_ex;
	//for (int i = 1; i <= 150; i++, p++) {
	//	m_dcp.FillSolidEllipse(x_start + (i * ((x_end - x_start) / 204)) -4, y_zero - (p->temp) * (interval / 5)-4, x_start + (i * ((x_end - x_start) / 204))+4, y_zero - (p->temp) * (interval / 5)+4, RGB32(255, 255, 255, 255));
	//}
	
	// 습도 그래프 (다각형)
	p = m_ex;
	m_dcp.MoveTo(x_start, y_bottom);
	Gdiplus::Point* humi_points = NULL;
	humi_points = new Gdiplus::Point[152];
	Gdiplus::Point* pos_humi = humi_points;
	*pos_humi = Gdiplus::Point(x_start, y_bottom);
	for (int i = 1; i <= 150; i++, p++) {
		pos_humi++;
		*pos_humi = Gdiplus::Point(x_start + (i * ((x_end - x_start) / 204)), y_bottom - (p->humi) * (interval / 5));
	}
	pos_humi++;
	*pos_humi = Gdiplus::Point((pos_humi -1)->X, y_bottom);
	m_dcp.FillPolygon(humi_points, 152, RGB32(50, 0, 0, 255));
}

void CGraphBoxDlg::VibPaint()
{
	int x_start = m_rect2.left + 40;
	int x_end = m_rect2.right - 30;
	int y_bottom = m_rect2.bottom - 40;
	int interval = 20;

	// 그래프 기본 바탕
	m_dcp.DCPTextSetting(_T("맑은 고딕"), 11);
	m_dcp.Rectangle(m_rect2.left, m_rect2.top, m_rect2.right, m_rect2.bottom, RGB24(245, 245, 245), RGB24(245, 245, 245));

	// 그래프 선
	m_dcp.SetPenStyle(Gdiplus::DashStyleSolid, 2);
	m_dcp.MoveTo(x_start, y_bottom);
	m_dcp.LineTo(x_end, y_bottom, RGB24(0, 0, 0));
	m_dcp.SetPenStyle(Gdiplus::DashStyleSolid, 1);
	m_dcp.MoveTo(x_start, y_bottom);
	m_dcp.LineTo(x_start, m_rect2.top + 40, RGB24(15, 15, 15));

	// 최근 6개월 (x축)
	m_dcp.DCPText(x_start, y_bottom + 10, _T("7월"), RGB24(0, 0, 0));
	m_dcp.DCPText(x_start + (x_end - x_start) * 1 / 6, y_bottom + 10, _T("8월"), RGB24(0, 0, 0));
	m_dcp.DCPText(x_start + (x_end - x_start) * 2 / 6, y_bottom + 10, _T("9월"), RGB24(0, 0, 0));
	m_dcp.DCPText(x_start + (x_end - x_start) * 3 / 6, y_bottom + 10, _T("10월"), RGB24(0, 0, 0));
	m_dcp.DCPText(x_start + (x_end - x_start) * 4 / 6, y_bottom + 10, _T("11월"), RGB24(0, 0, 0));
	m_dcp.DCPText(x_start + (x_end - x_start) * 5 / 6, y_bottom + 10, _T("12월"), RGB24(0, 0, 0));

	// 진동값범위 (y1축)
	m_dcp.DCPText(x_start - 30, y_bottom - 10, _T("0"), RGB24(255, 0, 0));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 1), _T("5"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 2), _T("10"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 3), _T("15"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 4), _T("20"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 5), _T("25"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 6), _T("30"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 7), _T("35"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 8), _T("40"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 9), _T("45"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 10), _T("50"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 11), _T("55"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 12), _T("60"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 13), _T("65"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 14), _T("70"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 15), _T("75"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 16), _T("80"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 17), _T("85"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 18), _T("90"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 19), _T("95"));
	m_dcp.DCPText(x_start - 30, y_bottom - 10 - (interval * 20), _T("100"));

	m_dcp.SetPenStyle(Gdiplus::DashStyleSolid, 5);
	m_dcp.DCPText(x_start - 30, y_bottom - 20 - (interval * 21), _T("진동가속도 (G)"));
	m_dcp.DrawLine(x_start + 90, y_bottom - 10 - (interval * 21), x_start + 125, y_bottom - 10 - (interval * 21), RGB24(128, 0, 128));				// 온도색깔 안내표시 줄

	// y값 안내선
	m_dcp.SetPenStyle(Gdiplus::DashStyleSolid, 1, RGB32(130, 15, 15, 15));
	for (int i = 0; i < 21; i++) {
		m_dcp.MoveTo(x_start, y_bottom - (i * interval));
		m_dcp.LineTo(x_end, y_bottom - (i * interval));
	}

	int y_zero = y_bottom - (interval * 8);
	int y_top = y_bottom - 10 - (interval * 20);

	// 진동 그래프 (선)
	m_dcp.mp_pen->SetLineJoin(Gdiplus::LineJoinRound);
	m_dcp.SetPenStyle(Gdiplus::DashStyleSolid, 2);
	Ex* p = m_ex;
	m_dcp.MoveTo(x_start, y_zero);
	for (int i = 1; i <= 150; i++, p++) {
		m_dcp.LineTo(x_start + (i * ((x_end - x_start) / 204)), y_zero - (p->vib) * (interval / 5), RGB32(255, 255, 99, 71));
	}

	// 선위에 점찍기
	p = m_ex;
	for (int i = 1; i <= 150; i++, p++) {
		m_dcp.FillSolidEllipse(x_start + (i * ((x_end - x_start) / 204)) -4, y_zero - (p->vib) * (interval / 5)-4, x_start + (i * ((x_end - x_start) / 204))+4, y_zero - (p->vib) * (interval / 5)+4, RGB32(255, 0, 255, 0));
	}

}

void CGraphBoxDlg::PiePaint1()
{
	float percentage = 80.0f;
	float arc_percentage = percentage * 360.0f / 100.0f;
	TCHAR str_percentage[20];
	int arc_size = 8;
	float arc_start_x = 50.0f;
	float arc_start_y = 50.0f;
	float arc_end_x = 120.0f;
	float arc_end_y = 120.0f;
	int text_start_x = 60;
	int text_start_y = 85;

	int str_len = _stprintf_s(str_percentage, sizeof(str_percentage)/sizeof(TCHAR), _T("%.1f%%"), percentage);

	// 그래프 기본 바탕
	m_dcp.DCPTextSetting(_T("맑은 고딕"), 24);
	m_dcp.Rectangle(m_pie_rect1.left, m_pie_rect1.top, m_pie_rect1.right, m_pie_rect1.bottom, RGB24(245, 245, 245), RGB24(245, 245, 245));

	m_dcp.SetPenStyle(Gdiplus::DashStyleSolid, arc_size, RGB24(158, 158, 158));
	// 첫 270은 시작위치로 고정, 그 후 돌릴만큼의 각도를 주면 됨
	m_dcp.DrawArc(50.0f, 50.0f, 120.0f, 120.0f, 270.0f, 360.0f);	

	// 첫 270은 시작위치로 고정, 그 후 돌릴만큼의 각도를 주면 됨
	if (percentage > 90) {
		m_dcp.SetPenStyle(Gdiplus::DashStyleSolid, arc_size, RGB24(255, 255, 255));
		m_dcp.DrawArc(50.0f, 50.0f, 120.0f, 120.0f, 270.0f, arc_percentage);

		m_dcp.DCPText(text_start_x, text_start_y, str_percentage, RGB24(255, 255, 255));
	}
	else if (percentage > 60) {
		m_dcp.SetPenStyle(Gdiplus::DashStyleSolid, arc_size, RGB24(255, 255, 0));
		m_dcp.DrawArc(50.0f, 50.0f, 120.0f, 120.0f, 270.0f, arc_percentage);

		m_dcp.DCPText(text_start_x, text_start_y, str_percentage, RGB24(255,255,0));
	}
	else if (percentage > 0) {
		m_dcp.SetPenStyle(Gdiplus::DashStyleSolid, arc_size, RGB24(255, 0, 0));
		m_dcp.DrawArc(50.0f, 50.0f, 120.0f, 120.0f, 270.0f, arc_percentage);

		m_dcp.DCPText(text_start_x, text_start_y, str_percentage, RGB24(255, 0, 0));
	}
}

void CGraphBoxDlg::PiePaint2()
{
	// 그래프 기본 바탕
	m_dcp.DCPTextSetting(_T("맑은 고딕"), 11);
	m_dcp.Rectangle(m_pie_rect2.left, m_pie_rect2.top, m_pie_rect2.right, m_pie_rect2.bottom, RGB24(245, 245, 245), RGB24(245, 245, 245));


}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGraphBoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGraphBoxDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CGraphBoxDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
