
// GdiplusGuideDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "GdiplusGuide.h"

#include <gdiplus.h>


#include "GdiplusGuideDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGdiplusGuideDlg dialog



CGdiplusGuideDlg::CGdiplusGuideDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GDIPLUSGUIDE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	Gdiplus::GdiplusStartupInput gpsi;
	GdiplusStartup(&m_token, &gpsi, NULL);				// **GDI+ 관련 DLL과 연결
}


void CGdiplusGuideDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGdiplusGuideDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CGdiplusGuideDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGdiplusGuideDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CGdiplusGuideDlg message handlers

BOOL CGdiplusGuideDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetMemDC();

	//Gdiplus::DllExports::GdipCreateFromHDC(mh_mem_dc, &mp_graphics);				// **HDC와 연결해서 사용하는 GDI+ 출력 생성 --> 현재 윈도우 핸들에 연결해서 사용하는 GDI+ 출력 생성 --> Memory DC에 연결해서 사용하는 GDI+ 출력 생성
	Gdiplus::DllExports::GdipCreatePen1(0xFFFF0000, 1, Gdiplus::UnitWorld, &mp_pen);				// 붉은색 , 굵기 1
	
	// 'AntiAlias' 사용
	Gdiplus::DllExports::GdipSetSmoothingMode(mp_graphics, Gdiplus::SmoothingModeAntiAlias);

	// 배경색
	Gdiplus::DllExports::GdipGraphicsClear(mp_graphics, 0x440000FF);				// AARRGGBB

	Gdiplus::DllExports::GdipDrawRectangleI(mp_graphics, mp_pen, 30, 30, 300, 180);				// 30, 30, 300, 180
	Gdiplus::DllExports::GdipSetPenWidth(mp_pen, 10);				// 굵기를 10으로 변경
	Gdiplus::DllExports::GdipSetPenColor(mp_pen, 0x50600000);				// Red를 255에서 96으로 변경, 투명도를 255에서 80으로 변경

	GdipSetPenMode(mp_pen, PenAlignmentInset);				// 선이 굵어져도 영역 안쪽으로만 그려지게 설정 변경

	GdipDrawRectangleI(mp_graphics, mp_pen, 30, 30, 300, 180);				// 30, 30, 300, 180

	Gdiplus::DllExports::GdipDeletePen(mp_pen);
	Gdiplus::DllExports::GdipCreatePen1(0xFFFF0000, 7, Gdiplus::UnitWorld, &mp_pen);

	for (int i = 0; i < 5; i++) {
		//Gdiplus::DllExports::GdipSetPenEndCap(mp_pen, (LineCap)(0x10 + i));					// 펜의 끝 위치 모양을 지정
		//Gdiplus::DllExports::GdipSetPenStartCap(mp_pen, (LineCap)(0x10 + i));				// 펜의 시작위치 모양을 지정

		Gdiplus::DllExports::GdipSetPenDashStyle(mp_pen, (DashStyle)i);
		Gdiplus::DllExports::GdipDrawLineI(mp_graphics, mp_pen, 20, 20 + i * 16, 300, 20 + i * 16);				// 선을 그린다
	}

	Gdiplus::DllExports::GdipDeletePen(mp_pen);
	Gdiplus::DllExports::GdipCreatePen1(0xFFFF0000, 7, Gdiplus::UnitWorld, &mp_pen);
	Gdiplus::Point star_pos[11] = { {121,20}, {97,97}, {20,97}, {82,145}, {59,221}, {121,173}, {183,221}, {158,145}, {221,97}, {144,97}, {121,20} };

	// 11개의 점으로 10개의 선을 그린다
	//for (int i = 0; i < 10; i++) {
	//	GdipDrawLineI(mp_graphics, mp_pen, star_pos[i].X, star_pos[i].Y, star_pos[i + 1].X, star_pos[i + 1].Y);
	//}

	GdipSetPenLineJoin(mp_pen, LineJoinRound);				// 선과 선이 만나는 지점을 LineJoinRound로 변경
	GdipSetPenStartCap(mp_pen, LineCapRound);				// 선 시작점 둥글게
	GdipSetPenEndCap(mp_pen, LineCapRound);				// 선 끝점 둥글게

	GdipDrawLinesI(mp_graphics, mp_pen, star_pos, 11);

	GdipCreateSolidFill(0xFF00FF00, &mp_brush);				// 초록색 브러시 (알파 255)
	GdipFillRectangle(mp_graphics, mp_brush, 430, 30, 150, 150);				// 사각형

	GdipSetSolidFillColor(mp_brush, 0x700000FF);				// 브러시 변경 (알파 0x70 블루)
	GdipFillRectangle(mp_graphics, mp_brush, 460, 60, 150, 150);					// 사각형

	GdipSetSolidFillColor(mp_brush, 0x30FF00FF);				// 브러시 변경 (알파 0x30 핑크)
	GdipFillEllipse(mp_graphics, mp_brush, 520, 80, 170, 170);



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGdiplusGuideDlg::SetMemDC()
{
	//CClientDC dc(this);																			// Memory DC를 생성하기 위한 이 클래스의 DC를 얻는다
	//mh_mem_dc = CreateCompatibleDC(dc);											// Memory DC 생성!
	//mh_mem_bmp = CreateCompatibleBitmap(dc, 200, 200);					// Memory DC에 연결될 비트맵을 200, 200 크기로 생성!
	//::SelectObject(mh_mem_dc, mh_mem_bmp);									// MemDC와 비트맵을 연결!
	CRect rect;
	GetWindowRect(&rect);
	int width = rect.Width();
	int height = rect.Height();

	Gdiplus::DllExports::GdipCreateBitmapFromScan0(width, height, 0, PixelFormat64bppARGB, NULL, &mp_bitmap);
	Gdiplus::DllExports::GdipGetImageGraphicsContext(mp_bitmap, &mp_graphics);

}

void CGdiplusGuideDlg::DeleteMemDC()
{
	//::DeleteDC(mh_mem_dc);					// Memory DC 제거
	//::DeleteObject(mh_mem_bmp);			// Memory DC의 비트맵 제거
}




// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGdiplusGuideDlg::OnPaint()
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
		// Memory DC 를 0,0 ~ 200,200 만큼 카피한다
		//::BitBlt(dc, 0, 0, 200, 200, mh_mem_dc, 0, 0, SRCCOPY);
		
		Gdiplus::GpGraphics* p_graphics = NULL;
		Gdiplus::DllExports::GdipCreateFromHDC(dc, &p_graphics);					// 연결
		Gdiplus::DllExports::GdipDrawImageI(p_graphics, mp_bitmap, 0, 0);				// 비트맵을 화면의 0,0 위치에 출력
		Gdiplus::DllExports::GdipDeleteGraphics(p_graphics);				// 출력용 GDI+ 제거
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGdiplusGuideDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGdiplusGuideDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CGdiplusGuideDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CGdiplusGuideDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	Gdiplus::DllExports::GdipDeletePen(mp_pen);
	Gdiplus::DllExports::GdipDeleteBrush(mp_brush);

	Gdiplus::DllExports::GdipDeleteGraphics(mp_graphics);				// GDI+ 출력 제거
	Gdiplus::DllExports::GdipFree(mp_bitmap);
	Gdiplus::GdiplusShutdown(m_token);				// GDI+ 관련 DLL과 연결을 해제한다

	//DeleteMemDC();
}
