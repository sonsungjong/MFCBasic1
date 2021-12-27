
// MFCL106ListBoxOwnerDraw2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL106ListBoxOwnerDraw2.h"
#include "MFCL106ListBoxOwnerDraw2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL106ListBoxOwnerDraw2Dlg dialog



CMFCL106ListBoxOwnerDraw2Dlg::CMFCL106ListBoxOwnerDraw2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL106LISTBOXOWNERDRAW2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL106ListBoxOwnerDraw2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL106ListBoxOwnerDraw2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CMFCL106ListBoxOwnerDraw2Dlg message handlers

BOOL CMFCL106ListBoxOwnerDraw2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	COLORREF color_table[20] = {
		RGB(0,0,0), RGB(0,0,255), RGB(0,255,0), RGB(0,255,255), RGB(255,0,0), RGB(255,0,255),
		RGB(255,255,0), RGB(255,255,255), RGB(0, 0, 128), RGB(0,128, 0), RGB(0, 128, 128),
		RGB(128, 0, 0), RGB(128, 0, 128), RGB(128,128,0), RGB(128,128,128), RGB(192,192,192),
		RGB(192,220,192), RGB(166, 202, 240), RGB(255, 251, 240), RGB(160, 160, 164)
	};

	m_color_list.SubclassDlgItem(IDC_COLOR_LIST, this);
	for (int i = 0; i < 20; i++) {
		m_color_list.InsertString(i, L"");
		m_color_list.SetItemData(i, color_table[i]);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL106ListBoxOwnerDraw2Dlg::OnPaint()
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
		dc.Rectangle(20, 20, 150, 150);

	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCL106ListBoxOwnerDraw2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

