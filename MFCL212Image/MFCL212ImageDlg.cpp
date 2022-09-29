
// MFCL212ImageDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL212Image.h"
#include "MFCL212ImageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL212ImageDlg dialog



CMFCL212ImageDlg::CMFCL212ImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL212IMAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL212ImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_IMAGE, m_list_image);
	DDX_Control(pDX, IDC_COMBO_LOG, m_log_list);
}

BEGIN_MESSAGE_MAP(CMFCL212ImageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL212ImageDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL212ImageDlg::OnBnClickedCancel)
	ON_LBN_DBLCLK(IDC_LIST_IMAGE, &CMFCL212ImageDlg::OnLbnDblclkListImage)
	ON_LBN_SELCHANGE(IDC_LIST_IMAGE, &CMFCL212ImageDlg::OnLbnSelchangeListImage)
	ON_BN_CLICKED(IDC_BUTTON_RESIZE, &CMFCL212ImageDlg::OnBnClickedButtonResize)
END_MESSAGE_MAP()


// CMFCL212ImageDlg message handlers

BOOL CMFCL212ImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetDlgItem(IDC_PICTURE_IMAGE)->GetWindowRect(m_rect);
	ScreenToClient(m_rect);

	TCHAR temp_path[MAX_PATH];

	int len = GetCurrentDirectory(MAX_PATH, temp_path);
	if (len > 3) {
		temp_path[len++] = '\\';
		temp_path[len] = 0;
	}

	SetDlgItemText(IDC_EDIT_PATH, temp_path);
	DirToList(temp_path);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL212ImageDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{

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
		//CDialogEx::OnPaint();
		if (!m_image.IsNull()) {
			dc.SetStretchBltMode(COLORONCOLOR);								// 이미지 리사이징할때 이미지 깨짐 방지
			m_image.Draw(dc, m_rect);
		}
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCL212ImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL212ImageDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
	OnLbnDblclkListImage();
}


void CMFCL212ImageDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CMFCL212ImageDlg::DirToList(const TCHAR* ap_path)
{
	// 리스트 박스 기존 목록 모두 제거
	m_list_image.ResetContent();

	const TCHAR* p_file_ext;
	CString name, temp_name;
	WIN32_FIND_DATA file_data;
	HANDLE h_item_list = FindFirstFile(CString(ap_path) + _T("*.*"), &file_data);
	if (h_item_list != INVALID_HANDLE_VALUE) {
		do {
			if (file_data.cFileName[0] != '.' || file_data.cFileName[1]) {
				name = file_data.cFileName;
				if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					m_list_image.InsertString(-1, _T("[")+name+_T("]"));
				}
				else {
					temp_name = name;
					temp_name.MakeLower();
					int position = temp_name.ReverseFind('.');
					p_file_ext = (const TCHAR*)temp_name + position;

					if (!_tcscmp(p_file_ext, _T(".png")) || !_tcscmp(p_file_ext, _T(".jpg")) ||
						!_tcscmp(p_file_ext, _T(".jpeg")) || !_tcscmp(p_file_ext, _T(".bmp")))
					{
						m_list_image.InsertString(-1, name);
					}
				}
			}
		} while (FindNextFile(h_item_list, &file_data));
		FindClose(h_item_list);
	}
}

void CMFCL212ImageDlg::AddLogString(const TCHAR* ap_string)
{
	int index = m_log_list.InsertString(-1, ap_string);
	m_log_list.SetCurSel(index);
}

// 리스트박스 더블클릭
void CMFCL212ImageDlg::OnLbnDblclkListImage()
{
	CString str, path;

	int index = m_list_image.GetCurSel();
	m_list_image.GetText(index, str);
	if (str[0] == '[') {
		GetDlgItemText(IDC_EDIT_PATH, path);
		str.TrimLeft('[');
		str.TrimRight(']');

		if (str == _T("..")) {
			// 이전 경로
			path.TrimRight('\\');
			int position = path.ReverseFind('\\');
			path.Delete(position + 1, path.GetLength() - position - 1);
		}
		else {
			path += str;
			path += _T("\\");
		}
		SetDlgItemText(IDC_EDIT_PATH, path);
		DirToList(path);
	}
}

// 리스트박스 선택시
void CMFCL212ImageDlg::OnLbnSelchangeListImage()
{
	CString str, path;
	int index = m_list_image.GetCurSel();
	m_list_image.GetText(index, str);
	if (str[0] != '[') {
		m_select_name = str;
		if (m_image.IsNull() == FALSE) {
			m_image.Destroy();
		}
		GetDlgItemText(IDC_EDIT_PATH, m_select_path);
		m_image.Load(m_select_path + m_select_name);
		InvalidateRect(m_rect);

		int position = m_select_name.ReverseFind('.');
		m_select_name.Delete(position + 1, m_select_name.GetLength() - position - 1);
		m_select_name += _T("png");

		str.Format(_T("폭:%d, 높이:%d, 색상수:%d, Pitch:%d"), m_image.GetWidth(), m_image.GetHeight(), m_image.GetBPP(), m_image.GetPitch());
		AddLogString(str);
	}
}


void CMFCL212ImageDlg::OnBnClickedButtonResize()
{
	if (m_image.IsNull() == FALSE)
	{
		int dest_width = GetDlgItemInt(IDC_EDIT_WIDTH), dest_height = GetDlgItemInt(IDC_EDIT_HEIGHT);
		int src_width = m_image.GetWidth(), src_height = m_image.GetHeight();

		CImage dest_image;
		dest_image.Create(dest_width, dest_height, 32);
		HDC h_dc = dest_image.GetDC();
		RECT r = { 0, 0, dest_width, dest_height };
		FillRect(h_dc, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));
		::SetStretchBltMode(h_dc, COLORONCOLOR);						// 크기 변경시 깨지지 않도록 옵션 변경
		::StretchBlt(h_dc, 0, 0, dest_width, dest_height, m_image.GetDC(), 0, 0, src_width, src_height, SRCCOPY);

		dest_image.ReleaseDC();
		m_image.ReleaseDC();

		m_select_name = _T("T") + m_select_name;
		dest_image.Save(m_select_path + m_select_name, Gdiplus::ImageFormatPNG);
		dest_image.Destroy();

		CString current_path;
		GetDlgItemText(IDC_EDIT_PATH, current_path);
		if (m_select_path == current_path) {
			m_list_image.InsertString(-1, m_select_name);
		}

		CString str;
		str.Format(_T("변환된 이미지는 %s 파일에 저장되었습니다."), m_select_name);
		AddLogString(str);
	}
}
