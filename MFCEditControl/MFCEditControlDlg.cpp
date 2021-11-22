
// MFCEditControlDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCEditControl.h"
#include "MFCEditControlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCEditControlDlg dialog



CMFCEditControlDlg::CMFCEditControlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCEDITCONTROL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCEditControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
}

BEGIN_MESSAGE_MAP(CMFCEditControlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCEditControlDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCEditControlDlg::OnEnChangeEdit1)
	ON_EN_SETFOCUS(IDC_EDIT1, &CMFCEditControlDlg::OnEnSetfocusEdit1)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CMFCEditControlDlg::OnEnKillfocusEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCEditControlDlg::OnEnChangeEdit2)
	ON_EN_SETFOCUS(IDC_EDIT2, &CMFCEditControlDlg::OnEnSetfocusEdit2)
	ON_EN_KILLFOCUS(IDC_EDIT2, &CMFCEditControlDlg::OnEnKillfocusEdit2)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCEditControlDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCEditControlDlg message handlers

BOOL CMFCEditControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_edit1.SetLimitText(19);
	m_edit1.SetWindowText(_T("YYYY-MM-DD hh:mm:ss"));

	m_edit2.SetLimitText(8);
	m_edit2.SetWindowText(_T("00:00:00"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCEditControlDlg::OnPaint()
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
HCURSOR CMFCEditControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCEditControlDlg::OnEnChangeEdit1()
{
	switch (m_edit1.GetWindowTextLength()) {
	case 4:
		m_edit1.SetSel(4, 4);
		m_edit1.ReplaceSel(_T("-"));
		break;
	case 7:
		m_edit1.SetSel(7, 7);
		m_edit1.ReplaceSel(_T("-"));
		break;
	case 10:
		m_edit1.SetSel(10, 10);
		m_edit1.ReplaceSel(_T(" "));
		break;
	case 13:
		m_edit1.SetSel(13, 13);
		m_edit1.ReplaceSel(_T(":"));
		break;
	case 16:
		m_edit1.SetSel(16, 16);
		m_edit1.ReplaceSel(_T(":"));
		break;
	}
}

void CMFCEditControlDlg::OnEnSetfocusEdit1()
{
	m_edit1.GetWindowText(m_getEdit1);
	if (m_getEdit1 == _T("YYYY-MM-DD hh:mm:ss")) {
		m_edit1.SetWindowText(_T(""));
	}
}

void CMFCEditControlDlg::OnEnKillfocusEdit1()
{
	m_edit1.GetWindowText(m_getEdit1);
	if (m_getEdit1 == _T("")) {
		m_edit1.SetWindowText(_T("YYYY-MM-DD hh:mm:ss"));
	}
}

void CMFCEditControlDlg::OnEnChangeEdit2()
{
	switch (m_edit2.GetWindowTextLength()) {
	case 2:
		m_edit2.SetSel(2, 2);
		m_edit2.ReplaceSel(_T(":"));
		break;
	case 5:
		m_edit2.SetSel(5, 5);
		m_edit2.ReplaceSel(_T(":"));
		break;
	}
}

void CMFCEditControlDlg::OnEnSetfocusEdit2()
{
	m_edit2.GetWindowText(m_getEdit2);
	if (m_getEdit2 == _T("00:00:00")) {
		m_edit2.SetWindowText(_T(""));
	}
}

void CMFCEditControlDlg::OnEnKillfocusEdit2()
{
	m_edit2.GetWindowText(m_getEdit2);
	if (m_getEdit2 == _T("")) {
		m_edit2.SetWindowText(_T("00:00:00"));
	}
}

void CMFCEditControlDlg::OnBnClickedButton1()
{
	char flag = 0;
	CString checkStr[19];
	int checkInt[19];
	m_edit1.GetWindowText(m_getEdit1);

	// 문자 길이와 특수문자 체크
	if (!(m_edit1.GetWindowTextLength() == 19 && m_getEdit1.Mid(4, 1) == _T("-") &&
		m_getEdit1.Mid(7, 1) == _T("-") && m_getEdit1.Mid(10, 1) == _T(" ") &&
		m_getEdit1.Mid(13, 1) == _T(":") && m_getEdit1.Mid(16, 1) == _T(":")))
	{
		::MessageBox(m_hWnd, _T("YYYY-MM-DD hh:mm:ss"), _T("형식 오류"), NULL);
		return;
	}
	flag = 1;

	// 정수변환이 가능한지 한번더 체크
	for (int i = 0; i < 19; i++) {
		checkStr[i] = m_getEdit1.Mid(i, 1);
		checkInt[i] = _ttoi(checkStr[i]);
		if (i != 4 && i != 7 && i != 10 && i != 13 && i != 16 &&
			checkStr[i] != "0" && checkInt[i] == 0) {
			flag = 0;
			break;
		}
	}

	if (flag) {
		m_edit1.GetWindowText(m_getEdit1);
		::MessageBox(m_hWnd, m_getEdit1, _T("형식 맞음"), NULL);
	}
	else {
		::MessageBox(m_hWnd, _T("YYYY-MM-DD hh:mm:ss"), _T("숫자입력 오류"), NULL);
	}
}

void CMFCEditControlDlg::OnBnClickedButton2()
{
	char flag = 0;
	int checkInt[8];
	CString checkStr[8];
	m_edit2.GetWindowText(m_getEdit2);

	// 문자 길이와 특수문자 체크
	if (!(m_edit2.GetWindowTextLength() == 8 && m_getEdit2.Mid(2, 1) == _T(":") && m_getEdit2.Mid(5,1) == _T(":")))
	{
		::MessageBox(m_hWnd, _T("00:00:00"), _T("형식 오류"), NULL);
		return;
	}
	flag = 1;

	// 정수인지 체크
	for (int i = 0; i < 8; i++) {
		checkStr[i] = m_getEdit2.Mid(i, 1);
		checkInt[i] = _ttoi(checkStr[i]);
		if (i != 2 && i != 5 && checkStr[i] != "0" && checkInt[i] == 0) {
			flag = 0;
			break;
		}
	}

	if (flag) {
		m_edit2.GetWindowText(m_getEdit2);
		::MessageBox(m_hWnd, m_getEdit2, _T("형식 맞음"), NULL);
	}
	else {
		::MessageBox(m_hWnd, _T("00:00:00"), _T("숫자입력 오류"), NULL);
	}
}
