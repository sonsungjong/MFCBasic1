
// MFCL209DragDropDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL209DragDrop.h"
#include "MFCL209DragDropDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL209DragDropDlg dialog



CMFCL209DragDropDlg::CMFCL209DragDropDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL209DRAGDROP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL209DragDropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL209DragDropDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL209DragDropDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL209DragDropDlg::OnBnClickedCancel)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_HIDE_PATH_CHECK, &CMFCL209DragDropDlg::OnBnClickedHidePathCheck)
END_MESSAGE_MAP()


// CMFCL209DragDropDlg message handlers

BOOL CMFCL209DragDropDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_drop_list.SubclassDlgItem(IDC_DROP_LIST, this);							// this : 이 대화상자

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL209DragDropDlg::OnPaint()
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
HCURSOR CMFCL209DragDropDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL209DragDropDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL209DragDropDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

/*
	대화상자 속성에서 Accept File을 True로 하면 드래그&드랍이 가능해진다.

*/

void CMFCL209DragDropDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: Add your message handler code here and/or call default
	m_drop_list.ResetContent();

	TCHAR temp_path[MAX_PATH];
	int count = DragQueryFile(hDropInfo, -1, NULL, 0);
	if (count > 0) {
		int len = DragQueryFile(hDropInfo, 0, temp_path, MAX_PATH);
		if (len > 3) {
			TCHAR* p = temp_path + len;
			while (*p != '\\') {
				p--;
				*(p + 1) = 0;
				SetDlgItemText(IDC_BASE_PATH_EDIT, temp_path);
				m_drop_list.SetBasePath(temp_path, p - temp_path +1);
			}
		}
	}
	
	for (int i = 0; i < count; i++) {
		DragQueryFile(hDropInfo, i, temp_path, MAX_PATH);
		m_drop_list.InsertString(i, temp_path);
		
		// 해당 경로가 디렉토리인지 파일인지 반환
		if (GetFileAttributes(temp_path) & FILE_ATTRIBUTE_DIRECTORY)
		{
			// 디렉토리
			m_drop_list.SetItemData(i, 1);									// 폴더면 1 저장
		}
		else
		{
			// 파일
			m_drop_list.SetItemData(i, 0);									// 파일이면 0 저장
		}
	}

	MakeFileList();

	CDialogEx::OnDropFiles(hDropInfo);
}

void CMFCL209DragDropDlg::MakeFileList()
{
	int is_continue;
	int count;
	int i;

	TCHAR temp_path[MAX_PATH];
	do {
		is_continue = 0;
		count = m_drop_list.GetCount();
		for (i = 0; i < count; i++)
		{
			// 항목에 추가된 값이 1이면 디렉토리이고 검색이 필요하다는 뜻
			if (m_drop_list.GetItemData(i) == 1)
			{
				m_drop_list.SetItemData(i, 2);
				m_drop_list.GetText(i, temp_path);
				GetFilesInDirectory(temp_path, i + 1);
				is_continue = 1;
				break;
			}
		}
	} while (is_continue);
}

void CMFCL209DragDropDlg::GetFilesInDirectory(TCHAR* ap_path, int a_insert_index)
{
	//CString path, file_path;
	TCHAR path[MAX_PATH];
	TCHAR file_path[MAX_PATH];
	WIN32_FIND_DATA file_data;

	// 현재 디렉토리에 있는 모든 파일을 읽음
	//path.Format(_T("%s\\*.*"), ap_path);
	_stprintf_s(path, MAX_PATH, _T("%s\\*.*"), ap_path);
	HANDLE h_item_list = FindFirstFile(path, &file_data);
	if (INVALID_HANDLE_VALUE != h_item_list)
	{
		do {
			// ".", ".." 디렉토리 제외
			if (memcmp(file_data.cFileName, _T("."), 4) && memcmp(file_data.cFileName, _T(".."), 6)) {
				//file_path.Format(_T("%s\\%s"), ap_path, file_data.cFileName);
				_stprintf_s(file_path, MAX_PATH, _T("%s\\%s"), ap_path, file_data.cFileName);
				m_drop_list.InsertString(a_insert_index, file_path);
				m_drop_list.SetItemData(a_insert_index++, (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) / 16);
			}
		} while (FindNextFile(h_item_list, &file_data));
		FindClose(h_item_list);
	}
}

void CMFCL209DragDropDlg::OnBnClickedHidePathCheck()
{
	// TODO: Add your control notification handler code here
	m_drop_list.SetSimpleMode((static_cast<CButton*>(GetDlgItem(IDC_HIDE_PATH_CHECK))->GetCheck()));
}
