
// MFCL206EditCtrl2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL206EditCtrl2.h"
#include "MFCL206EditCtrl2Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL206EditCtrl2Dlg dialog



CMFCL206EditCtrl2Dlg::CMFCL206EditCtrl2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL206EDITCTRL2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL206EditCtrl2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL206EditCtrl2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL206EditCtrl2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL206EditCtrl2Dlg::OnBnClickedCancel)


END_MESSAGE_MAP()


// CMFCL206EditCtrl2Dlg message handlers

BOOL CMFCL206EditCtrl2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// 컨트롤이 그려질때 특정 메시지를 날려주면 색상을 바꿀 수 있음 WM_CTLCOLOR
	

	for (int i = 0; i < 6; i++) {
		// 임시 텍스트
		SetDlgItemText(IDC_EDIT1+i, _T("안녕하세요 손성종 입니다^^"));

		// 상속받고 SubclassDlgItem으로 아이디와 연결만 해주면 됨
		m_my_edit[i].SubclassDlgItem(IDC_EDIT1 + i, this);				// 배열과 아이디를 연결 (중요)

		// 색상바꾸기 함수
		m_my_edit[1].ChangeColor(RGB(0, 255, 0), RGB(0, 0, 0), RGB(234, 234, 234));
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL206EditCtrl2Dlg::OnPaint()
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
HCURSOR CMFCL206EditCtrl2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL206EditCtrl2Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL206EditCtrl2Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
