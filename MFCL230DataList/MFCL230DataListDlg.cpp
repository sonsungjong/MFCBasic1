
// MFCL230DataListDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL230DataList.h"
#include "MFCL230DataListDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL230DataListDlg dialog



CMFCL230DataListDlg::CMFCL230DataListDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL230DATALIST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL230DataListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATE_CHECK, m_state_check);
}

BEGIN_MESSAGE_MAP(CMFCL230DataListDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL230DataListDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL230DataListDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_START_BTN, &CMFCL230DataListDlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_STOP_BTN, &CMFCL230DataListDlg::OnBnClickedStopBtn)
	ON_BN_CLICKED(IDC_STATE_CHECK, &CMFCL230DataListDlg::OnBnClickedStateCheck)
END_MESSAGE_MAP()


// CMFCL230DataListDlg message handlers

BOOL CMFCL230DataListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect r;
	GetDlgItem(IDC_LIST_RECT)->GetWindowRect(r);
	ScreenToClient(r);

	m_data_list.CreateEx(WS_EX_STATICEDGE, NULL, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL, r, this, 40044);

	SetDlgItemInt(IDC_UPDATE_TIME_EDIT, 100);				// 초기값 100
	srand((unsigned int)time(NULL));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL230DataListDlg::OnPaint()
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
HCURSOR CMFCL230DataListDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL230DataListDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL230DataListDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCL230DataListDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);
	m_data_list.DestroyWindow();
}


void CMFCL230DataListDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		int data[MAX_VALUE_COUNT];
		for (int i = 0; i < MAX_GROUP_COUNT; i++) 
		{
			for (int sub_i = 0; sub_i < MAX_VALUE_COUNT; sub_i++)
			{
				data[sub_i] = rand() % 1000;					// 0 ~ 999
			}
			m_data_list.UpdateData(i, data);
		}
		m_data_list.Redraw();
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}

}


void CMFCL230DataListDlg::OnBnClickedStartBtn()
{
	// TODO: Add your control notification handler code here
	SetTimer(1, GetDlgItemInt(IDC_UPDATE_TIME_EDIT), NULL);

}


void CMFCL230DataListDlg::OnBnClickedStopBtn()
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
}


void CMFCL230DataListDlg::OnBnClickedStateCheck()
{
	// TODO: Add your control notification handler code here
	m_data_list.SetStateCheck(m_state_check.GetCheck());				// 체크박스 체크되면 1, 체크안되있으면 0 반환
}

