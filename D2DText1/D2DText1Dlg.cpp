
// D2DText1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "D2DText1.h"
#include "D2DText1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "DWRITE.lib")

// CD2DText1Dlg dialog



CD2DText1Dlg::CD2DText1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_D2DTEXT1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CD2DText1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CD2DText1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CD2DText1Dlg::OnBnClickedOk)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CD2DText1Dlg message handlers

BOOL CD2DText1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// 1. COM 초기화
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	// 2. D2D 팩토리
	D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &mp_factory);

	// 문자열 출력 팩토리
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(mp_write_factory),
		reinterpret_cast<IUnknown**>(&mp_write_factory));

	if(S_OK == mp_write_factory->CreateTextFormat(_T("배달의민족"), nullptr,
		DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 
		32, _T("ko-kr"), &mp_text_format)) {
		mp_text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		mp_text_format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	// 클라이언트 영역 얻기
	::RECT r;
	::GetClientRect(m_hWnd, &r);
	// 렌더타겟을 생성해서 주소를 가져올 포인터 선언
	ID2D1HwndRenderTarget* p_hwnd_target;
	// 그림을 그리기 위한 RenderTarget을 생성
	mp_factory->CreateHwndRenderTarget(RenderTargetProperties(),
		HwndRenderTargetProperties(m_hWnd, SizeU(r.right - r.left, r.bottom - r.top)), &p_hwnd_target);

	// 부모 인터페이스를 주소로 보관한다.
	mp_target = p_hwnd_target;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CD2DText1Dlg::UserDraw()
{
	mp_target->BeginDraw();

	// 선에 사용할 브러시 자원 주소를 저장할 변수 선언
	ID2D1SolidColorBrush* p_user_brush = nullptr;
	D2D1_COLOR_F color = { 0.3f, 0.8f, 1.0f, 1.0f };						// RGBA
	// color에 지정된 색상으로 브러시를 생성
	mp_target->CreateSolidColorBrush(color, &p_user_brush);

	if (mp_text_format && p_user_brush) {
		D2D1_RECT_F r = { 30.0f, 30.0f, 450.0f, 150.0f };
		mp_target->DrawRectangle(r, p_user_brush);
		mp_target->DrawText(_T("9글자를 적기!!"), 9, mp_text_format, r, p_user_brush);
	}

	__IRelease(&p_user_brush);
	mp_target->EndDraw();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CD2DText1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

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
		::ValidateRect(m_hWnd, nullptr);
		UserDraw();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CD2DText1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CD2DText1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CD2DText1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	__IRelease(&mp_target);
	__IRelease(&mp_text_format);
	__IRelease(&mp_write_factory);
	__IRelease(&mp_factory);
	CoUninitialize();
}
