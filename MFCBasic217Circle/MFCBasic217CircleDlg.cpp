
// MFCBasic217CircleDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic217Circle.h"
#include "MFCBasic217CircleDlg.h"
#include "afxdialogex.h"
#include <cmath>

#define PI			3.141592

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic217CircleDlg dialog



CMFCBasic217CircleDlg::CMFCBasic217CircleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC217CIRCLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic217CircleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic217CircleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMFCBasic217CircleDlg message handlers

BOOL CMFCBasic217CircleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetClientRect(m_rect);				// Ŭ���̾�Ʈ ����ũ�� ����
	m_center = m_rect.CenterPoint();				// �簢���� �߽����� ����Ͽ� ����
	
	// �޸�DC ���
	m_image.Create(m_rect.Width(), m_rect.Height(), 32, 0);
	m_image_dc.Attach(m_image.GetDC());

	m_grid_pen.CreatePen(PS_DOT, 1, RGB(168, 168, 168));					// ȸ��
	m_green_pen.CreatePen(PS_SOLID, 2, RGB(140, 255, 140));				// ���� ���
	m_gray_pen.CreatePen(PS_SOLID, 2, RGB(225, 225, 225));					// ���� ȸ��

	m_green_brush.CreateSolidBrush(RGB(0, 200, 0));				// ��ο� ���
	m_gray_brush.CreateSolidBrush(RGB(120, 120, 120));				// ��ο� ȸ��

	SetBackgroundColor(RGB(0, 0, 0));			// ���� ���� : ����

	SetTimer(1, 10, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic217CircleDlg::OnPaint()
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
		m_image.Draw(dc, 0, 0);					// m_image�� ����� �׸��� �׸���

		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic217CircleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic217CircleDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	// Ÿ�̸� ����
	KillTimer(1);

	// �޸� DC����
	m_image_dc.Detach();
	m_image.ReleaseDC();

	// �� ����
	m_grid_pen.DeleteObject();
	m_green_pen.DeleteObject();
	m_green_brush.DeleteObject();
}

void CMFCBasic217CircleDlg::ShowGrid()
{
	m_image_dc.SelectObject(&m_grid_pen);

	// ������
	m_image_dc.MoveTo(m_center.x, 0);
	m_image_dc.LineTo(m_center.x, m_rect.bottom);

	// ����
	m_image_dc.MoveTo(0, m_center.y);
	m_image_dc.LineTo(m_rect.right, m_center.y);
}

void CMFCBasic217CircleDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1)
	{
		// �׸��� ���� ��ü�� ����
		m_image_dc.FillSolidRect(m_rect, RGB(0, 0, 0));
		ShowGrid();
		m_image_dc.SelectObject(&m_green_pen);
		if (m_grid_flag == 1) {
			m_image_dc.SelectStockObject(NULL_BRUSH);
			m_image_dc.Ellipse(m_center.x - 200, m_center.y - 200, m_center.x + 200, m_center.y + 200);
		}

		// ��ǥ����
		double radian = m_degree * PI / 180;
		int y = (int)(sin(radian) * -200);
		int x = (int)(cos(radian) * 200);

		// ��� ��ġ ����
		y += m_center.y;
		x += m_center.x;

		m_image_dc.SelectObject(&m_green_brush);
		m_image_dc.Ellipse(x - 30, y - 30, x + 30, y + 30);

		// �ð����
		radian = m_sub_degree * PI / 180;
		int sub_y = (int)(cos(radian) * -75);
		int sub_x = (int)(sin(radian) * 75);
		sub_y += y;
		sub_x += x;

		m_image_dc.SelectObject(&m_gray_pen);
		if (m_grid_flag == 1) {
			m_image_dc.SelectStockObject(NULL_BRUSH);
			m_image_dc.Ellipse(x-75, y-75, x+75, y+75);
		}

		m_image_dc.SelectObject(&m_gray_brush);
		m_image_dc.Ellipse(sub_x - 10, sub_y - 10, sub_x + 10, sub_y + 10);

		m_degree = (m_degree + 1) % 360;			// 0 ~ 359
		m_sub_degree = (m_sub_degree + 4) % 360;			// 0 ~ 359
		Invalidate(FALSE);					// ���׸������� ���游 �׸���
	}
	else CDialogEx::OnTimer(nIDEvent);
}


void CMFCBasic217CircleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_grid_flag = (m_grid_flag + 1) % 4;
	Invalidate(FALSE);

	CDialogEx::OnLButtonDown(nFlags, point);
}
