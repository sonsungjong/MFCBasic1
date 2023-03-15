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

	m_zoom_level = 0;				// ����� �� ũ�� ������ ����
	m_x = 0;
	m_y = 0;
	m_cx = IMAGE_WIDTH / 3;
	m_cy = IMAGE_HEIGHT / 3;
	m_is_clicked = 0;						// Ŭ�� �ȵ� ����
}

/*
��ġ ��ǥ�� �� ��ǥ�� �����ϴ� �ڵ�
logic_width : device_width = lx : dx
lx = dx * logic_width / device_width
*/
void CZoomInOutDlg::DpToLp(float a_dx, float a_dy, float* ap_lx, float* ap_ly)
{
	*ap_lx = a_dx * IMAGE_WIDTH / m_cx;
	*ap_ly = a_dy * IMAGE_HEIGHT / m_cy;
}

/*
�� ��ǥ�� ��ġ ��ǥ�� �����ϴ� �ڵ�
logic_width : device_width = lx : dx
dx = lx * device_width / logic_width
*/
void CZoomInOutDlg::LpToDp(float a_lx, float a_ly, float* ap_dx, float* ap_dy)
{
	*ap_dx = a_lx * m_cx / IMAGE_WIDTH;
	*ap_dy = a_ly * m_cy / IMAGE_HEIGHT;
}

// �ٽ� �׸��� �Լ�
void CZoomInOutDlg::RedrawMapImage()
{
	// ���� �ܻ��� �����ϱ� ���� ������ �̹����� ������ �����ϰ� �����
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
		// ���콺 �� ������ ��� ( 0 ~ 10 )
	}
	else {
		if (m_zoom_level < 10) { m_zoom_level++; }
		// ���콺 �� �ø��� Ȯ�� ( 0 ~ 10 )
	}

	if (old_zoom_level != m_zoom_level) {
		// ���� ���콺�� ��ġ ���ϱ�
		POINT position;
		GetCursorPos(&position);							// ���콺 Ŀ���� ��ġ�� ����
		::ScreenToClient(m_hWnd, &position);			// ȭ�� ��ǥ�踦 Ŭ���̾�Ʈ ��ǥ��� ����
		float mouse_x = (float)position.x;
		float mouse_y = (float)position.y;
		float lx, ly, dx, dy;
		// Ȯ�� ������ ����Ǳ� �� ���콺�� ������ �� ��ǥ�� ����
		DpToLp(mouse_x - m_x, mouse_y - m_y, &lx, &ly);
		// ����� Ȯ�� ������ ���� ��µ� �׸��� ���� ���̸� ���
		m_cx = int(IMAGE_WIDTH / (3 - 0.2f * m_zoom_level));
		m_cy = int(IMAGE_HEIGHT / (3 - 0.2f * m_zoom_level));
		// ����� �׸��� ���� ���̸� �������� �� ��ǥ�� �ش��ϴ� ��ġ ��ǥ�� ���Ѵ�
		LpToDp(lx, ly, &dx, &dy);
		// ���� ���콺 ��ġ�� �ִ� �׸��� �״�� ���콺 ��ġ�� �̵��ϵ��� ��ġ�� ����
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
		// ����� ���� ��ǥ�� ���� ���콺 ��ǥ�� ���� �̵��Ÿ�
		// �̵��Ÿ� ��ŭ ���� ����� ��ġ�� �����Ѵ�
		m_x += (short)point.x - (short)m_clicked_position.x;
		m_y += (short)point.y - (short)m_clicked_position.y;
		m_clicked_position = point;					// ���� ��ġ�� �ٽ� ����

		RedrawMapImage();
		Invalidate(FALSE);				// ����� �����ϰ� WM_PAINT �߻�
		UpdateWindow();				// CPU ���ɿ� ������� WM_PAINT�� ��� ����
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
