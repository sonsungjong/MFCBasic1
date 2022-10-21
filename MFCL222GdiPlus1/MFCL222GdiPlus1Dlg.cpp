
// MFCL222GdiPlus1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL222GdiPlus1.h"
#include "MFCL222GdiPlus1Dlg.h"
#include "afxdialogex.h"

#include <gdiplus.h>
using namespace Gdiplus;
// #pragma comment(lib, "gdiplus")					// win32는 적어야하는데 MFC는 안적어도됨

void DrawLine(CDC* ap_dc)
{
	// DC핸들값을 사용하여 GDI+ 사용하기 위한 그래픽 객체 생성
	Graphics* p_graphic = new Graphics(ap_dc->m_hDC);
	Pen* p_pen = new Pen(Color(255, 255, 0, 0), 2);

	// AntiAlias 필수
	p_graphic->SetSmoothingMode(SmoothingModeAntiAlias);				// SmoothingModelInvalid
	p_graphic->DrawEllipse(p_pen, 30, 130, 70, 50);
	p_graphic->DrawEllipse(p_pen, 110, 130, 70, 50);
	p_graphic->DrawEllipse(p_pen, 70, 150, 70, 50);

	// 사용한 그래픽 객체 제거
	delete p_graphic;
	delete p_pen;
}

#ifdef _DEBUG
//#define new DEBUG_NEW
#endif

// CMFCL222GdiPlus1Dlg dialog

CMFCL222GdiPlus1Dlg::CMFCL222GdiPlus1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL222GDIPLUS1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL222GdiPlus1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL222GdiPlus1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL222GdiPlus1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL222GdiPlus1Dlg::OnBnClickedCancel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCL222GdiPlus1Dlg message handlers

BOOL CMFCL222GdiPlus1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// GDI+ 사용전에 해줘야하는 작업들
	GdiplusStartupInput gpsi;
	if (GdiplusStartup(&m_token, &gpsi, NULL) != Ok) {
		AfxMessageBox(_T("GDI+ 실패"));
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL222GdiPlus1Dlg::OnPaint()
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

		// GDI
		CPen blue_pen(PS_SOLID, 2, RGB(0, 0, 255));
		dc.SelectStockObject(NULL_BRUSH);
		dc.SelectObject(&blue_pen);
		dc.Ellipse(30, 30, 100, 80);
		dc.Ellipse(110, 30, 180, 80);
		dc.Ellipse(70, 50, 140, 100);

		// GDI+
		DrawLine(&dc);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCL222GdiPlus1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL222GdiPlus1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL222GdiPlus1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCL222GdiPlus1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	GdiplusShutdown(m_token);				// GDI+ 해제
}
