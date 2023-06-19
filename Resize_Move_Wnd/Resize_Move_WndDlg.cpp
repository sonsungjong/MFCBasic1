
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
	// 캡션이 없어져서 강제로 프로그램 제목을 지정
	SetWindowText(_T("윈도우 이동 및 크기 변경 기능 구현하기"));

	// 상황별 마우스 커서 이름 지정한다.
	TCHAR* p_cursor_type[10] = {
		IDC_ARROW, IDC_ARROW, IDC_SIZENS, IDC_SIZENESW, IDC_SIZEWE,
		IDC_SIZENWSE, IDC_SIZENS, IDC_SIZENESW, IDC_SIZEWE, IDC_SIZENWSE
	};

	// 상황별 마우스 이미지를 로드한다
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
	if (!m_is_clicked) {				// (예외처리) 클릭이 아닌 상태에서 클릭됨
		CRect r;
		GetClientRect(r);

		// 윈도우 크기 변화 영역을 제외한 영역을 계산한다				// +- 7 를 테두리 범위로 설정(크기변경을 위한 범위)
		CRect temp_rect(r.left + 7, r.top + 7, r.right - 7, r.bottom - 7);
		m_prev_pos = point;					// 이동 및 크기변화 체크하기 위해 현재 위치를 기억

		if (temp_rect.PtInRect(point)) {					// 테두리가 아닌 내부 영역을 클릭
			m_is_clicked = 1;				// 화면 이동 전용
		}
		else {				// 테두리 클릭 (크기변경)
			if (point.x <= 7 && point.y <= 7) {				// 좌측 상단
				m_is_clicked = 9;
			}
			else if (point.x >= (r.right - 7) && point.y >= (r.bottom - 7)) {				// 우측 하단
				m_is_clicked = 5;
			}
			else if (point.x >= (r.right - 7) && point.y <= 7) {				// 우측 상단
				m_is_clicked = 3;
			}
			else if (point.x <= 7 && point.y >= (r.bottom - 7)) {				// 좌측 하단
				m_is_clicked = 7;
			}
			else if (point.y <= 7) {					// 상단
				m_is_clicked = 2;
			}
			else if (point.x >= (r.right - 7)) {				// 우측
				m_is_clicked = 4;
			}
			else if (point.y >= (r.bottom - 7)) {				// 아래쪽
				m_is_clicked = 6;
			}
			else {				// 왼쪽
				m_is_clicked = 8;
			}

			SetCursor(mh_cursor[m_is_clicked]);				// 상황에 따른 마우스 이미지 출력
			ClientToScreen(&m_prev_pos);						// 클라이언트 좌표를 윈도우 좌표로 변경
		}
		SetCapture();				// 마우스가 윈도우 영역을 벗어나도 메시지를 받도록 설정
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CResizeMoveWndDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect r;
	CPoint pos;

	if (m_is_clicked) {
		GetWindowRect(r);				// 현재 윈도우 좌표를 얻는다 (화면 좌표계)

		// 이동거리를 구한다 (현재점 - 이전점)
		// 이동거리를 윈도우 좌표에 반영하여 이동시킨다
		if (m_is_clicked == 1) {
			SetWindowPos(NULL, r.left + point.x - m_prev_pos.x, r.top + point.y - m_prev_pos.y, 0, 0, SWP_NOSIZE);
		}
		else {				// 크기 변화 상태라면 마우스 좌표를 윈도우 좌표계로 변경한다
			pos = point;
			ClientToScreen(&pos);

			if (m_is_clicked == 2) {								// 상단
				if (r.Height() - (pos.y - m_prev_pos.y) >= 20) {
					SetWindowPos(NULL, r.left, r.top + pos.y - m_prev_pos.y, r.Width(), r.Height() - (pos.y - m_prev_pos.y), 0);
				}
			}
			else if (m_is_clicked == 3) {				// 우측 상단
				if ((r.Width() + pos.x - m_prev_pos.x) >= 20 && r.Height() - (pos.y - m_prev_pos.y) >= 20) {
					SetWindowPos(NULL, r.left, r.top + pos.y - m_prev_pos.y, r.Width() + pos.x - m_prev_pos.x, r.Height() - (pos.y - m_prev_pos.y), 0);
				}
			}
			else if (m_is_clicked == 4) {					// 우측 크기 변화
				if ((r.Width() + pos.x - m_prev_pos.x) >= 20 && r.Height() - (pos.y - m_prev_pos.y) >= 20) {
					SetWindowPos(NULL, 0, 0, r.Width() + pos.x - m_prev_pos.x, r.Height(), SWP_NOMOVE);
				}
			}
			else if (m_is_clicked == 5) {					// 우측/하단 크기 변화
				if ((r.Width() + pos.x - m_prev_pos.x) >= 20 && (r.Height() + pos.y - m_prev_pos.y) >= 20) {
					SetWindowPos(NULL, 0, 0, r.Width() + pos.x - m_prev_pos.x, r.Height() + pos.y - m_prev_pos.y, SWP_NOMOVE);
				}
			}
			else if (m_is_clicked == 6) {						// 하단 크기 변화
				if ((r.Height() + pos.y - m_prev_pos.y) >= 20) {
					SetWindowPos(NULL, 0, 0, r.Width(), r.Height() + pos.y - m_prev_pos.y, SWP_NOMOVE);
				}
			}
			else if (m_is_clicked == 7) {					// 좌측/하단 크기 변화
				if ((r.Height() + pos.y - m_prev_pos.y) >= 20 && r.Width() - (pos.x - m_prev_pos.x) >= 20) {
					SetWindowPos(NULL, r.left + pos.x - m_prev_pos.x, r.top, r.Width() - (pos.x - m_prev_pos.x), r.Height() + pos.y - m_prev_pos.y, 0);
				}
			}
			else if (m_is_clicked == 8) {					// 좌측
				if (r.Width() - (pos.x - m_prev_pos.x) >= 20) {
					SetWindowPos(NULL, r.left + pos.x - m_prev_pos.x, r.top, r.Width() - (pos.x - m_prev_pos.x), r.Height(), 0);
				}
			}
			else {													// 좌측 상단
				if (r.Width() - (pos.x - m_prev_pos.x) >= 20 && r.Height() - (pos.y - m_prev_pos.y) >= 20) {
					SetWindowPos(NULL, r.left + pos.x - m_prev_pos.x, r.top + pos.y - m_prev_pos.y, r.Width() - (pos.x - m_prev_pos.x), r.Height() - (pos.y - m_prev_pos.y), 0);
				}
			}

			SetCursor(mh_cursor[m_is_clicked]);				// 상황에 맞는 커서로 변경
			m_prev_pos = pos;						// 현재 위치를 다음 이동의 이전 위치로 사용하기 위해 저장한다
		}
	}
	else {
		GetClientRect(r);				// 클라이언트 좌표를 얻는다
		CRect temp_rect(r.left + 7, r.top + 7, r.right - 7, r.bottom - 7);				// 내부 (테두리 안쪽)

		if (!temp_rect.PtInRect(point)) {					// 테두리에 마우스 커서가 있으면 (내부가 아니면)
			int index = 0;

			// 상황별 커서 종류를 선택
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
	if(m_is_clicked){				// 클릭 상태
		m_is_clicked = 0;				// 클릭 해제로 변경
		ReleaseCapture();				// SetCapture 해제
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}
