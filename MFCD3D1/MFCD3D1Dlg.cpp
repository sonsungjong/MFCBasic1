
// MFCD3D1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCD3D1.h"
#include "MFCD3D1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCD3D1Dlg dialog
#pragma comment(lib, "D3D11.lib")


CMFCD3D1Dlg::CMFCD3D1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCD3D1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}



void CMFCD3D1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCD3D1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCD3D1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCD3D1Dlg::OnBnClickedCancel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCD3D1Dlg message handlers

BOOL CMFCD3D1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// D3D 초기화
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = 640;
	sd.BufferDesc.Height = 480;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = GetSafeHwnd();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	D3D_FEATURE_LEVEL FeatureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL FeatureLevel;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &FeatureLevels, 1, D3D11_SDK_VERSION, &sd, &pSwapChain, &pd3dDevice, &FeatureLevel, &pImmediateContext);
	if (FAILED(hr))
	{
		MessageBox(_T("Direct3D 초기화에 실패했습니다."), _T("에러"), MB_OK);
		return FALSE;
	}

	// 렌더 타겟 뷰 생성
	ID3D11Texture2D* pBackBuffer = NULL;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr)) { return FALSE; }

	hr = pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr)) { return FALSE; }

	pImmediateContext->OMSetRenderTargets(1, &pRenderTargetView, NULL);

	// 뷰포트 설정
	D3D11_VIEWPORT vp;
	vp.Width = 640;
	vp.Height = 480;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pImmediateContext->RSSetViewports(1, &vp);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCD3D1Dlg::OnPaint()
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
		Render();
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCD3D1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCD3D1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCD3D1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CMFCD3D1Dlg::Render()
{
	if (pImmediateContext == nullptr) { return; }

	// 화면을 파란색으로 지우기
	float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
	pImmediateContext->ClearRenderTargetView(pRenderTargetView, clearColor);

	// 화면 출력
	pSwapChain->Present(0, 0);
}

void CMFCD3D1Dlg::Cleanup()
{
	if (pImmediateContext) { pImmediateContext->ClearState(); }
	if (pRenderTargetView) { pRenderTargetView->Release(); }
	if (pSwapChain) { pSwapChain->Release(); }
	if (pd3dDevice) { pd3dDevice->Release(); }
}

void CMFCD3D1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	Cleanup();
}
