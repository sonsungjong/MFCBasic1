
// MFCL232BinaryViewerUpDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL232BinaryViewerUp.h"
#include "MFCL232BinaryViewerUpDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL232BinaryViewerUpDlg dialog



CMFCL232BinaryViewerUpDlg::CMFCL232BinaryViewerUpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL232BINARYVIEWERUP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL232BinaryViewerUpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL232BinaryViewerUpDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL232BinaryViewerUpDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL232BinaryViewerUpDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SELECT_BTN, &CMFCL232BinaryViewerUpDlg::OnBnClickedSelectBtn)
END_MESSAGE_MAP()


// CMFCL232BinaryViewerUpDlg message handlers

BOOL CMFCL232BinaryViewerUpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect r;
	GetDlgItem(IDC_VIEW_RECT)->GetWindowRect(r);
	ScreenToClient(r);

	m_bin_data_view.CreateEx(WS_EX_STATICEDGE, NULL, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL, r, this, 2005);				// 컨트롤ID 2005

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL232BinaryViewerUpDlg::OnPaint()
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
HCURSOR CMFCL232BinaryViewerUpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL232BinaryViewerUpDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL232BinaryViewerUpDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCL232BinaryViewerUpDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	m_bin_data_view.DestroyWindow();
}

// 파일 선택
void CMFCL232BinaryViewerUpDlg::OnBnClickedSelectBtn()
{
	// 파일 선택 목록 만들기
	TCHAR name_filter[] = _T("모든 파일 (*.*)|*.*|Raw 파일 (*.raw)|*.raw|Data파일 (*.dat)|*.dat|BMP 파일 (*.bmp)|*.bmp|실행 파일 (*.exe)|*.exe||");
	CFileDialog ins_dlg(TRUE, _T("*"), _T("*.*"), OFN_HIDEREADONLY | OFN_NOCHANGEDIR, name_filter);
	ins_dlg.m_ofn.nFilterIndex = 1;

	INT_PTR modal_btn = ins_dlg.DoModal();				// 모달 띄우기
	if (modal_btn == IDOK)					// 모달에서 OK 버튼을 누르면
	{
		SetDlgItemText(IDC_PATH_STATIC, ins_dlg.GetPathName());
		m_bin_data_view.LoadFile(ins_dlg.GetPathName());
	}
}

// 마우스 스크롤로 수직스크롤 조정할 수 있게하기 추가필요
// 키보드 위아래 키로 수직스크롤 조정할 수 있게하기 추가필요