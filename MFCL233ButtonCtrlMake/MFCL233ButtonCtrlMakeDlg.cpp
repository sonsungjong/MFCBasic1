
// MFCL233ButtonCtrlMakeDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL233ButtonCtrlMake.h"
#include "MFCL233ButtonCtrlMakeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL233ButtonCtrlMakeDlg dialog



CMFCL233ButtonCtrlMakeDlg::CMFCL233ButtonCtrlMakeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL233BUTTONCTRLMAKE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL233ButtonCtrlMakeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL233ButtonCtrlMakeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL233ButtonCtrlMakeDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL233ButtonCtrlMakeDlg::OnBnClickedCancel)
	ON_MESSAGE(LM_BTN_CLICKED, &CMFCL233ButtonCtrlMakeDlg::OnLmBtnClicked)
END_MESSAGE_MAP()


// CMFCL233ButtonCtrlMakeDlg message handlers

BOOL CMFCL233ButtonCtrlMakeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_test_btn1.CreateButton(this, _T("승인"), 1001, IDC_TEST_BTN_RECT);					// picture컨트롤을 사용해서 버튼생성 (1001번)
	m_test_btn2.CreateButton(this, _T("거부"), 1002, CRect(155, 11, 292, 40));				// 좌표를 줘서 버튼생성 (1002번)

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL233ButtonCtrlMakeDlg::OnPaint()
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
HCURSOR CMFCL233ButtonCtrlMakeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL233ButtonCtrlMakeDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL233ButtonCtrlMakeDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

// TipsButton에서 define한 값을 부모윈도우에서 메시지로 등록 (28001)
afx_msg LRESULT CMFCL233ButtonCtrlMakeDlg::OnLmBtnClicked(WPARAM wParam, LPARAM lParam)
{
	// wParam으로 비교
	if (wParam == 1001) {
		AfxMessageBox(_T("승인 되었습니다."));
	}
	else if (wParam == 1002) {
		AfxMessageBox(_T("거부 되었습니다."));
	}
	return 0;
}
