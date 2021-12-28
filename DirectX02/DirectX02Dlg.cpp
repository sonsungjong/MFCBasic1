
// DirectX02Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "DirectX02.h"
#include "DirectX02Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// D2D를 사용하기 위한 라이브러리
#pragma comment(lib, "D2D1.lib")

CDirectX02Dlg::CDirectX02Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIRECTX02_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDirectX02Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDirectX02Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDirectX02Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDirectX02Dlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDirectX02Dlg message handlers

BOOL CDirectX02Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// COM 초기화
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mp_factory);

	RECT r;
	::GetClientRect(m_hWnd, &r);
	
	// 그릴 원의 좌표
	m_x = (r.right - r.left) / 2;
	m_y = (r.bottom - r.top) / 2;
	if (m_x < m_y) m_rot_radius = m_x - 40;
	else m_rot_radius = m_y - 40;

	double radian;
	for (int i = 0; i < 720; i++) {
		radian = (PI * i / 180) / 2;
		m_circle_position[i].x = (float)(sin(radian) * m_rot_radius + m_x);
		m_circle_position[i].y = (float)(cos(radian) * m_rot_radius + m_y);
	}

	// 윈도우 렌더 타겟
	ID2D1HwndRenderTarget* p_hwnd_target;
	mp_factory->CreateHwndRenderTarget(
		RenderTargetProperties(),
		HwndRenderTargetProperties(m_hWnd, SizeU(r.right - r.left, r.bottom - r.top)), 
		&p_hwnd_target
	);
	mp_target = p_hwnd_target;

	D2D1_COLOR_F color = { 0.0f, 0.1f, 0.0f, 1.0f };		// 어두운 녹색
	ID2D1SolidColorBrush* p_green_brush = nullptr;
	mp_target->CreateSolidColorBrush(color, &mp_green_brush);

	SetTimer(1, 10, nullptr);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDirectX02Dlg::OnPaint()
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
		// WM_PAINT를 무효화
		::ValidateRect(m_hWnd, nullptr);
		OnTimer(1);

		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDirectX02Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDirectX02Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CDirectX02Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CDirectX02Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);

	// D2D 해제
	IRelease(&mp_green_brush);
	IRelease(&mp_target);
	IRelease(&mp_factory);
	CoUninitialize();
}


void CDirectX02Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == 1){
		// D2D 그림 그리기
		mp_target->BeginDraw();
		mp_target->Clear(ColorF(0.0f, 0.0f, 0.0f));			// 배경색

		// 원
		D2D1_ELLIPSE circle = { {m_circle_position[m_degree].x, m_circle_position[m_degree].y}, 5, 5 };
		D2D1_COLOR_F color = { 0.0f, 0.05f, 0.05f, 1.0f };			// RGBA

		// 20번 반복 시 밝은 색
		float step = 0.95f / 20;
		int degree = m_degree;
		if (mp_green_brush != nullptr) {
			mp_green_brush->SetColor(color);
			for (int i = 0; i < 20; i++) {
				// 타원 그리기
				mp_target->FillEllipse(circle, mp_green_brush);
				// 점이동
				circle.point.x = m_circle_position[degree].x;
				circle.point.y = m_circle_position[degree].y;
				degree = (degree + 4) % 720;

				// 반지름 크기 변경
				circle.radiusX = i / 2.0f + 5;
				circle.radiusY = i / 2.0f + 5;
				// 색 변경
				color.g += step;
				color.b += step;
				// 조정된 색상을 브러시 객체에 반영
				mp_green_brush->SetColor(color);
			}
		}
		// 그리기 종료 후 화면 출력
		mp_target->EndDraw();

		// 각도 변경
		m_degree = (m_degree + 1) % 720;					// 각도를 1도씩 증가
	}else { CDialogEx::OnTimer(nIDEvent); }
}
