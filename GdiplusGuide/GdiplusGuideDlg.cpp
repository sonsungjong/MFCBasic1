
// GdiplusGuideDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "GdiplusGuide.h"

#include <gdiplus.h>
//using namespace Gdiplus;
//using namespace DllExports;

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

	Gdiplus::DllExports::GdipCreateFromHDC(mh_mem_dc, &mp_graphics);				// **HDC�� �����ؼ� ����ϴ� GDI+ ��� ���� --> ���� ������ �ڵ鿡 �����ؼ� ����ϴ� GDI+ ��� ���� --> Memory DC�� �����ؼ� ����ϴ� GDI+ ��� ����
	Gdiplus::DllExports::GdipCreatePen1(0xFFFF0000, 3, Gdiplus::UnitWorld, &mp_pen);
	
	// 'AntiAlias' ���
	Gdiplus::DllExports::GdipSetSmoothingMode(mp_graphics, Gdiplus::SmoothingModeAntiAlias);

	// ����
	Gdiplus::DllExports::GdipGraphicsClear(mp_graphics, 0xFFFFFFFF);
	// 30, 30, 300, 180 ������ �׸�
	Gdiplus::DllExports::GdipDrawEllipseI(mp_graphics, mp_pen, 30, 30, 300, 180);
	// 10,20 ~ 300,160 ���� ���� �׸�
	Gdiplus::DllExports::GdipDrawLine(mp_graphics, mp_pen, 20, 40, 340, 190);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGdiplusGuideDlg::SetMemDC()
{
	CClientDC dc(this);																			// Memory DC�� �����ϱ� ���� �� Ŭ������ DC�� ��´�
	mh_mem_dc = CreateCompatibleDC(dc);											// Memory DC ����!
	mh_mem_bmp = CreateCompatibleBitmap(dc, 200, 200);					// Memory DC�� ����� ��Ʈ���� 200, 200 ũ��� ����!
	::SelectObject(mh_mem_dc, mh_mem_bmp);									// MemDC�� ��Ʈ���� ����!
}

void CGdiplusGuideDlg::DeleteMemDC()
{
	::DeleteDC(mh_mem_dc);					// Memory DC ����
	::DeleteObject(mh_mem_bmp);			// Memory DC�� ��Ʈ�� ����
}

void CGdiplusGuideDlg::PrintMemDC(HDC dc)
{
	::BitBlt(dc, 0, 0, 200, 200, mh_mem_dc, 0, 0, SRCCOPY);				// Memory DC�� 0,0 ~ 200,200 �� ī��
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
		::BitBlt(dc, 0, 0, 200, 200, mh_mem_dc, 0, 0, SRCCOPY);
		//CDialogEx::OnPaint();
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
	Gdiplus::DllExports::GdipDeleteGraphics(mp_graphics);				// GDI+ ��� ����

	Gdiplus::GdiplusShutdown(m_token);				// GDI+ ���� DLL�� ������ �����Ѵ�

	DeleteMemDC();
}
