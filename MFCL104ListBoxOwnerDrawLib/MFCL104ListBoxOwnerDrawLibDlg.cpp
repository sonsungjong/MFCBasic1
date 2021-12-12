
// MFCL104ListBoxOwnerDrawLibDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL104ListBoxOwnerDrawLib.h"
#include "MFCL104ListBoxOwnerDrawLibDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(lib, "SJ_ListBoxD.lib")
#else
#pragma comment(lib, "SJ_ListBox.lib")
#endif

#define MAX_TITLE_LINE 32

// CMFCL104ListBoxOwnerDrawLibDlg dialog



CMFCL104ListBoxOwnerDrawLibDlg::CMFCL104ListBoxOwnerDrawLibDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL104LISTBOXOWNERDRAWLIB_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL104ListBoxOwnerDrawLibDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_DATA_LIST, m_data_list);
}

BEGIN_MESSAGE_MAP(CMFCL104ListBoxOwnerDrawLibDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL104ListBoxOwnerDrawLibDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMFCL104ListBoxOwnerDrawLibDlg message handlers

BOOL CMFCL104ListBoxOwnerDrawLibDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_data_list.SubclassDlgItem(IDC_DATA_LIST, this);				// 내가 만든 클래스와 컨트롤을 연결
	TCHAR* str = new TCHAR[MAX_TITLE_LINE];
	for (int i = 0; i < 10; i++)
	{
		//int len = MAX_TITLE_LINE;						// 32
		_stprintf_s(str, 9, _T("item - %d"), i);			// 내부에서 유니코드 메모리사이즈 처리
		m_data_list.InsertString(i, str);
	}
	m_data_list.SetItemHeight(0, 22);					// 각 셸의 높이를 22
	delete[] str;
	return TRUE;
}

void CMFCL104ListBoxOwnerDrawLibDlg::OnPaint()
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

HCURSOR CMFCL104ListBoxOwnerDrawLibDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCL104ListBoxOwnerDrawLibDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}

// 27:22