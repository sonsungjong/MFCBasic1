
// D2DBarGraph1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "D2DBarGraph1.h"
#include "D2DBarGraph1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CD2DBarGraph1Dlg dialog
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")



CD2DBarGraph1Dlg::CD2DBarGraph1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_D2DBARGRAPH1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}



void CD2DBarGraph1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CD2DBarGraph1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CD2DBarGraph1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CD2DBarGraph1Dlg::OnBnClickedCancel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CD2DBarGraph1Dlg message handlers

BOOL CD2DBarGraph1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// Direct2D 초기화 코드
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	if (SUCCEEDED(hr))
	{
		CRect rc;
		GetClientRect(&rc);
		D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

		hr = m_pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(GetSafeHwnd(), size), &m_pRenderTarget);
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBrush);
	}

	return SUCCEEDED(hr) ? TRUE : FALSE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CD2DBarGraph1Dlg::OnPaint()
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
		//D2DRender();
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CD2DBarGraph1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CD2DBarGraph1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CD2DBarGraph1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CD2DBarGraph1Dlg::D2DRender()
{
	if (m_pRenderTarget == NULL)
	{ return; }

	// D2D 그리기 시작
	m_pRenderTarget->BeginDraw();

	// 전체 배경색 덮기
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::AliceBlue));

	// 막대 그래프 코드 추가
	D2DBarGraph();

	// 그리기를 마무리하고 화면에 출력
	m_pRenderTarget->EndDraw();
}

void CD2DBarGraph1Dlg::D2DCleanup()
{
	if (m_pBrush) { m_pBrush->Release(); }
	if (m_pRenderTarget) { m_pRenderTarget->Release(); }
	if (m_pD2DFactory) { m_pD2DFactory->Release(); }
}

void CD2DBarGraph1Dlg::D2DBarGraph()
{
	// 막대 그래프 그리는 코드 예시
	float barWidth = 50.0f;
	float barSpacing = 20.0f;
	float barHeight[] = { 100.0f, 200.0f, 300.0f, 150.0f, 250.0f };
	D2D1_COLOR_F colors[] = {
		{0.0f, 0.125f, 0.3f, 1.0f},
		{0.5f, 0.125f, 0.3f, 1.0f},
		{0.1f, 0.125f, 0.3f, 0.5f},
		{0.0f, 0.5f, 0.3f, 1.0f},
		{0.0f, 0.125f, 0.125f, 1.0f}
	};
	size_t barCount = sizeof(barHeight) / sizeof(barHeight[0]);

	for (size_t i = 0; i < barCount; ++i)
	{
		D2D1_RECT_F barRect = D2D1::RectF(barSpacing + i * (barWidth + barSpacing), m_pRenderTarget->GetSize().height - barHeight[i], 
			barSpacing + (i+1) * barWidth + i * barSpacing, m_pRenderTarget->GetSize().height);
		m_pBrush->SetColor(colors[i]);
		m_pRenderTarget->FillRectangle(barRect, m_pBrush);
	}
}

void CD2DBarGraph1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	D2DCleanup();
}

