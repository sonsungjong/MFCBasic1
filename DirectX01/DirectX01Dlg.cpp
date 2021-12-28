
// DirectX01Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "DirectX01.h"
#include "DirectX01Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// D2D�� ����ϱ� ���� ���̺귯��
#pragma comment(lib, "D2D1.lib")


// CDirectX01Dlg dialog



CDirectX01Dlg::CDirectX01Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIRECTX01_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDirectX01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDirectX01Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDirectX01Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDirectX01Dlg::OnBnClickedCancel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDirectX01Dlg message handlers

BOOL CDirectX01Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// COM�� ����ϱ� ���� �ʱ�ȭ�Լ�
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	// D2D ����� ���� ���丮 ����
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mp_factory);

	RECT r;
	// Ŭ���̾�Ʈ ����
	::GetClientRect(m_hWnd, &r);

	// ������ ���� Ÿ�� ����
	ID2D1HwndRenderTarget* p_hwnd_target;
	// ������ �������� Ŭ���̾�Ʈ ������ �׸��� �׸��� ���� Render Target ����
	mp_factory->CreateHwndRenderTarget(RenderTargetProperties(), 
		HwndRenderTargetProperties(m_hWnd, SizeU(r.right - r.left, r.bottom - r.top)), &p_hwnd_target);

	// �θ� �������̽��� �ּҸ� ����
	mp_target = p_hwnd_target;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDirectX01Dlg::OnPaint()
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
		// WM_PAINT�߻��� ��ȿȭ
		::ValidateRect(m_hWnd, NULL);

		// D2D�� �׸��� �׸��� ����
		mp_target->BeginDraw();
		mp_target->Clear(ColorF(0.0f, 0.0f, 0.0f));					// ��� ����

		// �߽��� (50,50)�̰� ������15�� ��
		D2D1_ELLIPSE circle = { {50, 50}, 15, 15 };
		D2D1_COLOR_F color = { 0.0f, 0.1f, 0.0f, 1.0f };			// 10% ���

		// 28�� �׸� ���� ���� ����� ����ϱ�
		float step = 0.9f / 28;
		// �귯�� �ּ�
		ID2D1SolidColorBrush* p_green_brush = nullptr;
		mp_target->CreateSolidColorBrush(color, &p_green_brush);

		if (p_green_brush != nullptr) {
			for (int i = 0; i < 28; i++) {
				// ���� �׸�
				mp_target->FillEllipse(circle, p_green_brush);
				// �̵��ϸ鼭 ���� ũ��
				circle.point.x += 10;
				circle.point.y += 10;
				circle.radiusX++;
				circle.radiusY++;
				// �ʷϻ��� ������� ����
				color.g += step;
				// �ݿ�
				p_green_brush->SetColor(color);
			}
			IRelease(&p_green_brush);
		}
		// �׸��⸦ �����ϰ� ȭ�鿡 ���
		mp_target->EndDraw();
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDirectX01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDirectX01Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CDirectX01Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CDirectX01Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// D2D ��ü ����
	IRelease(&mp_target);
	IRelease(&mp_factory);
	CoUninitialize();
}
