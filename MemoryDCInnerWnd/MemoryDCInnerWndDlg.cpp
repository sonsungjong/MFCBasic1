#include "pch.h"
#include "framework.h"
#include "MemoryDCInnerWnd.h"
#include "MemoryDCInnerWndDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMemoryDCInnerWndDlg::CMemoryDCInnerWndDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MEMORYDCINNERWND_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMemoryDCInnerWndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMemoryDCInnerWndDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMemoryDCInnerWndDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMemoryDCInnerWndDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMemoryDCInnerWndDlg message handlers

BOOL CMemoryDCInnerWndDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect r;
	//GetDlgItem(IDC_RECT_INNER1)->GetWindowRect(r);				// Picture컨트롤 사용시
	r.SetRect(0, 0, 300, 200);
	ScreenToClient(r);					// 대화상자 기준으로 좌표보정
	
	// 출력
	m_inner_wnd.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, r, this, 27001);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMemoryDCInnerWndDlg::OnPaint()
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
HCURSOR CMemoryDCInnerWndDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMemoryDCInnerWndDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMemoryDCInnerWndDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMemoryDCInnerWndDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	m_inner_wnd.DestroyWindow();
}
