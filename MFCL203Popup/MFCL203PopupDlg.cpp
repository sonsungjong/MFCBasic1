
// MFCL203PopupDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL203Popup.h"
#include "MFCL203PopupDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL203PopupDlg dialog



CMFCL203PopupDlg::CMFCL203PopupDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL203POPUP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL203PopupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL203PopupDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL203PopupDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL203PopupDlg::OnBnClickedCancel)
	ON_WM_RBUTTONUP()
	ON_COMMAND(20005, &CMFCL203PopupDlg::OnMyCommand)			// 커맨드 20005번 추가
END_MESSAGE_MAP()


// CMFCL203PopupDlg message handlers

BOOL CMFCL203PopupDlg::OnInitDialog()
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

void CMFCL203PopupDlg::OnPaint()
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
HCURSOR CMFCL203PopupDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL203PopupDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL203PopupDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCL203PopupDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CMenu menu;
	menu.CreatePopupMenu();
	
	CString str;
	for (size_t i = 0; i < 6; i++) {
		str.Format(_T("%lld번 메뉴 항목"), i);
		menu.AppendMenu(MF_STRING, static_cast<UINT_PTR>(20000) + i, str);
	}

	CPoint pos;
	GetCursorPos(&pos);

	menu.TrackPopupMenu(TPM_LEFTALIGN, pos.x, pos.y, this);
	menu.DestroyMenu();

	CDialogEx::OnRButtonUp(nFlags, point);
}


BOOL CMFCL203PopupDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	int cmd_id = LOWORD(wParam);
	if (cmd_id == 20000)
	{
		CString str;
		str.Format(_T("%d 항목을 선택했습니다."), cmd_id - 20000);
		::MessageBox(m_hWnd, str, _T("제목1"), MB_OK|MB_ICONWARNING);
		return 1;
	}
	else if (cmd_id == 20001)
	{
		CString str;
		str.Format(_T("%d 항목을 선택했습니다."), cmd_id - 20000);
		::MessageBox(m_hWnd, str, _T("제목2"), MB_OK | MB_ICONWARNING);
		return 1;
	}
	else if (cmd_id == 20002)
	{
		CString str;
		str.Format(_T("%d 항목을 선택했습니다."), cmd_id - 20000);
		::MessageBox(m_hWnd, str, _T("제목3"), MB_OK | MB_ICONWARNING);
		return 1;
	}
	else if (cmd_id == 20003)
	{
		CString str;
		str.Format(_T("%d 항목을 선택했습니다."), cmd_id - 20000);
		::MessageBox(m_hWnd, str, _T("제목4"), MB_OK | MB_ICONWARNING);
		return 1;
	}
	else if (cmd_id == 20004)
	{
		CString str;
		str.Format(_T("%d 항목을 선택했습니다."), cmd_id - 20000);
		::MessageBox(m_hWnd, str, _T("제목5"), MB_OK | MB_ICONWARNING);
		return 1;
	}

	return CDialogEx::OnCommand(wParam, lParam);
}

void CMFCL203PopupDlg::OnMyCommand()
{
	AfxMessageBox(_T("다섯번째 선택"));
}