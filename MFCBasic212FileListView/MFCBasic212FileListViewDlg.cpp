
// MFCBasic212FileListViewDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic212FileListView.h"
#include "MFCBasic212FileListViewDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic212FileListViewDlg dialog



CMFCBasic212FileListViewDlg::CMFCBasic212FileListViewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC212FILELISTVIEW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic212FileListViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_LIST2, m_list2);
}

BEGIN_MESSAGE_MAP(CMFCBasic212FileListViewDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMFCBasic212FileListViewDlg message handlers

BOOL CMFCBasic212FileListViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_list1.Dir(DDL_ARCHIVE | DDL_HIDDEN | DDL_DIRECTORY, _T("C:\\*.*"));						// 파일 | 숨겨진파일 | 폴더

	TCHAR* name;
	TCHAR name2[256];
	WIN32_FIND_DATA file_data;				// 현재 탐색한 파일의 정보를 저장하는 구조체
	HANDLE h_item_list = FindFirstFile(_T("C:\\*.*"), &file_data);
	if (h_item_list != INVALID_HANDLE_VALUE) {					// 해당 파일이 있으면
		do {
			// "." 디렉토리 제외
			if (!(file_data.cFileName[0] == '.' && file_data.cFileName[1] == 0)) {					// memcmp(file_data.cFileName, _T("."), 4); 메모리컴페어
				name = file_data.cFileName;
				if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					_stprintf(name2, _T("%s%s%s"), _T("["), file_data.cFileName, _T("]"));
				}
				m_list2.InsertString(-1, name2);
			}
		} while (FindNextFile(h_item_list, &file_data));

		FindClose(h_item_list);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic212FileListViewDlg::OnPaint()
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
HCURSOR CMFCBasic212FileListViewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

