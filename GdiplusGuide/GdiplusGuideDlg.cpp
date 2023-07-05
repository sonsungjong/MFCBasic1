
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
	GdiplusStartup(&m_token, &gpsi, NULL);				// **GDI+ ���� DLL�� ����
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

	//Gdiplus::DllExports::GdipCreateFromHDC(mh_mem_dc, &mp_graphics);				// **HDC�� �����ؼ� ����ϴ� GDI+ ��� ���� --> ���� ������ �ڵ鿡 �����ؼ� ����ϴ� GDI+ ��� ���� --> Memory DC�� �����ؼ� ����ϴ� GDI+ ��� ����
	Gdiplus::DllExports::GdipCreatePen1(0xFFFF0000, 1, Gdiplus::UnitWorld, &mp_pen);				// ������ , ���� 1
	
	// 'AntiAlias' ���
	Gdiplus::DllExports::GdipSetSmoothingMode(mp_graphics, Gdiplus::SmoothingModeAntiAlias);

	// ����
	Gdiplus::DllExports::GdipGraphicsClear(mp_graphics, 0x440000FF);				// AARRGGBB

	Gdiplus::DllExports::GdipDrawRectangleI(mp_graphics, mp_pen, 30, 30, 300, 180);				// 30, 30, 300, 180
	Gdiplus::DllExports::GdipSetPenWidth(mp_pen, 10);				// ���⸦ 10���� ����
	Gdiplus::DllExports::GdipSetPenColor(mp_pen, 0x50600000);				// Red�� 255���� 96���� ����, ������ 255���� 80���� ����

	GdipSetPenMode(mp_pen, Gdiplus::PenAlignmentInset);				// ���� �������� ���� �������θ� �׷����� ���� ����

	GdipDrawRectangleI(mp_graphics, mp_pen, 30, 30, 300, 180);				// 30, 30, 300, 180

	Gdiplus::DllExports::GdipDeletePen(mp_pen);
	Gdiplus::DllExports::GdipCreatePen1(0xFFFF0000, 7, Gdiplus::UnitWorld, &mp_pen);

	for (int i = 0; i < 5; i++) {
		//Gdiplus::DllExports::GdipSetPenEndCap(mp_pen, (LineCap)(0x10 + i));					// ���� �� ��ġ ����� ����
		//Gdiplus::DllExports::GdipSetPenStartCap(mp_pen, (LineCap)(0x10 + i));				// ���� ������ġ ����� ����

		Gdiplus::DllExports::GdipSetPenDashStyle(mp_pen, (Gdiplus::DashStyle)i);
		Gdiplus::DllExports::GdipDrawLineI(mp_graphics, mp_pen, 20, 20 + i * 16, 300, 20 + i * 16);				// ���� �׸���
	}

	Gdiplus::DllExports::GdipDeletePen(mp_pen);
	Gdiplus::DllExports::GdipCreatePen1(0xFFFF0000, 7, Gdiplus::UnitWorld, &mp_pen);
	Gdiplus::Point star_pos[11] = { {121,20}, {97,97}, {20,97}, {82,145}, {59,221}, {121,173}, {183,221}, {158,145}, {221,97}, {144,97}, {121,20} };

	// 11���� ������ 10���� ���� �׸���
	//for (int i = 0; i < 10; i++) {
	//	GdipDrawLineI(mp_graphics, mp_pen, star_pos[i].X, star_pos[i].Y, star_pos[i + 1].X, star_pos[i + 1].Y);
	//}

	GdipSetPenLineJoin(mp_pen, Gdiplus::LineJoinRound);				// ���� ���� ������ ������ LineJoinRound�� ����
	GdipSetPenStartCap(mp_pen, Gdiplus::LineCapRound);				// �� ������ �ձ۰�
	GdipSetPenEndCap(mp_pen, Gdiplus::LineCapRound);				// �� ���� �ձ۰�

	GdipDrawLinesI(mp_graphics, mp_pen, star_pos, 11);

	GdipCreateSolidFill(0xFF00FF00, &mp_brush);				// �ʷϻ� �귯�� (���� 255)
	GdipFillRectangle(mp_graphics, mp_brush, 430, 30, 150, 150);				// �簢��

	GdipSetSolidFillColor(mp_brush, 0x700000FF);				// �귯�� ���� (���� 0x70 ���)
	GdipFillRectangle(mp_graphics, mp_brush, 460, 60, 150, 150);					// �簢��

	GdipSetSolidFillColor(mp_brush, 0x30FF00FF);				// �귯�� ���� (���� 0x30 ��ũ)
	GdipFillEllipse(mp_graphics, mp_brush, 520, 80, 170, 170);

	// ��ġ �귯��
	Gdiplus::GpHatch* p_brush = NULL;
	GdipCreateHatchBrush(Gdiplus::HatchStyleHorizontal, 0xFF00FF00, 0xFF009000, &p_brush);
	GdipFillRectangleI(mp_graphics, p_brush, 30, 230, 150, 150);
	GdipDeleteBrush(p_brush);

	//// 52���� Hatch Style ��� ���
	//for (int i = 0; i < 52; ++i) {
	//	GdipCreateHatchBrush((GpHatchStyle)i, 0xFF00FF00, 0xFF009000, &p_brush);
	//	GdipFillRectangleI(mp_graphics, p_brush, 20 + (i % 8) * 61, 370 + (i / 8) * 41, 60, 40);
	//	GdipDeleteBrush(p_brush);
	//}
	
	// ���ڿ� ���
	Gdiplus::GpFontFamily* p_font_family = NULL;
	Gdiplus::GpFont* p_font = NULL;
	Gdiplus::DllExports::GdipCreateFontFamilyFromName(L"���� ���", NULL, &p_font_family);
	Gdiplus::GpSolidFill* p_font_brush = NULL;
	Gdiplus::DllExports::GdipCreateSolidFill(0xFF00FF00, &p_font_brush);

	Gdiplus::RectF text_rect(30.0f, 30.0f, 0.0f, 0.0f);
	FontStyle style_table[6] = {FontStyleRegular, FontStyleBold, FontStyleItalic, FontStyleBoldItalic, FontStyleUnderline, FontStyleStrikeout};

	for (int i = 0; i < 6; ++i) {
		Gdiplus::DllExports::GdipCreateFont(p_font_family, 20, style_table[i], Gdiplus::UnitPixel, &p_font);
		GdipDrawString(mp_graphics, L"�ȳ��ϼ��� �ݰ����ϴ� GDI+ �Դϴ�", -1, p_font, &text_rect, NULL, p_font_brush);
		text_rect.Y += 35.0f;
		GdipDeleteFont(p_font);
	}

	text_rect = Gdiplus::RectF(730.0f, 30.0f, 260.0f, 200.0f);
	GdipDrawRectangle(mp_graphics, mp_pen, text_rect.X, text_rect.Y, text_rect.Width, text_rect.Height);

	// ��� ���� �ɼ�
	GpStringFormat* p_str_format = NULL;
	GdipCreateStringFormat(0, LANG_KOREAN, &p_str_format);
	GdipSetStringFormatAlign(p_str_format, StringAlignmentCenter);
	GdipSetStringFormatLineAlign(p_str_format, StringAlignmentCenter);

	Gdiplus::DllExports::GdipCreateFont(p_font_family, 20, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel, &p_font);
	GdipDrawString(mp_graphics, L"�簢�� ������ �����ϰ� \n�� �ȿ����� ���� �����ϴ�. \n���� ������ �ʰ��ϸ� \n�ڵ����� �ٹٲ��� ���ݴϴ�.", -1, p_font, &text_rect, p_str_format, p_font_brush);

	GdipDeleteStringFormat(p_str_format);
	GdipDeleteFont(p_font);
	GdipDeleteBrush(p_font_brush);
	GdipDeleteFontFamily(p_font_family);

	GdipLoadImageFromFile(L"../photo.jpg", &mp_image);				// GDI+ ���� �̹��� ��ü�� ����ؾ� ���İ��� ���� ����ȴ�
	Gdiplus::DllExports::GdipDrawImageRectI(mp_graphics, mp_image, 0, 400, 200, 200);				// �簢�� ũ�⿡ ���� ���
	//Gdiplus::DllExports::GdipDrawImageI(mp_graphics, mp_image, 0, 0);				// 0,0 ��ġ�� �̹��� ���
	GdipDisposeImage(mp_image);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGdiplusGuideDlg::SetMemDC()
{
	//CClientDC dc(this);																			// Memory DC�� �����ϱ� ���� �� Ŭ������ DC�� ��´�
	//mh_mem_dc = CreateCompatibleDC(dc);											// Memory DC ����!
	//mh_mem_bmp = CreateCompatibleBitmap(dc, 200, 200);					// Memory DC�� ����� ��Ʈ���� 200, 200 ũ��� ����!
	//::SelectObject(mh_mem_dc, mh_mem_bmp);									// MemDC�� ��Ʈ���� ����!
	CRect rect;
	GetWindowRect(&rect);
	int width = rect.Width();
	int height = rect.Height();

	Gdiplus::DllExports::GdipCreateBitmapFromScan0(width, height, 0, PixelFormat64bppARGB, NULL, &mp_bitmap);
	Gdiplus::DllExports::GdipGetImageGraphicsContext(mp_bitmap, &mp_graphics);

}

void CGdiplusGuideDlg::DeleteMemDC()
{
	//::DeleteDC(mh_mem_dc);					// Memory DC ����
	//::DeleteObject(mh_mem_bmp);			// Memory DC�� ��Ʈ�� ����
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
		// Memory DC �� 0,0 ~ 200,200 ��ŭ ī���Ѵ�
		//::BitBlt(dc, 0, 0, 200, 200, mh_mem_dc, 0, 0, SRCCOPY);
		
		Gdiplus::GpGraphics* p_graphics = NULL;
		Gdiplus::DllExports::GdipCreateFromHDC(dc, &p_graphics);					// ����
		Gdiplus::DllExports::GdipDrawImageI(p_graphics, mp_bitmap, 0, 0);				// ��Ʈ���� ȭ���� 0,0 ��ġ�� ���
		Gdiplus::DllExports::GdipDeleteGraphics(p_graphics);				// ��¿� GDI+ ����
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

	Gdiplus::DllExports::GdipDeleteGraphics(mp_graphics);				// GDI+ ��� ����
	Gdiplus::DllExports::GdipFree(mp_bitmap);
	Gdiplus::GdiplusShutdown(m_token);				// GDI+ ���� DLL�� ������ �����Ѵ�

	//DeleteMemDC();
}
