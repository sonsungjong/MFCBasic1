
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

// D2D ���̺귯��
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
	// COM �ʱ�ȭ
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	// D2D Factory ����
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mp_factory);

	// ���ڿ� ��� ���丮 ����
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(mp_write_factory),
		reinterpret_cast<IUnknown**>(&mp_write_factory));

	// ���ڿ� ��� ������ ������ �ڿ��� �����Ѵ�.
	if (S_OK == mp_write_factory->CreateTextFormat(_T("����ǹ���"), nullptr,
		DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		22, _T("ko-kr"), &mp_text_format)) {
		// ����� �� �������Ŀɼ� ���� (���)
		mp_text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		// ����� �� �������Ŀɼ� ���� (���)
		mp_text_format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	::RECT r;
	// Ŭ���̾�Ʈ ���� ���
	::GetClientRect(m_hWnd, &r);

	// ����Ÿ���� �����Ͽ� �ּҸ� ������ ������ ����
	ID2D1HwndRenderTarget* p_hwnd_target;
	// ������ �������� Ŭ���̾�Ʈ ������ �׸��� �׸������� Render Target ����
	mp_factory->CreateHwndRenderTarget(RenderTargetProperties(),
		HwndRenderTargetProperties(m_hWnd, SizeU(r.right - r.left, r.bottom - r.top)), &p_hwnd_target);

	// �θ� �������̽� �ּҸ� �����Ѵ�
	mp_target = p_hwnd_target;

	// ���� �ؽ�Ʈ ��¿� ����� �귯�ø� �����Ѵ�.
	mp_target->CreateSolidColorBrush(m_btn_border_color[0], &mp_user_brush);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CD2DButton1Dlg::UserDraw()
{
	mp_target->BeginDraw();
	// ȭ�� ��ü�� ���������� ä���
	mp_target->Clear(ColorF(ColorF::Black));

	if (mp_text_format) {
		// "SonSungJong" ��ư�� ����Ѵ�.
		mp_user_brush->SetColor(m_btn_border_color[m_btn_state[0]]);
		mp_target->DrawRectangle(m_btn_rect[0], mp_user_brush, 3);
		mp_user_brush->SetColor(m_text_color[m_btn_state[0]]);
		D2D1_RECT_F r = m_btn_rect[0];
		if (m_btn_state[0]) {				// ��ư�� ������ ���¶�� ��¦ �Ʒ������� �̵�
			r.left += 1.0f;
			r.top += 1.0f;
			r.right += 1.0f;
			r.bottom += 1.0f;
		}
		mp_target->DrawText(_T("SonSungJong"), 12, mp_text_format, r, mp_user_brush);

		// "�ռ���" ��ư�� ���
		D2D1_ROUNDED_RECT round_r = { m_btn_rect[1], 9.0f, 9.0f };
		mp_user_brush->SetColor(m_btn_border_color[m_btn_state[1]]);
		mp_target->DrawRoundedRectangle(&round_r, mp_user_brush, 3);
		mp_user_brush->SetColor(m_text_color[m_btn_state[1]]);
		r = m_btn_rect[1];
		if (m_btn_state[1]) {			// ��ư�� ������ ���¸� ��¦ �Ʒ��� �̵�
			r.left += 1.0f;
			r.top += 1.0f;
			r.right += 1.0f;
			r.bottom += 1.0f;
		}
		mp_target->DrawText(_T("�ռ���"), 3, mp_text_format, r, mp_user_brush);

		// "��������" ��ư�� ����Ѵ�
		round_r.rect = m_btn_rect[2];
		round_r.radiusX = 20.0f;
		round_r.radiusY = 20.0f;
		mp_user_brush->SetColor(m_btn_border_color[m_btn_state[2]]);
		mp_target->DrawRoundedRectangle(&round_r, mp_user_brush, 3);
		mp_user_brush->SetColor(m_text_color[m_btn_state[2]]);
		r = m_btn_rect[2];
		if (m_btn_state[2]) {				// ��ư�� ������ ���¸� ��¦ �Ʒ��� �̵�
			r.left += 1.0f;
			r.top += 1.0f;
			r.right += 1.0f;
			r.bottom += 1.0f;
		}
		mp_target->DrawText(_T("��������"), 4, mp_text_format, r, mp_user_brush);
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
		// ���� ��ư üũ
		if (__PtInRectF(m_btn_rect + i, &point)) {
			// ������ ��ư�� �ε����� �����Ѵ�
			m_selected_btn = i;
			// ������ ��ư�� ���¸� 1�� �����
			m_btn_state[m_selected_btn] = 1;
			// ���� ��Ȳ�� �ݿ��ǵ��� ��ư�� �ٽ� �׸���
			UserDraw();
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CD2DButton1Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	// ������ ��ư�� �ִ��� üũ�Ѵ�
	if (m_selected_btn != 0xFF) {
		// ��ư�� ���°� 1�� ��쿡�� Ŭ�� ���¸� �뺸�Ѵ�
		// �̹� 0�̶�� ��ư �ۿ� ���콺�� �ִ� ���¶� �ٽ� �׸��� �ʴ´�
		if (m_btn_state[m_selected_btn] == 1) {
			if (__PtInRectF(m_btn_rect + m_selected_btn, &point)) {
				PostMessage(27000, m_selected_btn);
			}
			m_btn_state[m_selected_btn] = 0;
			UserDraw();
		}
		// ��ư ���� ���� �ʱ�ȭ
		m_selected_btn = 0xFF;
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CD2DButton1Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	// ���õ� ��ư�� �ִ��� üũ
	if (m_selected_btn != 0xFF) {
		// ��ư ���ο� ���콺�� �ִ��� üũ
		if (__PtInRectF(m_btn_rect + m_selected_btn, &point)) {
			// ���ο� �ִٰ� �ϴ��� �̹� 1�� ���¶��
			// ���¸� �ٽ� �������� �ʴ´�
			if (m_btn_state[m_selected_btn] == 0) {
				m_btn_state[m_selected_btn] = 1;
				UserDraw();
			}
		} else {
			// �ܺο� �ִٰ� �ϴ��� �̹� 0�� ���¸�
			// ���¸� �ٽ� �������� �ʴ´�
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
	// ���õ� ��ư�� �ش��ϴ� �޽����� ȭ�鿡 ����Ѵ�
	const TCHAR* p_msg_list[3] = { _T("SonSungJong"), _T("�ռ���"), _T("��������") };
	AfxMessageBox(p_msg_list[wParam]);
	return 0;
}
