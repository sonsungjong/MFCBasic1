
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

// D2D ���̺귯�� �߰�
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
	// COM �ʱ�ȭ
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	// D2D factory ����
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mp_factory);

	::RECT r;
	// Ŭ���̾�Ʈ ������ ����
	::GetClientRect(m_hWnd, &r);
	m_x = (r.right - r.left) / 2;
	m_y = (r.bottom - r.top) / 2;

	// ������ ��� ���� Ÿ���� �������� �ּҸ� ������ ������ ����
	ID2D1HwndRenderTarget* p_hwnd_target;
	// ������ �������� Ŭ���̾�Ʈ ������ �׸��� �׸��� ���� Render Target�� �����Ѵ�.
	mp_factory->CreateHwndRenderTarget(RenderTargetProperties(),
		HwndRenderTargetProperties(m_hWnd, SizeU(r.right - r.left, r.bottom - r.top)), &p_hwnd_target);
	// �θ� �������̽��� �ּҸ� �����Ѵ�.
	mp_target = p_hwnd_target;

	D2D1_COLOR_F color = { 1.0f, 1.0f, 1.0f, 1.0f };						// RGBA
	// color ������ �귯�ÿ�
	mp_target->CreateSolidColorBrush(color, &mp_user_brush);

	// ����, ���� ���� �������� �׸��� ���� ȹ �Ӽ��� ����
	mp_factory->CreateStrokeStyle(D2D1::StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,
		D2D1_CAP_STYLE_FLAT, D2D1_CAP_STYLE_ROUND,
		D2D1_LINE_JOIN_MITER, 10.0f, D2D1_DASH_STYLE_DOT, 0.0f),
		nullptr, 0, &mp_stroke_style);

	// ���� ���� ���ҽ��� �����Ѵ�
	HRESULT hr = mp_factory->CreatePathGeometry(&mp_geometry);
	if (SUCCEEDED(hr))
	{
		ID2D1GeometrySink* p_sink = nullptr;
		// ������ �߰��ϱ� ���� �Է��� ���� sink �ڿ��� ����.
		hr = mp_geometry->Open(&p_sink);
		if (SUCCEEDED(hr)) {
			// ���� �������� �׷��� ���ϴ� ���� �׸��� , ������ = (50, 50)
			p_sink->BeginFigure(Point2F(float(m_x - 75), float(m_y - 25)), D2D1_FIGURE_BEGIN_FILLED);
			p_sink->AddLine(Point2F(float(m_x - 25), float(m_y + 25)));
			p_sink->AddLine(Point2F(float(m_x + 25), float(m_y - 25)));
			p_sink->AddLine(Point2F(float(m_x + 75), float(m_y + 25)));
			p_sink->EndFigure(D2D1_FIGURE_END_CLOSED);
			p_sink->Close();

			// ���� �߰��� ���� ����� sink ���ҽ� �ݳ�
			__IRelease(&p_sink);
		}
	}

	// �ִϸ��̼� Ÿ�̸� 1��
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
		// WM_PAINT ��ȿȭ
		//CDialogEx::OnPaint();
		::ValidateRect(m_hWnd, nullptr);
		OnTimer(1);					// �׸��� ��ƾ�� Ÿ�̸ӿ� �����ϰ� ���
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

	// D2D ����
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
		// D2D �׸��� ����
		mp_target->BeginDraw();
		// �׷��� ������ ������� ó��
		mp_target->Clear(ColorF(0.0f, 0.0f, 0.0f));

		D2D1_COLOR_F color = { 0.0f, 0.05f, 0.05f, 1.0f };				// RGBA
		D2D1_COLOR_F color2  = {0.8f, 0.9f, 1.0f, 1.0f };				// RGBA
		D2D1_POINT_2F rot_center = { float(m_x), float(m_y) };				// ȸ�� �߽� ��ǥ

		for (int i = 0; i < 20; i++) {
			// ���ϵ����� 8���� ȸ��
			mp_target->SetTransform(Matrix3x2F::Rotation(FLOAT(m_degree + i * 8), rot_center));

			// ���� ���θ� ����� ����� �ϴû����� ä��� ���� ���� ����
			mp_user_brush->SetColor(color2);
			// ���� ���θ� �׸���.
			mp_target->FillGeometry(mp_geometry, mp_user_brush);

			// ���� �׵θ� ������ �����Ѵ�.
			mp_user_brush->SetColor(color);
			// ���� �׵θ��� �׸���.
			mp_target->DrawGeometry(mp_geometry, mp_user_brush, 5);
			// ������ ���ݾ� ��� �����.
			color.g += 0.05f;
			color.b += 0.05f;
		}
		// ���� ��ȯ ����� �ʱⰪ�� ����
		mp_target->SetTransform(Matrix3x2F::Identity());
		// ���� 4�� ������Ű�� 360���� �Ǹ� 0����
		m_degree = (m_degree + 4) % 360;
		// �׸��� �۾� ���� �� ȭ�����
		mp_target->EndDraw();
	}else{ CDialogEx::OnTimer(nIDEvent); }
}
