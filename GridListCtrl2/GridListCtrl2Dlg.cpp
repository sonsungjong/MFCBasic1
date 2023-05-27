
// GridListCtrl2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "GridListCtrl2.h"
#include "GridListCtrl2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CGridListCtrl2Dlg::CGridListCtrl2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRIDLISTCTRL2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGridListCtrl2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGridListCtrl2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CGridListCtrl2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGridListCtrl2Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SET_BTN, &CGridListCtrl2Dlg::OnBnClickedSetBtn)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
END_MESSAGE_MAP()


// CGridListCtrl2Dlg message handlers

BOOL CGridListCtrl2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	grid_view.SubclassDlgItem(IDC_LIST1, this);

	grid_view.SetGridLine();
	m_test = 1;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGridListCtrl2Dlg::OnPaint()
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
HCURSOR CGridListCtrl2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGridListCtrl2Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CGridListCtrl2Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CGridListCtrl2Dlg::OnBnClickedSetBtn()
{
	// TODO: Add your control notification handler code here
	grid_view.DeleteAllItems();
	for (int i = grid_view.GetHeaderCtrl()->GetItemCount() - 1; i >= 0; i--) { grid_view.DeleteColumn(i); }
	if (m_test == 1) {
		m_test = 2;
		grid_view.SetGridLine2();
	}
	else {
		m_test = 1;
		grid_view.SetGridLine();
	}
}


void CGridListCtrl2Dlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	if (IDC_LIST1 == nIDCtl)
	{
		grid_view.MyDraw(lpDrawItemStruct);
	}
	else
	{
		CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
	}
}


void CGridListCtrl2Dlg::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	if (IDC_LIST1 == nIDCtl)
	{
		lpMeasureItemStruct->itemHeight += 15;
	}

	CDialogEx::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}
