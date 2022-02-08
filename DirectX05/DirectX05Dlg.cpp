
// DirectX05Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "DirectX05.h"
#include "DirectX05Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// D2D 라이브러리 추가
#pragma comment(lib, "D2D1.lib")

// CDirectX05Dlg dialog
CDirectX05Dlg::CDirectX05Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIRECTX05_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDirectX05Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDirectX05Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDirectX05Dlg::OnBnClickedOk)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDirectX05Dlg message handlers

BOOL CDirectX05Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// COM 초기화
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	// D2D factory 생성
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mp_factory);

	::RECT r;
	// 클라이언트 영역을 저장
	::GetClientRect(m_hWnd, &r);
	m_x = (r.right - r.left) / 2;
	m_y = (r.bottom - r.top) / 2;

	// 윈도우 기반 렌더 타겟을 생성에서 주소를 가져올 포인터 선언
	ID2D1HwndRenderTarget* p_hwnd_target;
	// 지정한 윈도우의 클라이언트 영역에 그림을 그리기 위한 Render Target을 생성한다.
	mp_factory->CreateHwndRenderTarget(RenderTargetProperties(),
		HwndRenderTargetProperties(m_hWnd, SizeU(r.right - r.left, r.bottom - r.top)), &p_hwnd_target);
	// 부모 인터페이스로 주소를 보관한다.
	mp_target = p_hwnd_target;

	D2D1_COLOR_F color = { 1.0f, 1.0f, 1.0f, 1.0f };						// RGBA
	// color 색상을 브러시에
	mp_target->CreateSolidColorBrush(color, &mp_user_brush);

	// 수평, 수직 선을 점선으로 그리기 위해 획 속성을 생성
	mp_factory->CreateStrokeStyle(D2D1::StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,
		D2D1_CAP_STYLE_FLAT, D2D1_CAP_STYLE_ROUND,
		D2D1_LINE_JOIN_MITER, 10.0f, D2D1_DASH_STYLE_DOT, 0.0f),
		nullptr, 0, &mp_stroke_style);

	// 기하 도형 리소스를 생성한다
	HRESULT hr = mp_factory->CreatePathGeometry(&mp_geometry);
	if (SUCCEEDED(hr))
	{
		ID2D1GeometrySink* p_sink = nullptr;
		// 도형을 추가하기 위해 입력을 받을 sink 자원을 연다.
		hr = mp_geometry->Open(&p_sink);
		if (SUCCEEDED(hr)) {
			// 선을 연속으로 그려서 원하는 도형 그리기 , 시작점 = (50, 50)
			p_sink->BeginFigure(Point2F(float(m_x - 75), float(m_y - 25)), D2D1_FIGURE_BEGIN_FILLED);
			p_sink->AddLine(Point2F(float(m_x - 25), float(m_y + 25)));
			p_sink->AddLine(Point2F(float(m_x + 25), float(m_y - 25)));
			p_sink->AddLine(Point2F(float(m_x + 75), float(m_y + 25)));
			p_sink->EndFigure(D2D1_FIGURE_END_CLOSED);
			p_sink->Close();

			// 도형 추가를 위해 사용한 sink 리소스 반납
			__IRelease(&p_sink);
		}
	}

	// 애니메이션 타이머 1번
	SetTimer(1, 30, nullptr);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDirectX05Dlg::OnPaint()
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
		// WM_PAINT 무효화
		//CDialogEx::OnPaint();
		::ValidateRect(m_hWnd, nullptr);
		OnTimer(1);					// 그리기 루틴을 타이머와 동일하게 사용
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDirectX05Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDirectX05Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CDirectX05Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);

	// D2D 해제
	__IRelease(&mp_geometry);
	__IRelease(&mp_geometry);
	__IRelease(&mp_geometry);
	__IRelease(&mp_geometry);
	__IRelease(&mp_geometry);
	CoUninitialize();
}


void CDirectX05Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		// D2D 그리기 시작
		mp_target->BeginDraw();
		// 그려질 영역을 검정배경 처리
		mp_target->Clear(ColorF(0.0f, 0.0f, 0.0f));

		D2D1_COLOR_F color = { 0.0f, 0.05f, 0.05f, 1.0f };				// RGBA
		D2D1_COLOR_F color2  = {0.8f, 0.9f, 1.0f, 1.0f };				// RGBA
		D2D1_POINT_2F rot_center = { float(m_x), float(m_y) };				// 회전 중심 좌표

		for (int i = 0; i < 20; i++) {
			// 기하도형을 8도씩 회전
			mp_target->SetTransform(Matrix3x2F::Rotation(FLOAT(m_degree + i * 8), rot_center));

			// 도형 내부를 흰색에 가까운 하늘색으로 채우기 위해 색을 설정
			mp_user_brush->SetColor(color2);
			// 도형 내부를 그린다.
			mp_target->FillGeometry(mp_geometry, mp_user_brush);

			// 도형 테두리 색상을 설정한다.
			mp_user_brush->SetColor(color);
			// 도형 테두리를 그린다.
			mp_target->DrawGeometry(mp_geometry, mp_user_brush, 5);
			// 색상을 조금씩 밝게 만든다.
			color.g += 0.05f;
			color.b += 0.05f;
		}
		// 도형 변환 기능을 초기값을 복구
		mp_target->SetTransform(Matrix3x2F::Identity());
		// 각을 4도 증가시키고 360도가 되면 0으로
		m_degree = (m_degree + 4) % 360;
		// 그리기 작업 종료 후 화면출력
		mp_target->EndDraw();
	}else{ CDialogEx::OnTimer(nIDEvent); }
}
