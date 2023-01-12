
// ChildDlgDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ChildDlg.h"
#include "ChildDlgDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CChildDlgDlg dialog



CChildDlgDlg::CChildDlgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHILDDLG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CChildDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChildDlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CChildDlgDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CChildDlgDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_MESSAGE(27000, &CChildDlgDlg::On27000)
	ON_MESSAGE(27001, &CChildDlgDlg::On27001)
	ON_MESSAGE(33001, &CChildDlgDlg::On33001)
	ON_MESSAGE(33002, &CChildDlgDlg::On33002)
	ON_MESSAGE(33003, &CChildDlgDlg::On33003)
	ON_BN_CLICKED(IDC_OPEN_NEW_DLG, &CChildDlgDlg::OnBnClickedOpenNewDlg)
	ON_BN_CLICKED(IDC_BROAD_BTN, &CChildDlgDlg::OnBnClickedBroadBtn)
END_MESSAGE_MAP()


// CChildDlgDlg message handlers

BOOL CChildDlgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetWindowPos(NULL, 0, 0, 800, 600, SWP_NOMOVE);

	// 비정형 대화상자 동적할당
	m_child_tap = new NewChild;
	m_child_tap->Create(IDD_NEW_CHILD, this);
	m_child_tap->SetWindowPos(NULL, 0, 0, 500, 200, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChildDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChildDlgDlg::OnPaint()
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
HCURSOR CChildDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChildDlgDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CChildDlgDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CChildDlgDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	if (m_popup_dlg != NULL) {
		// 팝업창 닫는 메시지
		On27000(0, 0);
	}

	if (m_child_tap != NULL) {
		// Inner 닫기
		m_child_tap->DestroyWindow();
		delete m_child_tap;
		m_child_tap = NULL;
	}
}


afx_msg LRESULT CChildDlgDlg::On27000(WPARAM wParam, LPARAM lParam)
{
	DestroyPopup();

	return 0;
}

// PostMessage로 전달받아 값을 조작하여 사용
afx_msg LRESULT CChildDlgDlg::On27001(WPARAM wParam, LPARAM lParam)
{
	int num = (int)wParam;
	if (num < 0) { num = num * (-1); }

	CString str = ((CString*)lParam)->GetString();

	CString cat;
	cat.Format(_T("%d"), num);
	str += cat;

	SetDlgItemText(IDC_MAIN_EDIT1, str);

	return 0;
}


afx_msg LRESULT CChildDlgDlg::On33001(WPARAM wParam, LPARAM lParam)
{
	m_tap_status = 0;
	DrawBack();

	return 0;
}


afx_msg LRESULT CChildDlgDlg::On33002(WPARAM wParam, LPARAM lParam)
{
	m_tap_status = 1;
	DrawBack();

	return 0;
}


afx_msg LRESULT CChildDlgDlg::On33003(WPARAM wParam, LPARAM lParam)
{
	m_tap_status = 2;
	DrawBack();

	return 0;
}

// 비정형 대화상자 동적할당
void CChildDlgDlg::OnBnClickedOpenNewDlg()
{
	if (m_popup_dlg == NULL) {
		m_popup_dlg = new NewDlg;
		m_popup_dlg->Create(IDD_NEW_DLG, NULL);
	}
}


void CChildDlgDlg::OnBnClickedBroadBtn()
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_MAIN_EDIT1, str);

	// TODO: Add your control notification handler code here
	if (m_child_tap != NULL) {
		m_child_tap->SetDlgItemText(IDC_CHILD_EDIT1, str);
	}

	if (m_popup_dlg != NULL) {
		m_popup_dlg->SetDlgItemText(IDC_POPUP_EDIT1, str);
	}
}

void CChildDlgDlg::DestroyPopup()
{
	m_popup_dlg->DestroyWindow();
	delete m_popup_dlg;
	m_popup_dlg = NULL;
}

void CChildDlgDlg::DrawBack()
{
	// 탭 상태에 따라서 다르게 그림
	if (m_tap_status == 0) {
		if (m_popup_dlg != NULL) {
			m_popup_dlg->PostMessage(33001);
		}
	}
	else if (m_tap_status == 1) {
		if (m_popup_dlg != NULL) {
			m_popup_dlg->PostMessage(33002);
		}
	}
	else if (m_tap_status == 2) {
		if (m_popup_dlg != NULL) {
			m_popup_dlg->PostMessage(33003);
		}
	}
	else {
		/* no actions */
	}
	Invalidate();
}