
// MFCBasic107CommandRangeDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic107CommandRange.h"
#include "MFCBasic107CommandRangeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic107CommandRangeDlg dialog



CMFCBasic107CommandRangeDlg::CMFCBasic107CommandRangeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC107COMMANDRANGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic107CommandRangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic107CommandRangeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND_RANGE(IDC_BUTTON1, IDC_BUTTON3, OnSetNumFunc)			// ���ҽ���ȣ���� ���� Ư���Լ��� ����
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCBasic107CommandRangeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCBasic107CommandRangeDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCBasic107CommandRangeDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFCBasic107CommandRangeDlg message handlers

BOOL CMFCBasic107CommandRangeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic107CommandRangeDlg::OnPaint()
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
HCURSOR CMFCBasic107CommandRangeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCBasic107CommandRangeDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	//SetDlgItemInt(IDC_SHOW_NUM_EDIT, 1);
}

void CMFCBasic107CommandRangeDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	//SetDlgItemInt(IDC_SHOW_NUM_EDIT, 2);
}

void CMFCBasic107CommandRangeDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	//SetDlgItemInt(IDC_SHOW_NUM_EDIT, 3);
}


LRESULT CMFCBasic107CommandRangeDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	/*
	if (WM_COMMAND == message) {
		// ���� 16��Ʈ �Լ�
		unsigned int ctrl_id = LOWORD(wParam);
		if (ctrl_id >= IDC_BUTTON1 && ctrl_id <= IDC_BUTTON3) {
			// Resource.h ���� ��ư�� ID�� �ٲ�
			SetDlgItemInt(IDC_SHOW_NUM_EDIT, ctrl_id - IDC_BUTTON1 +1);
		}
	}
	*/

	return CDialogEx::WindowProc(message, wParam, lParam);
}

// WindowProc�� WM_COMMAND�� ó���ϴ� �����Լ�
BOOL CMFCBasic107CommandRangeDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: WM_COMMAND
	/*
	unsigned int ctrl_id = LOWORD(wParam);
	if (ctrl_id >= IDC_BUTTON1 && ctrl_id <= IDC_BUTTON3) {
		// Resource.h ���� ��ư�� ID�� �ٲ���
		SetDlgItemInt(IDC_SHOW_NUM_EDIT, ctrl_id - IDC_BUTTON1 + 1);
	}
	*/
	return CDialogEx::OnCommand(wParam, lParam);
}

void CMFCBasic107CommandRangeDlg::OnSetNumFunc(unsigned int a_ctrl_id) {
	SetDlgItemInt(IDC_SHOW_NUM_EDIT, a_ctrl_id - 44000);
}

// Button �����Լ�
// WindowProc �����Լ�
// OnCommand �����Լ�
// On_Command_Range ��ũ���Լ�