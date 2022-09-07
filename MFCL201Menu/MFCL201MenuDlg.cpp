
// MFCL201MenuDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL201Menu.h"
#include "MFCL201MenuDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL201MenuDlg dialog



CMFCL201MenuDlg::CMFCL201MenuDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL201MENU_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL201MenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL201MenuDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL201MenuDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL201MenuDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_START_BTN, &CMFCL201MenuDlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_STOP_BTN, &CMFCL201MenuDlg::OnBnClickedStopBtn)
	ON_COMMAND(ID_START_CMD, &CMFCL201MenuDlg::OnStartCmd)
	ON_COMMAND(ID_EXIT_CMD, &CMFCL201MenuDlg::OnExitCmd)
END_MESSAGE_MAP()


// CMFCL201MenuDlg message handlers

BOOL CMFCL201MenuDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	OnBnClickedStopBtn();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL201MenuDlg::OnPaint()
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
HCURSOR CMFCL201MenuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL201MenuDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL201MenuDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CMFCL201MenuDlg::OnBnClickedStartBtn()
{
	m_start_flag = 1;
	SetDlgItemText(IDC_STATE_EDIT, _T("시작했습니다."));
	// 다이얼로그 내의 컨트롤 아이디를 얻어옴
	CWnd* start_btn = GetDlgItem(IDC_START_BTN);
	CWnd* stop_btn = GetDlgItem(IDC_STOP_BTN);

	// 버튼 활성&비활성화
	start_btn->EnableWindow(FALSE);
	stop_btn->EnableWindow(TRUE);

	// 메뉴 활성&비활성화 함수
	UpdateMenu();
}


void CMFCL201MenuDlg::OnBnClickedStopBtn()
{
	m_start_flag = 0;
	SetDlgItemText(IDC_STATE_EDIT, _T("중지했습니다."));

	// 컨트롤의 아이디(주소)를 얻어옴
	CWnd* start_btn = GetDlgItem(IDC_START_BTN);
	CWnd* stop_btn = GetDlgItem(IDC_STOP_BTN);

	// 버튼 활성&비활성화
	start_btn->EnableWindow(TRUE);
	stop_btn->EnableWindow(FALSE);

	// 메뉴 활성&비활성화 함수
	UpdateMenu();
}

// 메뉴의 이벤트 핸들러 추가 (컨트롤과 아이디가 같아도 됨)
void CMFCL201MenuDlg::OnStartCmd()
{
	OnBnClickedStartBtn();
}


void CMFCL201MenuDlg::OnExitCmd()
{
	EndDialog(IDCANCEL);
}

void CMFCL201MenuDlg::UpdateMenu()
{
	CMenu* p_menu = GetMenu();
	if (p_menu != NULL) {
		CMenu* p_sub_menu = p_menu->GetSubMenu(0);
		if (p_sub_menu != NULL) {
			if (m_start_flag == 1) {
				p_sub_menu->EnableMenuItem(ID_START_CMD, MF_BYCOMMAND | MF_DISABLED);
				p_sub_menu->EnableMenuItem(IDC_STOP_BTN, MF_BYCOMMAND | MF_ENABLED);
			}
			else {
				p_sub_menu->EnableMenuItem(ID_START_CMD, MF_BYCOMMAND | MF_ENABLED);
				p_sub_menu->EnableMenuItem(IDC_STOP_BTN, MF_BYCOMMAND | MF_DISABLED);
			}
		}
	}
}