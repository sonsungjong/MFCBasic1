
// Resize_Move_WndDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Resize_Move_Wnd.h"
#include "Resize_Move_WndDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CResizeMoveWndDlg dialog



CResizeMoveWndDlg::CResizeMoveWndDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RESIZE_MOVE_WND_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CResizeMoveWndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CResizeMoveWndDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CResizeMoveWndDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CResizeMoveWndDlg::OnBnClickedCancel)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CResizeMoveWndDlg message handlers

BOOL CResizeMoveWndDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// ĸ���� �������� ������ ���α׷� ������ ����
	SetWindowText(_T("������ �̵� �� ũ�� ���� ��� �����ϱ�"));

	// ��Ȳ�� ���콺 Ŀ�� �̸� �����Ѵ�.
	TCHAR* p_cursor_type[10] = {
		IDC_ARROW, IDC_ARROW, IDC_SIZENS, IDC_SIZENESW, IDC_SIZEWE,
		IDC_SIZENWSE, IDC_SIZENS, IDC_SIZENESW, IDC_SIZEWE, IDC_SIZENWSE
	};

	// ��Ȳ�� ���콺 �̹����� �ε��Ѵ�
	for (int i = 0; i < 10; i++) {
		mh_cursor[i] = ::LoadCursor(NULL, p_cursor_type[i]);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CResizeMoveWndDlg::OnPaint()
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
HCURSOR CResizeMoveWndDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CResizeMoveWndDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CResizeMoveWndDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CResizeMoveWndDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_is_clicked) {				// (����ó��) Ŭ���� �ƴ� ���¿��� Ŭ����
		CRect r;
		GetClientRect(r);

		// ������ ũ�� ��ȭ ������ ������ ������ ����Ѵ�				// +- 7 �� �׵θ� ������ ����(ũ�⺯���� ���� ����)
		CRect temp_rect(r.left + 7, r.top + 7, r.right - 7, r.bottom - 7);
		m_prev_pos = point;					// �̵� �� ũ�⺯ȭ üũ�ϱ� ���� ���� ��ġ�� ���

		if (temp_rect.PtInRect(point)) {					// �׵θ��� �ƴ� ���� ������ Ŭ��
			m_is_clicked = 1;				// ȭ�� �̵� ����
		}
		else {				// �׵θ� Ŭ�� (ũ�⺯��)
			if (point.x <= 7 && point.y <= 7) {				// ���� ���
				m_is_clicked = 9;
			}
			else if (point.x >= (r.right - 7) && point.y >= (r.bottom - 7)) {				// ���� �ϴ�
				m_is_clicked = 5;
			}
			else if (point.x >= (r.right - 7) && point.y <= 7) {				// ���� ���
				m_is_clicked = 3;
			}
			else if (point.x <= 7 && point.y >= (r.bottom - 7)) {				// ���� �ϴ�
				m_is_clicked = 7;
			}
			else if (point.y <= 7) {					// ���
				m_is_clicked = 2;
			}
			else if (point.x >= (r.right - 7)) {				// ����
				m_is_clicked = 4;
			}
			else if (point.y >= (r.bottom - 7)) {				// �Ʒ���
				m_is_clicked = 6;
			}
			else {				// ����
				m_is_clicked = 8;
			}

			SetCursor(mh_cursor[m_is_clicked]);				// ��Ȳ�� ���� ���콺 �̹��� ���
			ClientToScreen(&m_prev_pos);						// Ŭ���̾�Ʈ ��ǥ�� ������ ��ǥ�� ����
		}
		SetCapture();				// ���콺�� ������ ������ ����� �޽����� �޵��� ����
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CResizeMoveWndDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect r;
	CPoint pos;

	if (m_is_clicked) {
		GetWindowRect(r);				// ���� ������ ��ǥ�� ��´� (ȭ�� ��ǥ��)

		// �̵��Ÿ��� ���Ѵ� (������ - ������)
		// �̵��Ÿ��� ������ ��ǥ�� �ݿ��Ͽ� �̵���Ų��
		if (m_is_clicked == 1) {
			SetWindowPos(NULL, r.left + point.x - m_prev_pos.x, r.top + point.y - m_prev_pos.y, 0, 0, SWP_NOSIZE);
		}
		else {				// ũ�� ��ȭ ���¶�� ���콺 ��ǥ�� ������ ��ǥ��� �����Ѵ�
			pos = point;
			ClientToScreen(&pos);

			if (m_is_clicked == 2) {								// ���
				if (r.Height() - (pos.y - m_prev_pos.y) >= 20) {
					SetWindowPos(NULL, r.left, r.top + pos.y - m_prev_pos.y, r.Width(), r.Height() - (pos.y - m_prev_pos.y), 0);
				}
			}
			else if (m_is_clicked == 3) {				// ���� ���
				if ((r.Width() + pos.x - m_prev_pos.x) >= 20 && r.Height() - (pos.y - m_prev_pos.y) >= 20) {
					SetWindowPos(NULL, r.left, r.top + pos.y - m_prev_pos.y, r.Width() + pos.x - m_prev_pos.x, r.Height() - (pos.y - m_prev_pos.y), 0);
				}
			}
			else if (m_is_clicked == 4) {					// ���� ũ�� ��ȭ
				if ((r.Width() + pos.x - m_prev_pos.x) >= 20 && r.Height() - (pos.y - m_prev_pos.y) >= 20) {
					SetWindowPos(NULL, 0, 0, r.Width() + pos.x - m_prev_pos.x, r.Height(), SWP_NOMOVE);
				}
			}
			else if (m_is_clicked == 5) {					// ����/�ϴ� ũ�� ��ȭ
				if ((r.Width() + pos.x - m_prev_pos.x) >= 20 && (r.Height() + pos.y - m_prev_pos.y) >= 20) {
					SetWindowPos(NULL, 0, 0, r.Width() + pos.x - m_prev_pos.x, r.Height() + pos.y - m_prev_pos.y, SWP_NOMOVE);
				}
			}
			else if (m_is_clicked == 6) {						// �ϴ� ũ�� ��ȭ
				if ((r.Height() + pos.y - m_prev_pos.y) >= 20) {
					SetWindowPos(NULL, 0, 0, r.Width(), r.Height() + pos.y - m_prev_pos.y, SWP_NOMOVE);
				}
			}
			else if (m_is_clicked == 7) {					// ����/�ϴ� ũ�� ��ȭ
				if ((r.Height() + pos.y - m_prev_pos.y) >= 20 && r.Width() - (pos.x - m_prev_pos.x) >= 20) {
					SetWindowPos(NULL, r.left + pos.x - m_prev_pos.x, r.top, r.Width() - (pos.x - m_prev_pos.x), r.Height() + pos.y - m_prev_pos.y, 0);
				}
			}
			else if (m_is_clicked == 8) {					// ����
				if (r.Width() - (pos.x - m_prev_pos.x) >= 20) {
					SetWindowPos(NULL, r.left + pos.x - m_prev_pos.x, r.top, r.Width() - (pos.x - m_prev_pos.x), r.Height(), 0);
				}
			}
			else {													// ���� ���
				if (r.Width() - (pos.x - m_prev_pos.x) >= 20 && r.Height() - (pos.y - m_prev_pos.y) >= 20) {
					SetWindowPos(NULL, r.left + pos.x - m_prev_pos.x, r.top + pos.y - m_prev_pos.y, r.Width() - (pos.x - m_prev_pos.x), r.Height() - (pos.y - m_prev_pos.y), 0);
				}
			}

			SetCursor(mh_cursor[m_is_clicked]);				// ��Ȳ�� �´� Ŀ���� ����
			m_prev_pos = pos;						// ���� ��ġ�� ���� �̵��� ���� ��ġ�� ����ϱ� ���� �����Ѵ�
		}
	}
	else {
		GetClientRect(r);				// Ŭ���̾�Ʈ ��ǥ�� ��´�
		CRect temp_rect(r.left + 7, r.top + 7, r.right - 7, r.bottom - 7);				// ���� (�׵θ� ����)

		if (!temp_rect.PtInRect(point)) {					// �׵θ��� ���콺 Ŀ���� ������ (���ΰ� �ƴϸ�)
			int index = 0;

			// ��Ȳ�� Ŀ�� ������ ����
			if ((point.x <= 7 && point.y <= 7) || (point.x >= (r.right - 7) && point.y >= (r.bottom - 7))) {
				index = 5;
			}
			else if ((point.x >= (r.right - 7) && point.y <= 7) || (point.x <= 7 && point.y >= (r.bottom - 7))) {
				index = 3;
			}
			else if (point.x <= 7 || point.x >= r.right - 7) {
				index = 4;
			}
			else {
				index = 2;
			}

			SetCursor(mh_cursor[index]);
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CResizeMoveWndDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_is_clicked){				// Ŭ�� ����
		m_is_clicked = 0;				// Ŭ�� ������ ����
		ReleaseCapture();				// SetCapture ����
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}
