
// Grid1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Grid1.h"
#include "Grid1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGrid1Dlg dialog



CGrid1Dlg::CGrid1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRID1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGrid1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGrid1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CGrid1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGrid1Dlg::OnBnClickedCancel)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CGrid1Dlg message handlers

BOOL CGrid1Dlg::OnInitDialog()
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

void CGrid1Dlg::OnPaint()
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
		dc.SelectStockObject(DC_BRUSH);
		dc.SelectStockObject(DC_PEN);
		dc.SetDCBrushColor(RGB(255, 255, 255));
		dc.SetDCPenColor(RGB(0, 0, 0));

		for (int y = 0; y < 5; y++){
			for (int x = 0; x < 8; x++) {
				dc.Rectangle(30+x*70, 40+y*20, 101+x*70, 61+y*20);
			}
		}
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGrid1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGrid1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CGrid1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CGrid1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	


	
}
