
// MFCBasic227CSocketClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic227CSocketClient.h"
#include "MFCBasic227CSocketClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic227CSocketClientDlg dialog



CMFCBasic227CSocketClientDlg::CMFCBasic227CSocketClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC227CSOCKETCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CMFCBasic227CSocketClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
}

BEGIN_MESSAGE_MAP(CMFCBasic227CSocketClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCBasic227CSocketClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCBasic227CSocketClientDlg::OnBnClickedSendBtn)
END_MESSAGE_MAP()


// CMFCBasic227CSocketClientDlg message handlers

BOOL CMFCBasic227CSocketClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_client.Create();
	m_client.Connect(IP, PORT);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic227CSocketClientDlg::OnPaint()
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
HCURSOR CMFCBasic227CSocketClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic227CSocketClientDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCBasic227CSocketClientDlg::OnBnClickedSendBtn()
{
	CString str;
	GetDlgItemText(IDC_EDIT1, str);
	SetDlgItemText(IDC_EDIT1, _T(""));

	unsigned int data_size = ((unsigned int)str.GetLength() + 1U) * 2U;
	char* p_send_data = new char[sizeof(unsigned int) + data_size];					// 4byte헤더
	*(unsigned int*)p_send_data = data_size;													// 헤더에 문자열 길이넣기
	memcpy(p_send_data + sizeof(unsigned int), str.GetBuffer(), data_size);				// 4byte떨어진곳에 문자열 저장

	m_client.Send(p_send_data, sizeof(unsigned int) +data_size);				// 유니코드여서 문자길이의 2배 사이즈

	delete[] p_send_data;
}

void CMFCBasic227CSocketClientDlg::AddEventString(const TCHAR* ap_string)
{
	int index = m_list1.InsertString(-1, ap_string);
	m_list1.SetCurSel(index);
}