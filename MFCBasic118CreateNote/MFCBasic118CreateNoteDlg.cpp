
// MFCBasic118CreateNoteDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic118CreateNote.h"
#include "MFCBasic118CreateNoteDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic118CreateNoteDlg dialog



CMFCBasic118CreateNoteDlg::CMFCBasic118CreateNoteDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC118CREATENOTE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic118CreateNoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic118CreateNoteDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCBasic118CreateNoteDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCBasic118CreateNoteDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_OPEN_BTN, &CMFCBasic118CreateNoteDlg::OnBnClickedOpenBtn)
	ON_BN_CLICKED(IDC_SAVE_BTN, &CMFCBasic118CreateNoteDlg::OnBnClickedSaveBtn)
END_MESSAGE_MAP()


// CMFCBasic118CreateNoteDlg message handlers

BOOL CMFCBasic118CreateNoteDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic118CreateNoteDlg::OnPaint()
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
HCURSOR CMFCBasic118CreateNoteDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic118CreateNoteDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCBasic118CreateNoteDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	int result = MessageBox(L"프로그램을 종료하시겠습니까?", L"종료", MB_OKCANCEL | MB_ICONQUESTION);
	if(result == IDOK) CDialogEx::OnCancel();
}


void CMFCBasic118CreateNoteDlg::OnBnClickedOpenBtn()
{
	// TODO: Add your control notification handler code here
	wchar_t name_filter[] = L"모든 파일 (*.*)|*.*|C++ 파일 (*.cpp)|*.cpp|Header 파일 (*.h)|*.h|텍스트 파일 (*.txt)|*.txt||";
	CFileDialog ins_dlg(TRUE, L"txt", L"*.txt", OFN_HIDEREADONLY | OFN_NOCHANGEDIR, name_filter);		// TRUE면 Open, FALSE면 Save
	ins_dlg.m_ofn.nFilterIndex = 4;		// 기본 선택 파일
	
	if (IDOK == ins_dlg.DoModal()) {
		SetDlgItemText(IDC_PATH_EDIT, ins_dlg.GetPathName());			// UTF-8

		FILE* p_file = NULL;
		CString str;
		if (0 == _wfopen_s(&p_file, ins_dlg.GetPathName(), L"rt")) {		// 성공시 0 return
			char temp_str[1024];
			int length;		// 변환 후 길이를 저장할 변수
			wchar_t unicode_str[1024];
			while (fgets(temp_str, 1024, p_file) != NULL) {			// 한줄씩 읽되 글자가 없으면 0 return
				// 유니코드로 변환
				length = MultiByteToWideChar(CP_UTF8, 0, temp_str, -1, NULL, 0);
				MultiByteToWideChar(CP_UTF8, 0, temp_str, -1, unicode_str, length);		// UTF-8을 UniCode로 변경
				str += unicode_str;
				//str += temp_str;
			}
			str.Replace(L"\n", L"\r\n");			// str 중 모든 \n을 \r\n으로 변경
			SetDlgItemText(IDC_NOTE_EDIT, str);
			fclose(p_file);
		}
	}
}


void CMFCBasic118CreateNoteDlg::OnBnClickedSaveBtn()
{
	// TODO: Add your control notification handler code here
	wchar_t name_filter[] = L"모든 파일 (*.*)|*.*|C++ 파일 (*.cpp)|*.cpp|Header 파일 (*.h)|*.h|텍스트 파일 (*.txt)|*.txt||";
	CFileDialog ins_dlg(FALSE, L"txt", L"*.txt", OFN_HIDEREADONLY | OFN_NOCHANGEDIR | OFN_OVERWRITEPROMPT, name_filter);		// TRUE면 Open, FALSE면 Save
	ins_dlg.m_ofn.nFilterIndex = 4;		// 기본 선택 파일

	if (IDOK == ins_dlg.DoModal()) {
		SetDlgItemText(IDC_PATH_EDIT, ins_dlg.GetPathName());

		FILE* p_file = NULL;
		CString str;
		if (0 == _wfopen_s(&p_file, ins_dlg.GetPathName(), L"wt")) {
			GetDlgItemText(IDC_NOTE_EDIT, str);
			str.Replace(L"\r\n", L"\n");

			// int length = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
			int length = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);		// 길이구하기
			char* p = new char[length];
			WideCharToMultiByte(CP_UTF8, 0, str, -1, p, length, NULL, NULL);
			fwrite(p, length, 1, p_file);
			delete[] p;

			fclose(p_file);
		}
	}
}
