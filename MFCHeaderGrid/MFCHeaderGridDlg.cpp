
// MFCHeaderGridDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCHeaderGrid.h"
#include "MFCHeaderGridDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCHeaderGridDlg dialog



CMFCHeaderGridDlg::CMFCHeaderGridDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCHEADERGRID_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCHeaderGridDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCHeaderGridDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCHeaderGridDlg message handlers

BOOL CMFCHeaderGridDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect r;
	GetDlgItem(IDC_GRID_RECT)->GetWindowRect(r);
	ScreenToClient(r);

	// 헤더그리드 컨트롤을 Picture Control 좌표위치에 생성
	m_header_grid.Create(NULL, NULL, WS_VISIBLE | WS_CHILD, r, this, 44000);
	m_header_grid.AddItemData(_T("아이디"), 100);
	m_header_grid.AddItemData(_T("이름"), 100);
	m_header_grid.AddItemData(_T("주소"), 200);
	m_header_grid.RedrawItemData();

	m_data_list.SubclassDlgItem(IDC_DATA_LIST, this);
	for (int i = 0; i < 10; i++) {m_data_list.InsertString(i, _T(""));}					// 임시로 10개 항목 넣음
	// 헤더 컨트롤과 리스트박스가 함께 동작하도록 핸들을 설정
	m_header_grid.SetBuddyWnd(m_data_list.m_hWnd);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCHeaderGridDlg::OnPaint()
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
HCURSOR CMFCHeaderGridDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCHeaderGridDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialogEx::OnOK();
}


void CMFCHeaderGridDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnCancel();
}


void CMFCHeaderGridDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	// 헤더컨트롤 윈도우 제거
	m_header_grid.DestroyWindow();
}
