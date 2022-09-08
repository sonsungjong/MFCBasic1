
// MFCL204KeyboardMsgDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL204KeyboardMsg.h"
#include "MFCL204KeyboardMsgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL204KeyboardMsgDlg dialog



CMFCL204KeyboardMsgDlg::CMFCL204KeyboardMsgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL204KEYBOARDMSG_DIALOG, pParent), m_start_flag(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	// m_start_flag = 0;
}

void CMFCL204KeyboardMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL204KeyboardMsgDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL204KeyboardMsgDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL204KeyboardMsgDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_START_BTN, &CMFCL204KeyboardMsgDlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_STOP_BTN, &CMFCL204KeyboardMsgDlg::OnBnClickedStopBtn)
	
	ON_COMMAND(ID_EXIT_MENU, &CMFCL204KeyboardMsgDlg::OnExitMenu)
	ON_COMMAND(ID_START_MENU, &CMFCL204KeyboardMsgDlg::OnStartMenu)
	ON_COMMAND(ID_EDIT_CLEAR_CMD, &CMFCL204KeyboardMsgDlg::OnEditClearCmd)
END_MESSAGE_MAP()


// CMFCL204KeyboardMsgDlg message handlers

BOOL CMFCL204KeyboardMsgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_acc_key = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MY_ACC));

	OnBnClickedStopBtn();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL204KeyboardMsgDlg::OnPaint()
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
HCURSOR CMFCL204KeyboardMsgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL204KeyboardMsgDlg::OnBnClickedOk()
{
	//CDialogEx::OnOK();
}


void CMFCL204KeyboardMsgDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


void CMFCL204KeyboardMsgDlg::OnBnClickedStartBtn()
{
	// 버튼상태 플래그
	m_start_flag = 1;
	// edit에 글자넣기
	SetDlgItemText(IDC_STATE_EDIT, _T("시작했습니다."));

	// 버튼 리소스 주소 얻기
	CWnd* start_btn = GetDlgItem(IDC_START_BTN);
	CWnd* stop_btn = GetDlgItem(IDC_STOP_BTN);

	// 활성&비활성 처리
	start_btn->EnableWindow(FALSE);
	stop_btn->EnableWindow(TRUE);

	UpdateMenu();
}

void CMFCL204KeyboardMsgDlg::OnBnClickedStopBtn()
{
	// 버튼상태 플래그
	m_start_flag = 0;
	// edit에 글자넣기
	SetDlgItemText(IDC_STATE_EDIT, _T("중지했습니다."));

	// 버튼 리소스 주소 얻기
	CWnd* start_btn = GetDlgItem(IDC_START_BTN);
	CWnd* stop_btn = GetDlgItem(IDC_STOP_BTN);

	// 활성&비활성 처리
	start_btn->EnableWindow(TRUE);
	stop_btn->EnableWindow(FALSE);

	UpdateMenu();
}

void CMFCL204KeyboardMsgDlg::OnExitMenu()
{
	EndDialog(IDCLOSE);
}


void CMFCL204KeyboardMsgDlg::OnStartMenu()
{
	OnBnClickedStartBtn();
}

void CMFCL204KeyboardMsgDlg::UpdateMenu()
{
	CMenu* p_menu = GetMenu();				// 메뉴바 주소를 얻음
	if (p_menu != NULL)
	{
		CMenu* p_sub_menu = p_menu->GetSubMenu(0);				// 메뉴바 중 첫번째 메뉴의 주소 얻음
		if (p_sub_menu != NULL)
		{
			if (m_start_flag == 1)
			{
				p_sub_menu->EnableMenuItem(ID_START_MENU, MF_BYCOMMAND | MF_DISABLED);
				p_sub_menu->EnableMenuItem(IDC_STOP_BTN, MF_BYCOMMAND | MF_ENABLED);
			}
			else
			{
				p_sub_menu->EnableMenuItem(ID_START_MENU, MF_BYCOMMAND | MF_ENABLED);
				p_sub_menu->EnableMenuItem(IDC_STOP_BTN, MF_BYCOMMAND | MF_DISABLED);
			}
		}
	}
}

// TranslateMessage 함수 전에 실행되는 함수
BOOL CMFCL204KeyboardMsgDlg::PreTranslateMessage(MSG* pMsg)
{
	if (::TranslateAccelerator(m_hWnd, m_acc_key, pMsg))
	{
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

// Acc 리소스에서 핸들러 추가함
void CMFCL204KeyboardMsgDlg::OnEditClearCmd()
{
	SetDlgItemText(IDC_STATE_EDIT, _T(""));
}
// 이미 등록되어있는 리소스명과 acc리소스명이 같으면 등록 추가로 안해도 됨