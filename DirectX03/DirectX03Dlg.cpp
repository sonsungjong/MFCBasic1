
// DirectX03Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "DirectX03.h"
#include "DirectX03Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// D2D 라이브러리
#pragma comment(lib, "D2D1.lib")

// CDirectX03Dlg dialog

CDirectX03Dlg::CDirectX03Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIRECTX03_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDirectX03Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDirectX03Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CDirectX03Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDirectX03Dlg message handlers

BOOL CDirectX03Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// COM 사용을 위한 초기화
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	// D2D 사용을 위한 팩토리 생성
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mp_factory);

	RECT r;
	// 클라이언트 영역을 얻는다.
	::GetClientRect(m_hWnd, &r);
	// 영역의 중심 좌표를 구한다.
	m_x = (r.right - r.left) / 2;
	m_y = (r.bottom - r.top) / 2;

	// 윈도우 렌더 타겟을 생성에서 주소로 가져올 포인터 선언
	ID2D1HwndRenderTarget* p_hwnd_target;
	// 지정한 윈도우의 클라이언트 영역에 그림을 그리기 위한 Render Target 생성
	mp_factory->CreateHwndRenderTarget(RenderTargetProperties(), HwndRenderTargetProperties(m_hWnd, SizeU(r.right - r.left, r.bottom - r.top)), &p_hwnd_target);
	// 부모 인터페이스로 주소를 보관한다.
	mp_target = p_hwnd_target;

	D2D1_COLOR_F color = { 1.0f, 1.0f, 1.0f, 1.0f };					// RGBA
	// color의 색상을 브러시에 생성
	mp_target->CreateSolidColorBrush(color, &mp_user_brush);

	// 수평, 수직 선을 점선으로 그리기 위해 획 속성을 생성한다.
	mp_factory->CreateStrokeStyle(D2D1::StrokeStyleProperties(
		D2D1_CAP_STYLE_FLAT, D2D1_CAP_STYLE_FLAT, D2D1_CAP_STYLE_ROUND,
		D2D1_LINE_JOIN_MITER, 10.0f,
		D2D1_DASH_STYLE_DOT, 0.0f), nullptr, 0, &mp_stroke_style);

	// 애니메이션을 위한 1번 타이머
	SetTimer(1, 30, nullptr);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDirectX03Dlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDirectX03Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDirectX03Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);

	// D2D 해제
	__IRelease(&mp_stroke_style);
	__IRelease(&mp_user_brush);
	__IRelease(&mp_target);
	__IRelease(&mp_factory);
	CoUninitialize();
}


void CDirectX03Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		// D2D 그림 그리기 시작
		mp_target->BeginDraw();
		// 그려질 영역을 검은색으로 채우기
		mp_target->Clear(ColorF(0.0f, 0.0f, 0.0f));

		D2D1_POINT_2F start = { (FLOAT)m_x, 0.0f };
		D2D1_POINT_2F end = { (FLOAT)m_x, (FLOAT)(m_y << 1) };
		D2D1_COLOR_F color = { 1.0f, 1.00f, 1.00f, 0.5f };			// RGBA

		// 수평, 수직 축에 대한 색상 지정
		mp_user_brush->SetColor(color);
		// 수직선 그리기
		mp_target->DrawLine(start, end, mp_user_brush, 3.0f, mp_stroke_style);
		start.x = 0.0f;
		start.y = (FLOAT)m_y;
		end.x = (FLOAT)(m_x << 1);
		end.y = (FLOAT)m_y;
		// 수평선 그리기
		mp_target->DrawLine(start, end, mp_user_brush, 3.0f, mp_stroke_style);

		// 각을 4도 증가시키다가 360도가 되면 0으로 만듦
		m_degree = (m_degree + 4) % 360;
		// 각을 라디안으로 변경
		double cur_process_radian = m_degree * COVT_RADIAN;

		color.r = 0;
		color.a = 1.0f;
		// 조정된 색상을 브러시 객체에 반영
		mp_user_brush->SetColor(color);

		// X축 시작점을 구한다.
		int fix = m_x - 360;
		// 첫 시작점을 구성한다.
		start.x = (FLOAT)fix;
		start.y = (FLOAT)m_y;

		// 윈도우 왼쪽 끝에서 오른쪽 끝까지 그래프를 그리기
		for (int x = 0; x < 2880; x += 4) {
			end.x = (FLOAT)((x >> 2) + fix);
			end.y = (FLOAT)(m_y - sin(x * COVT_RADIAN - cur_process_radian) * 100);
			mp_target->DrawLine(start, end, mp_user_brush, 5.0f);
			start = end;
		}
		// 그리기 종료 후 화면에 출력
		mp_target->EndDraw();

	} else { CDialogEx::OnTimer(nIDEvent); }

}


void CDirectX03Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}
