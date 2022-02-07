
// DirectX04Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "DirectX04.h"
#include "DirectX04Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// D2D ���̺귯��
#pragma comment(lib, "D2D1.lib")


CDirectX04Dlg::CDirectX04Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIRECTX04_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDirectX04Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDirectX04Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDirectX04Dlg::OnBnClickedOk)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDirectX04Dlg message handlers

BOOL CDirectX04Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// COM �ʱ�ȭ
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	// D2D ���丮
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mp_factory);

	::RECT r;
	// Ŭ���̾�Ʈ ������ ��´�
	::GetClientRect(m_hWnd, &r);
	// ������ �߽���ǥ�� ��´�.
	m_x = (r.right - r.left) / 2;
	m_y = (r.bottom - r.top) / 2;

	// ������ ���� Ÿ���� �������� �ּҸ� ������ ������ ����
	ID2D1HwndRenderTarget* p_hwnd_target;
	// ������ ������ Ŭ���̾�Ʈ ������ �׸��� �׸������� Render Target ����
	mp_factory->CreateHwndRenderTarget(RenderTargetProperties(),
		HwndRenderTargetProperties(m_hWnd, SizeU(r.right - r.left, r.bottom - r.top)), &p_hwnd_target);
	// �θ� �������̽��� �ּҸ� �����Ѵ�.
	mp_target = p_hwnd_target;

	D2D1_COLOR_F color = { 1.0f, 1.0f, 1.0f, 1.0f };					// RGBA
	// color �������� �귯�� ����
	mp_target->CreateSolidColorBrush(color, &mp_user_brush);

	// ����, ���� ���� �������� �׸��� ���� ȹ �Ӽ��� ����
	mp_factory->CreateStrokeStyle(D2D1::StrokeStyleProperties(D2D1_CAP_STYLE_FLAT,
		D2D1_CAP_STYLE_FLAT, D2D1_CAP_STYLE_ROUND,
		D2D1_LINE_JOIN_MITER, 10.0f,
		D2D1_DASH_STYLE_DOT, 0.0f), nullptr, 0, &mp_stroke_style);

	// �ִϸ��̼� ���� Ÿ�̸�
	SetTimer(1, 30, nullptr);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDirectX04Dlg::OnPaint()
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
HCURSOR CDirectX04Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDirectX04Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CDirectX04Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);

	// D2D ����
	__IRelease(&mp_stroke_style);
	__IRelease(&mp_user_brush);
	__IRelease(&mp_target);
	__IRelease(&mp_factory);
	CoUninitialize();
}


void CDirectX04Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		// D2D �׸��� ����
		mp_target->BeginDraw();
		// �׷��� ���� ������
		mp_target->Clear(ColorF(0.0f, 0.0f, 0.0f));

		D2D1_POINT_2F start = { (FLOAT)m_x, 0.0f };
		D2D1_POINT_2F end = { (FLOAT)m_x, (FLOAT)(m_y << 1) };
		D2D1_COLOR_F color = { 1.0f, 1.00f, 1.00f, 0.5f };				// RGBA
		// ����, ���� �࿡ ���� ����
		mp_user_brush->SetColor(color);
		// ������ �׸���
		mp_target->DrawLine(start, end, mp_user_brush, 3.0f, mp_stroke_style);
		start.x = 0.0f;
		start.y = (FLOAT)m_y;
		end.x = (FLOAT)(m_x << 1);
		end.y = (FLOAT)m_y;
		// ������ �׸���
		mp_target->DrawLine(start, end, mp_user_brush, 3.0f, mp_stroke_style);

		// ���� 4�� ������Ű�� 360�� �Ǹ� 0���� �����.
		m_degree = (m_degree + 4) % 360;
		// ���Ȱ����� ����
		double cur_process_radian = m_degree * COVT_RADIAN;

		ID2D1PathGeometry* p_geometry = nullptr;
		// ���� ������ ���ҽ��� ����
		HRESULT hr = mp_factory->CreatePathGeometry(&p_geometry);
		if (SUCCEEDED(hr)) {
			ID2D1GeometrySink* p_sink = nullptr;
			// ������ �߰��ϱ� ���� �Է¹��� sink �ڿ��� ����.
			hr = p_geometry->Open(&p_sink);
			if (SUCCEEDED(hr)) {
				// X�� �������� ���Ѵ�.
				int fix = m_x - 360;
				// ù �������� �����Ѵ�.
				start.x = (FLOAT)fix;
				start.y = (FLOAT)m_y;

				// ���� �������� �׷��� ���ϴ� ������ �׸���
				p_sink->BeginFigure(start, D2D1_FIGURE_BEGIN_FILLED);
				// ������ ���� ������ ������ ������ �׷����� �׸���.
				for (int x = 0; x < 2880; x += 4) {
					end.x = (FLOAT)((x >> 2) + fix);
					end.y = (FLOAT)(m_y - sin(x * COVT_RADIAN - cur_process_radian) * 100);
					p_sink->AddLine(end);
				}
				p_sink->EndFigure(D2D1_FIGURE_END_OPEN);
				p_sink->Close();

				__IRelease(&p_sink);				// �����߰��� ���� ����� sink�� �ݳ�
			}
			// ������ �ϴû�����
			color.a = 0.2f;
			mp_user_brush->SetColor(color);
			// ������ ȭ�鿡 ���
			mp_target->DrawGeometry(p_geometry, mp_user_brush, 20);
			color.r = 0.0f;
			color.g = 0.9961f;
			color.b = 0.5686f;
			color.a = 1.0f;
			mp_user_brush->SetColor(color);
			mp_target->DrawGeometry(p_geometry, mp_user_brush, 5);
			// ���� �ݳ�
			__IRelease(&p_geometry);
		}
		mp_target->EndDraw();
	}else{ CDialogEx::OnTimer(nIDEvent); }
}
