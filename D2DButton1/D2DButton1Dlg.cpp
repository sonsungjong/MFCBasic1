
// D2DButton1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "D2DButton1.h"
#include "D2DButton1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// D2D 라이브러리
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "DWRITE.lib")

// CD2DButton1Dlg dialog



CD2DButton1Dlg::CD2DButton1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_D2DBUTTON1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CD2DButton1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CD2DButton1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CD2DButton1Dlg::OnBnClickedOk)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(27000, &CD2DButton1Dlg::On27000)
END_MESSAGE_MAP()


// CD2DButton1Dlg message handlers

BOOL CD2DButton1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// COM 초기화
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	// D2D Factory 생성
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mp_factory);

	// 문자열 출력 팩토리 생성
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(mp_write_factory),
		reinterpret_cast<IUnknown**>(&mp_write_factory));

	// 문자열 출력 형식을 지정할 자원을 생성한다.
	if (S_OK == mp_write_factory->CreateTextFormat(_T("배달의민족"), nullptr,
		DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		22, _T("ko-kr"), &mp_text_format)) {
		// 출력할 때 수평정렬옵션 지정 (가운데)
		mp_text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		// 출력할 때 수직정렬옵션 지정 (가운데)
		mp_text_format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	::RECT r;
	// 클라이언트 영역 얻기
	::GetClientRect(m_hWnd, &r);

	// 렌더타겟을 생성하여 주소를 가져올 포인터 선언
	ID2D1HwndRenderTarget* p_hwnd_target;
	// 지정한 윈도우의 클라이언트 영역에 그림을 그리기위한 Render Target 생성
	mp_factory->CreateHwndRenderTarget(RenderTargetProperties(),
		HwndRenderTargetProperties(m_hWnd, SizeU(r.right - r.left, r.bottom - r.top)), &p_hwnd_target);

	// 부모 인터페이스 주소를 보관한다
	mp_target = p_hwnd_target;

	// 선과 텍스트 출력에 사용할 브러시를 생성한다.
	mp_target->CreateSolidColorBrush(m_btn_border_color[0], &mp_user_brush);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CD2DButton1Dlg::UserDraw()
{
	mp_target->BeginDraw();
	// 화면 전체를 검은색으로 채운다
	mp_target->Clear(ColorF(ColorF::Black));

	if (mp_text_format) {
		// "SonSungJong" 버튼을 출력한다.
		mp_user_brush->SetColor(m_btn_border_color[m_btn_state[0]]);
		mp_target->DrawRectangle(m_btn_rect[0], mp_user_brush, 3);
		mp_user_brush->SetColor(m_text_color[m_btn_state[0]]);
		D2D1_RECT_F r = m_btn_rect[0];
		if (m_btn_state[0]) {				// 버튼이 눌려진 상태라면 살짝 아래쪽으로 이동
			r.left += 1.0f;
			r.top += 1.0f;
			r.right += 1.0f;
			r.bottom += 1.0f;
		}
		mp_target->DrawText(_T("SonSungJong"), 12, mp_text_format, r, mp_user_brush);

		// "손성종" 버튼을 출력
		D2D1_ROUNDED_RECT round_r = { m_btn_rect[1], 9.0f, 9.0f };
		mp_user_brush->SetColor(m_btn_border_color[m_btn_state[1]]);
		mp_target->DrawRoundedRectangle(&round_r, mp_user_brush, 3);
		mp_user_brush->SetColor(m_text_color[m_btn_state[1]]);
		r = m_btn_rect[1];
		if (m_btn_state[1]) {			// 버튼이 눌려진 상태면 살짝 아래로 이동
			r.left += 1.0f;
			r.top += 1.0f;
			r.right += 1.0f;
			r.bottom += 1.0f;
		}
		mp_target->DrawText(_T("손성종"), 3, mp_text_format, r, mp_user_brush);

		// "팁스웨어" 버튼을 출력한다
		round_r.rect = m_btn_rect[2];
		round_r.radiusX = 20.0f;
		round_r.radiusY = 20.0f;
		mp_user_brush->SetColor(m_btn_border_color[m_btn_state[2]]);
		mp_target->DrawRoundedRectangle(&round_r, mp_user_brush, 3);
		mp_user_brush->SetColor(m_text_color[m_btn_state[2]]);
		r = m_btn_rect[2];
		if (m_btn_state[2]) {				// 버튼이 눌려진 상태면 살짝 아래로 이동
			r.left += 1.0f;
			r.top += 1.0f;
			r.right += 1.0f;
			r.bottom += 1.0f;
		}
		mp_target->DrawText(_T("팁스웨어"), 4, mp_text_format, r, mp_user_brush);
	}
	mp_target->EndDraw();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CD2DButton1Dlg::OnPaint()
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
HCURSOR CD2DButton1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CD2DButton1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CD2DButton1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	__IRelease(&mp_user_brush);
	__IRelease(&mp_text_format);
	__IRelease(&mp_write_factory);
	__IRelease(&mp_target);
	__IRelease(&mp_factory);
	CoUninitialize();
}

__inline int __PtInRectF(D2D1_RECT_F* ap_rect, CPoint* ap_pos)
{
	return ap_rect->left <= ap_pos->x && ap_rect->top <= ap_pos->y &&
		ap_rect->right >= ap_pos->x && ap_rect->bottom >= ap_pos->y;
}

void CD2DButton1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	for (int i = 0; i < 3; i++) {
		// 눌린 버튼 체크
		if (__PtInRectF(m_btn_rect + i, &point)) {
			// 선택한 버튼의 인덱스를 저장한다
			m_selected_btn = i;
			// 선택한 버튼의 상태를 1로 만든다
			m_btn_state[m_selected_btn] = 1;
			// 선택 상황이 반영되도록 버튼을 다시 그린다
			UserDraw();
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CD2DButton1Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	// 선택한 버튼이 있는지 체크한다
	if (m_selected_btn != 0xFF) {
		// 버튼의 상태가 1인 경우에만 클릭 상태를 통보한다
		// 이미 0이라면 버튼 밖에 마우스가 있는 상태라서 다시 그리지 않는다
		if (m_btn_state[m_selected_btn] == 1) {
			if (__PtInRectF(m_btn_rect + m_selected_btn, &point)) {
				PostMessage(27000, m_selected_btn);
			}
			m_btn_state[m_selected_btn] = 0;
			UserDraw();
		}
		// 버튼 선택 상태 초기화
		m_selected_btn = 0xFF;
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CD2DButton1Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	// 선택된 버튼이 있는지 체크
	if (m_selected_btn != 0xFF) {
		// 버튼 내부에 마우스가 있는지 체크
		if (__PtInRectF(m_btn_rect + m_selected_btn, &point)) {
			// 내부에 있다고 하더라도 이미 1인 상태라면
			// 상태를 다시 설정하지 않는다
			if (m_btn_state[m_selected_btn] == 0) {
				m_btn_state[m_selected_btn] = 1;
				UserDraw();
			}
		} else {
			// 외부에 있다고 하더라도 이미 0인 상태면
			// 상태를 다시 결정하지 않는다
			if (m_btn_state[m_selected_btn] == 1) {
				m_btn_state[m_selected_btn] = 0;
				UserDraw();
			}
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


afx_msg LRESULT CD2DButton1Dlg::On27000(WPARAM wParam, LPARAM lParam)
{
	// 선택된 버튼에 해당하는 메시지를 화면에 출력한다
	const TCHAR* p_msg_list[3] = { _T("SonSungJong"), _T("손성종"), _T("팁스웨어") };
	AfxMessageBox(p_msg_list[wParam]);
	return 0;
}
