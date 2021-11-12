
// MFCBasic222CircleWindowDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic222CircleWindow.h"
#include "MFCBasic222CircleWindowDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic222CircleWindowDlg dialog



CMFCBasic222CircleWindowDlg::CMFCBasic222CircleWindowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC222CIRCLEWINDOW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic222CircleWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic222CircleWindowDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMFCBasic222CircleWindowDlg message handlers

BOOL CMFCBasic222CircleWindowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRgn rgn;
	rgn.CreateEllipticRgn(0, 0, 200, 200);
	SetWindowRgn(rgn, TRUE);

	SetBackgroundColor(RGB(0, 200, 255));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic222CircleWindowDlg::OnPaint()
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
HCURSOR CMFCBasic222CircleWindowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic222CircleWindowDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_clickFlag = 1;
	//m_prevPosition = point;					// Ŭ���� ���콺 ��ǥ�� ���
	GetCursorPos(&m_prevPosition);			// ȭ�� ��ü�� �������� ���� �� ���콺 Ŀ���� ��ġ�� ��ȯ
	SetCapture();									// ���콺�� ������ ���������� ��� �޽����� ���� �� �ִ� �Լ�

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCBasic222CircleWindowDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_clickFlag) {
		m_clickFlag = 0;
		ReleaseCapture();					//SetCapture() ����� ����
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCBasic222CircleWindowDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_clickFlag) {
		CRect rect;
		//GetClientRect(r);				// ���α׷� ����
		GetWindowRect(rect);				// ��ü������ ����

		CPoint position;
		GetCursorPos(&position);			// ��ǥ�� ��
		// MoveWindow()						// ���� ��ġ���� ������ġ�� ���� �̵��Ÿ��� ������
		SetWindowPos(NULL, rect.left + position.x - m_prevPosition.x, rect.top + position.y - m_prevPosition.y, 0,0,SWP_NOSIZE);			// �������� �ٲ㼭 �����찡 �̵��ϴ� ��ó�� ���̰��ϱ�
		m_prevPosition = position;					// ������ �������� ���������� ����
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
