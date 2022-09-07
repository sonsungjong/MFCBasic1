
// MFCL202PopupMenuDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL202PopupMenu.h"
#include "MFCL202PopupMenuDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL202PopupMenuDlg dialog



CMFCL202PopupMenuDlg::CMFCL202PopupMenuDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL202POPUPMENU_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL202PopupMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL202PopupMenuDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL202PopupMenuDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL202PopupMenuDlg::OnBnClickedCancel)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MY_OPEN, &CMFCL202PopupMenuDlg::OnMyOpen)
	ON_COMMAND(ID_MY_CLOSE, &CMFCL202PopupMenuDlg::OnMyClose)
END_MESSAGE_MAP()


// CMFCL202PopupMenuDlg message handlers

BOOL CMFCL202PopupMenuDlg::OnInitDialog()
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

void CMFCL202PopupMenuDlg::OnPaint()
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
HCURSOR CMFCL202PopupMenuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL202PopupMenuDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL202PopupMenuDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCL202PopupMenuDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_MY_MENU);
	CMenu* p_sub_menu = menu.GetSubMenu(0);

	// 현재 마우스 위치
	CPoint pos;
	GetCursorPos(&pos);

	// 팝업생성
	p_sub_menu->TrackPopupMenu(TPM_LEFTALIGN, pos.x, pos.y, this);
	menu.DestroyMenu();

	CDialogEx::OnRButtonDown(nFlags, point);
}


void CMFCL202PopupMenuDlg::OnMyOpen()
{
	// 선택시 원하는 기능 작동1
	::MessageBox(m_hWnd, _T("열기가 선택되었습니다."), _T("열기"), MB_OK | MB_ICONWARNING);
}


void CMFCL202PopupMenuDlg::OnMyClose()
{
	// 선택시 원하는 기능 작동2
	::MessageBox(m_hWnd, _T("닫기가 선택되었습니다."), _T("닫기"), MB_OK | MB_ICONWARNING);
}
