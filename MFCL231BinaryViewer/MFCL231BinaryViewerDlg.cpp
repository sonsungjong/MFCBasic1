
// MFCL231BinaryViewerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL231BinaryViewer.h"
#include "MFCL231BinaryViewerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL231BinaryViewerDlg dialog



CMFCL231BinaryViewerDlg::CMFCL231BinaryViewerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL231BINARYVIEWER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL231BinaryViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BIN_DATA_LIST, m_bin_data_list);
}

BEGIN_MESSAGE_MAP(CMFCL231BinaryViewerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL231BinaryViewerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL231BinaryViewerDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SELECT_BTN, &CMFCL231BinaryViewerDlg::OnBnClickedSelectBtn)
END_MESSAGE_MAP()


// CMFCL231BinaryViewerDlg message handlers

BOOL CMFCL231BinaryViewerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_font.CreatePointFont(128, _T("굴림체"));					// 굴림체를 화면기준 128크기로 폰트생성
	m_bin_data_list.SetFont(&m_font);						// 리스트박스에 폰트 적용

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL231BinaryViewerDlg::OnPaint()
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
HCURSOR CMFCL231BinaryViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL231BinaryViewerDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL231BinaryViewerDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCL231BinaryViewerDlg::OnBnClickedSelectBtn()
{
	// TODO: Add your control notification handler code here
	CFileDialog ins_dlg(TRUE);
	if (ins_dlg.DoModal() == IDOK) {
		m_bin_data_list.ResetContent();				// 리스트박스 내용 전부 지움
		SetDlgItemText(IDC_PATH_STATIC, ins_dlg.GetPathName());
		FILE *p_file = NULL;
		if (_tfopen_s(&p_file, ins_dlg.GetPathName(), _T("rb")) == 0) {
			// 파일 열기가 성공했다면 0

			TCHAR str[128];
			unsigned char temp[24];
			int len = 24, line = 1, str_len;
			while (len == 24) {
				len = fread(temp, 1, 24, p_file);
				if (len > 0) {
					str_len = _stprintf_s(str, 128, _T("%06d :  "), line++);
					for (int i = 0; i < 24; i++) {
						str_len += _stprintf_s(str + str_len, 128 - str_len, _T("%02X  "), temp[i]);				// 더해서 뒤로감
					}
					m_bin_data_list.InsertString(-1, str);
				}
			}
			fclose(p_file);
		}
	}

}
