
// MFCCaptureDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCCapture.h"
#include "MFCCaptureDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCCaptureDlg dialog



CMFCCaptureDlg::CMFCCaptureDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCAPTURE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCaptureDlg::AddEventString(const wchar_t* ap_string)
{
	int index = m_event_list.InsertString(-1, ap_string);
	m_event_list.SetCurSel(index);
}

void CMFCCaptureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EVENT_LIST, m_event_list);
	DDX_Control(pDX, IDC_AUTO_SAVE_CHECK, m_auto_save_check);
}

BEGIN_MESSAGE_MAP(CMFCCaptureDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCCaptureDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCCaptureDlg::OnBnClickedCancel)
	ON_WM_CHANGECBCHAIN()
	ON_WM_DESTROY()
	ON_WM_DRAWCLIPBOARD()
	ON_BN_CLICKED(IDC_SAVE_BTN, &CMFCCaptureDlg::OnBnClickedSaveBtn)
	ON_BN_CLICKED(IDC_OPEN_PATH_BTN, &CMFCCaptureDlg::OnBnClickedOpenPathBtn)
END_MESSAGE_MAP()


// CMFCCaptureDlg message handlers

BOOL CMFCCaptureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	::CreateDirectory(L"C:\\son", NULL);

	GetDlgItem(IDC_IMAGE_RECT)->GetWindowRect(m_image_rect);
	mh_next_chain = ::SetClipboardViewer(m_hWnd);
	HDC h_dc = ::GetDC(m_hWnd);
	mh_mem_dc = ::CreateCompatibleDC(h_dc);
	::ReleaseDC(m_hWnd, h_dc);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCCaptureDlg::OnPaint()
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
		if (!m_image.IsNull()) {
			dc.SetStretchBltMode(COLORONCOLOR);
			m_image.Draw(dc, m_image_rect);
		}
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCCaptureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCCaptureDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCCaptureDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCCaptureDlg::OnChangeCbChain(HWND hWndRemove, HWND hWndAfter)
{
	CDialogEx::OnChangeCbChain(hWndRemove, hWndAfter);

	// TODO: Add your message handler code here
	if (hWndRemove == mh_next_chain) mh_next_chain = hWndAfter;
	else if (mh_next_chain != NULL) {
		::SendMessage(mh_next_chain, WM_CHANGECBCHAIN, (WPARAM)hWndRemove, (LPARAM)hWndAfter);
	}
}


void CMFCCaptureDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	if (mh_next_chain != NULL) {
		::ChangeClipboardChain(m_hWnd, mh_next_chain);
	}

	::DeleteDC(mh_mem_dc);
}


void CMFCCaptureDlg::OnDrawClipboard()
{
	CDialogEx::OnDrawClipboard();

	// TODO: Add your message handler code here
	unsigned int priority_list = CF_BITMAP;
	int format_info = ::GetPriorityClipboardFormat(&priority_list, 1);
	if (format_info == CF_BITMAP) {
		AddEventString(L"새로운 이미지가 클립보드에 추가되었습니다.");

		if (::OpenClipboard(m_hWnd)) {
			HBITMAP h_bitmap = (HBITMAP)::GetClipboardData(format_info);
			if (h_bitmap != NULL) {
				BITMAP bmp_info;
				::GetObject(h_bitmap, sizeof(BITMAP), &bmp_info);

				CString str;
				str.Format(L"이미지 정보 -> 폭: %d, 높이: %d, 색상: %d", bmp_info.bmWidth, bmp_info.bmHeight, bmp_info.bmBitsPixel);
				AddEventString(str);
				if (!m_image.IsNull()) m_image.Destroy();
				m_image.Create(bmp_info.bmWidth, bmp_info.bmHeight, bmp_info.bmBitsPixel);
				::SelectObject(mh_mem_dc, h_bitmap);
				::BitBlt(m_image.GetDC(), 0,0, bmp_info.bmWidth, bmp_info.bmHeight, mh_mem_dc, 0,0,SRCCOPY);
				m_image.ReleaseDC();
				InvalidateRect(m_image_rect);
				if (m_auto_save_check.GetCheck()) {
					OnBnClickedSaveBtn();
				}
			}
			::CloseClipboard();
		}
	}
}


void CMFCCaptureDlg::OnBnClickedSaveBtn()
{
	// TODO: Add your control notification handler code here
	if (!m_image.IsNull()) {
		CString path;
		SYSTEMTIME cur_time;
		GetLocalTime(&cur_time);

		path.Format(L"c:\\son\\%04d%02d%02d_%02d%02d%02d_%03d.png", 
			cur_time.wYear, cur_time.wMonth, cur_time.wDay, cur_time.wHour, cur_time.wMinute, cur_time.wSecond, cur_time.wMilliseconds);
		m_image.Save(path, Gdiplus::ImageFormatPNG);
	}
}


void CMFCCaptureDlg::OnBnClickedOpenPathBtn()
{
	// TODO: Add your control notification handler code here
	ShellExecute(NULL, L"open", L"c:\\son", NULL, NULL, SW_SHOW);
}
