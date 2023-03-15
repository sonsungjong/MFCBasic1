#include "pch.h"
#include "framework.h"
#include "ZoomInOut.h"
#include "ZoomInOutDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CZoomInOutDlg::CZoomInOutDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ZOOMINOUT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_zoom_level = 0;				// 삼분의 일 크기 배율로 시작
	m_x = 0;
	m_y = 0;
	m_cx = IMAGE_WIDTH / 3;
	m_cy = IMAGE_HEIGHT / 3;
	m_is_clicked = 0;						// 클릭 안된 상태
}

/*
장치 좌표를 논리 좌표로 변경하는 코드
logic_width : device_width = lx : dx
lx = dx * logic_width / device_width
*/
void CZoomInOutDlg::DpToLp(float a_dx, float a_dy, float* ap_lx, float* ap_ly)
{
	*ap_lx = a_dx * IMAGE_WIDTH / m_cx;
	*ap_ly = a_dy * IMAGE_HEIGHT / m_cy;
}

/*
논리 좌표를 장치 좌표로 변경하는 코드
logic_width : device_width = lx : dx
dx = lx * device_width / logic_width
*/
void CZoomInOutDlg::LpToDp(float a_lx, float a_ly, float* ap_dx, float* ap_dy)
{
	*ap_dx = a_lx * m_cx / IMAGE_WIDTH;
	*ap_dy = a_ly * m_cy / IMAGE_HEIGHT;
}

// 다시 그리는 함수
void CZoomInOutDlg::RedrawMapImage()
{
	// 지도 잔상을 제거하기 위해 배경색을 이미지의 배경색과 동일하게 맞춘다
	m_draw_dc.FillSolidRect(m_client_rect, RGB(157, 199, 232));
	m_image.Draw(m_draw_dc, m_x, m_y, m_cx, m_cy);
}

void CZoomInOutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CZoomInOutDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CZoomInOutDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CZoomInOutDlg::OnBnClickedCancel)
	ON_WM_MOUSEWHEEL()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CZoomInOutDlg message handlers

BOOL CZoomInOutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetClientRect(m_client_rect);
	m_draw_image.Create(m_client_rect.Width(), m_client_rect.Height(), 32);
	m_draw_dc.Attach(m_draw_image.GetDC());
	m_image.Load(_T("../img/jeju.png"));
	RedrawMapImage();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CZoomInOutDlg::OnPaint()
{
		CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{

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
		m_draw_image.Draw(dc, m_client_rect);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CZoomInOutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CZoomInOutDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CZoomInOutDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


BOOL CZoomInOutDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	int old_zoom_level = m_zoom_level;
	if (zDelta < 0) {
		if (m_zoom_level > 0) { m_zoom_level--; }
		// 마우스 휠 내리면 축소 ( 0 ~ 10 )
	}
	else {
		if (m_zoom_level < 10) { m_zoom_level++; }
		// 마우스 휠 올리면 확대 ( 0 ~ 10 )
	}

	if (old_zoom_level != m_zoom_level) {
		// 현재 마우스의 위치 구하기
		POINT position;
		GetCursorPos(&position);							// 마우스 커서의 위치를 얻음
		::ScreenToClient(m_hWnd, &position);			// 화면 좌표계를 클라이언트 좌표계로 변경
		float mouse_x = (float)position.x;
		float mouse_y = (float)position.y;
		float lx, ly, dx, dy;
		// 확대 비율이 변경되기 전 마우스가 위차한 논리 좌표를 구함
		DpToLp(mouse_x - m_x, mouse_y - m_y, &lx, &ly);
		// 변경된 확대 비율을 통해 출력될 그림의 폭과 높이를 계산
		m_cx = int(IMAGE_WIDTH / (3 - 0.2f * m_zoom_level));
		m_cy = int(IMAGE_HEIGHT / (3 - 0.2f * m_zoom_level));
		// 변경된 그림의 폭과 높이를 기준으로 논리 좌표에 해당하는 장치 좌표를 구한다
		LpToDp(lx, ly, &dx, &dy);
		// 이전 마우스 위치에 있던 그림이 그대로 마우스 위치에 이동하도록 위치를 조정
		m_x = int(mouse_x - dx);
		m_y = int(mouse_y - dy);

		RedrawMapImage();
		Invalidate(FALSE);
	}

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CZoomInOutDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	m_draw_dc.Detach();
	m_draw_image.ReleaseDC();
	m_draw_image.Destroy();
}


void CZoomInOutDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_is_clicked) {
		m_clicked_position = point;
		m_is_clicked = 1;
		SetCapture();
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CZoomInOutDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked == 1) {
		ReleaseCapture();
		m_is_clicked = 0;
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CZoomInOutDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked == 1) {
		// 저장된 이전 좌표와 현재 마우스 좌표를 빼면 이동거리
		// 이동거리 만큼 지도 출력의 위치를 변경한다
		m_x += (short)point.x - (short)m_clicked_position.x;
		m_y += (short)point.y - (short)m_clicked_position.y;
		m_clicked_position = point;					// 현재 위치를 다시 저장

		RedrawMapImage();
		Invalidate(FALSE);				// 배경을 제외하고 WM_PAINT 발생
		UpdateWindow();				// CPU 성능에 상관없이 WM_PAINT를 즉시 수행
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
