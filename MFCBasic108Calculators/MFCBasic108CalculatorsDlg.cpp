
// MFCBasic108CalculatorsDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic108Calculators.h"
#include "MFCBasic108CalculatorsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic108CalculatorsDlg dialog



CMFCBasic108CalculatorsDlg::CMFCBasic108CalculatorsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC108CALCULATORS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic108CalculatorsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic108CalculatorsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCBasic108CalculatorsDlg::OnBnClickedOk)
	ON_COMMAND_RANGE(IDC_BUTTON0, IDC_BUTTON9, OnSetNumFunc)
	ON_COMMAND_RANGE(IDC_OP_SUM_BTN, IDC_OP_DIV_BTN, OnProcessOpFunc)
	ON_BN_CLICKED(IDC_CLEAR_BTN, &CMFCBasic108CalculatorsDlg::OnBnClickedClearBtn)
	ON_BN_CLICKED(IDC_OP_EQUAL_BTN, &CMFCBasic108CalculatorsDlg::OnBnClickedOpEqualBtn)
	ON_BN_CLICKED(IDC_BACK_BTN, &CMFCBasic108CalculatorsDlg::OnBnClickedBackBtn)
END_MESSAGE_MAP()


// CMFCBasic108CalculatorsDlg message handlers

BOOL CMFCBasic108CalculatorsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	// 특정 부분의 폰트 바꾸기
	m_font.CreatePointFont(512, L"굴림");
	GetDlgItem(IDC_SHOW_NUM_EDIT)->SetFont(&m_font);
	SetDlgItemInt(IDC_SHOW_NUM_EDIT, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic108CalculatorsDlg::OnPaint()
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
HCURSOR CMFCBasic108CalculatorsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic108CalculatorsDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}

void CMFCBasic108CalculatorsDlg::OnSetNumFunc(unsigned int a_ctrl_id) {

	unsigned int originNum = GetDlgItemInt(IDC_SHOW_NUM_EDIT);

	if (m_reset_flag == 0) {
		SetDlgItemInt(IDC_SHOW_NUM_EDIT, originNum*10 + a_ctrl_id - IDC_BUTTON0);
	}
	else if (m_reset_flag == 1) {
		m_reset_flag = 0;
		SetDlgItemInt(IDC_SHOW_NUM_EDIT, a_ctrl_id - IDC_BUTTON0);
	}
}

void CMFCBasic108CalculatorsDlg::OnBnClickedClearBtn()
{
	// TODO: Add your control notification handler code here
	SetDlgItemInt(IDC_SHOW_NUM_EDIT, 0);
}


void CMFCBasic108CalculatorsDlg::OnBnClickedOpEqualBtn()
{
	// TODO: Add your control notification handler code here
	int second_num = GetDlgItemInt(IDC_SHOW_NUM_EDIT);
	
	switch (m_op_flag)
	{
		case 1:		// 더하기
			m_remember_num += second_num;
			break;
		case 2:		// 빼기
			m_remember_num -= second_num;
			break;
		case 3:		// 곱하기
			m_remember_num *= second_num;
			break;
		case 4:		// 나누기
			if (second_num != 0) {
				m_remember_num /= second_num;
			}
			break;
	}
	SetDlgItemInt(IDC_SHOW_NUM_EDIT, m_remember_num);
	m_remember_num = 0;
	m_reset_flag = 1;
}

void CMFCBasic108CalculatorsDlg::OnProcessOpFunc(unsigned int a_ctrl_id)
{
	m_op_flag = a_ctrl_id - IDC_OP_SUM_BTN + 1;
	m_reset_flag = 1;
	m_remember_num = GetDlgItemInt(IDC_SHOW_NUM_EDIT);
}

void CMFCBasic108CalculatorsDlg::OnBnClickedBackBtn()
{
	// TODO: Add your control notification handler code here
	unsigned int originNum = GetDlgItemInt(IDC_SHOW_NUM_EDIT);

	SetDlgItemInt(IDC_SHOW_NUM_EDIT, originNum / 10);
}
