
// MFCBasic218Circle2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic218Circle2.h"
#include "MFCBasic218Circle2Dlg.h"
#include "afxdialogex.h"
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic218Circle2Dlg dialog



CMFCBasic218Circle2Dlg::CMFCBasic218Circle2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC218CIRCLE2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic218Circle2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic218Circle2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMFCBasic218Circle2Dlg message handlers

BOOL CMFCBasic218Circle2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetClientRect(m_rect);								// ��ȭ���� Ŭ���̾�Ʈ ��ǥ�� ����
	m_center = m_rect.CenterPoint();				// �߽��� ��ȯ

	// �޸�DC
	m_image.Create(m_rect.Width(), m_rect.Height(), 32);				// 32bit ���� �̹���
	m_image_dc.Attach(m_image.GetDC());

	m_grid_pen.CreatePen(PS_DOT, 1, RGB(168, 168, 168));						// ȸ��
	m_green_pen.CreatePen(PS_SOLID, 2, RGB(100, 255, 100));				// ���� ���
	m_yellow_pen.CreatePen(PS_SOLID, 2, RGB(255, 255, 0));					// ���
	m_pie_brush.CreateHatchBrush(HS_DIAGCROSS, RGB(255, 200, 0));	// ��ο� ���
	SetBackgroundColor(RGB(0, 0, 0));
	m_image_dc.SetBkColor(RGB(0, 0, 0));
	ShowGrid();

	m_image_dc.SelectObject(&m_green_pen);
	m_image_dc.SelectStockObject(NULL_BRUSH);
	m_image_dc.Ellipse(m_center.x - 200, m_center.y - 200, m_center.x + 200, m_center.y + 200);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic218Circle2Dlg::OnPaint()
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
		m_image.Draw(dc, 0, 0);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic218Circle2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic218Circle2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	// �޸�DC ����
	m_image_dc.Detach();
	m_image.ReleaseDC();

	DeleteObject(m_grid_pen);
	DeleteObject(m_green_pen);
	DeleteObject(m_yellow_pen);
	DeleteObject(m_pie_brush);
}

void CMFCBasic218Circle2Dlg::ShowGrid()
{
	m_image_dc.SelectObject(&m_grid_pen);

	// ������
	m_image_dc.MoveTo(m_center.x, 0);
	m_image_dc.LineTo(m_center.x, m_rect.bottom);

	// ����
	m_image_dc.MoveTo(0, m_center.y);
	m_image_dc.LineTo(m_rect.right, m_center.y);
}

void CMFCBasic218Circle2Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (nFlags & MK_LBUTTON) {
		// ������ ������� ����
		m_image_dc.FillSolidRect(m_rect, RGB(0, 0, 0));

		// �����ϰ�
		ShowGrid();
		m_image_dc.SelectObject(&m_green_pen);
		m_image_dc.SelectStockObject(NULL_BRUSH);
		m_image_dc.Ellipse(m_center.x - 200, m_center.y - 200, m_center.x + 200, m_center.y + 200);

		// ���׸���
		m_image_dc.SelectObject(&m_green_pen);
		m_image_dc.MoveTo(m_center);
		m_image_dc.LineTo(point);

		double radian = atan2(-(point.y - m_center.y), point.x - m_center.x);
		int end_x = (int)(cos(radian) * 200 + m_center.x);
		int end_y = (int)(sin(radian) * -200 + m_center.y);

		int start_x = (int)(cos(0) * 200 + m_center.x);
		int start_y = (int)(sin(0) * -200 + m_center.y);

		m_image_dc.SelectObject(&m_yellow_pen);
		m_image_dc.Ellipse(end_x - 10, end_y - 10, end_x + 10, end_y + 10);

		m_image_dc.SelectObject(&m_pie_brush);
		m_image_dc.Pie(m_center.x - 180, m_center.y - 180, m_center.x + 180, m_center.y + 180, start_x, start_y, end_x, end_y);

		int degree = (int)(radian * 180 / PI);
		if (degree < 0) degree = 360 + degree;

		CString str;
		str.Format(_T("���� %d��"), degree);
		m_image_dc.SetTextColor(RGB(255, 255, 255));
		m_image_dc.TextOut(point.x, point.y, str);

		::InvalidateRect(m_hWnd, NULL, FALSE);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
