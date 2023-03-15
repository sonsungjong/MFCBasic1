
// GridListCtrlDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "GridListCtrl.h"
#include "GridListCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGridListCtrlDlg dialog



CGridListCtrlDlg::CGridListCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRIDLISTCTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGridListCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
}

BEGIN_MESSAGE_MAP(CGridListCtrlDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CGridListCtrlDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGridListCtrlDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CGridListCtrlDlg message handlers

BOOL CGridListCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// manifest를 설정하면 헤더쪽이 이상해지고 다중선택이 안됨
	// 무슨 설정인지 모르겠음
	LVITEM item;
	::ZeroMemory(&item, sizeof(item));
	item.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
	item.pszText = _T("TEST ITEM");
	item.iItem = 5;
	item.iImage = 1;
	item.state = LVIS_SELECTED | LVIS_FOCUSED;

	// 격자 모양 추가 후 컬럼 추가
	m_list1.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);							// 격자 추가
	m_list1.InsertColumn(0, _T("No"), LVCFMT_LEFT, 40);
	m_list1.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 100);
	m_list1.InsertColumn(2, _T("Kor"), LVCFMT_LEFT, 60);
	m_list1.InsertColumn(3, _T("Eng"), LVCFMT_LEFT, 60);
	m_list1.InsertColumn(4, _T("Math"), LVCFMT_LEFT, 60);
	m_list1.InsertColumn(5, _T("Sum"), LVCFMT_CENTER, 100);
	m_list1.InsertColumn(6, _T("Avg"), LVCFMT_CENTER, 60);
	m_list1.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	// 항목 삽입
	CString strItem = _T("");
	for (int i = 1; i <= 30; i++) {
		strItem.Format(_T("%d"), i);
		m_list1.InsertItem(i, strItem, i);
	}

	for (int i = 0; i < 30; i++) {
		m_list1.SetItem(i, 1, LVIF_TEXT, _T("item"), NULL, NULL, NULL, NULL);
		m_list1.SetItem(i, 2, LVIF_TEXT, _T("33"), NULL, NULL, NULL, NULL);
		m_list1.SetItem(i, 3, LVIF_TEXT, _T("44"), NULL, NULL, NULL, NULL);
		m_list1.SetItem(i, 4, LVIF_TEXT, _T("55"), NULL, NULL, NULL, NULL);
		m_list1.SetItem(i, 5, LVIF_TEXT, _T("22"), NULL, NULL, NULL, NULL);
		m_list1.SetItem(i, 6, LVIF_TEXT, _T("10.1"), NULL, NULL, NULL, NULL);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGridListCtrlDlg::OnPaint()
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
HCURSOR CGridListCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGridListCtrlDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CGridListCtrlDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
