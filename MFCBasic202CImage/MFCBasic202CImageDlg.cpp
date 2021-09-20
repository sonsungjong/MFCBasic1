
// MFCBasic202CImageDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic202CImage.h"
#include "MFCBasic202CImageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic202CImageDlg dialog



CMFCBasic202CImageDlg::CMFCBasic202CImageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC202CIMAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic202CImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic202CImageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SELECT_IMG, &CMFCBasic202CImageDlg::OnBnClickedSelectImg)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMFCBasic202CImageDlg message handlers

BOOL CMFCBasic202CImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetClientRect(m_rect);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic202CImageDlg::OnPaint()
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
		if (!m_img.IsNull()) {			// 이미지가 Null이 아니면
			dc.SetStretchBltMode(COLORONCOLOR);
			m_img.Draw(dc, m_rect);
		}
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic202CImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic202CImageDlg::OnBnClickedSelectImg()
{
	// TODO: Add your control notification handler code here
	wchar_t name_filter[] = L"모든 파일(*.*)|*.*|JPG 파일(*.jpg)|*.jpg|PNG 파일(*.png)|*.png||";
	CFileDialog ins_dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_NOCHANGEDIR, name_filter);
	ins_dlg.m_ofn.nFilterIndex = 2;			// 1~
	
	if (IDOK == ins_dlg.DoModal()) {
		if (!m_img.IsNull()) { m_img.Destroy(); }

		m_img.Load(ins_dlg.GetPathName());
		Invalidate(FALSE);
	}
}


void CMFCBasic202CImageDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	GetClientRect(m_rect);
	Invalidate(FALSE);
}
