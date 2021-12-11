
// MFCL103ListBoxOwnerDrawDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL103ListBoxOwnerDraw.h"
#include "MFCL103ListBoxOwnerDrawDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL103ListBoxOwnerDrawDlg dialog



CMFCL103ListBoxOwnerDrawDlg::CMFCL103ListBoxOwnerDrawDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL103LISTBOXOWNERDRAW_DIALOG, pParent)
	, m_list_box_bk_brush(RGB(0,0,128))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL103ListBoxOwnerDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATA_LIST, m_data_list);
}

BEGIN_MESSAGE_MAP(CMFCL103ListBoxOwnerDrawDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DRAWITEM()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCL103ListBoxOwnerDrawDlg message handlers

BOOL CMFCL103ListBoxOwnerDrawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CString str;
	for (int i = 0; i < 10; i++)
	{
		str.Format(_T("item - %d"), i);
		m_data_list.InsertString(i, str);
	}

	m_data_list.SetItemHeight(0, 22);			// 0번을 높이 22

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCL103ListBoxOwnerDrawDlg::OnPaint()
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
HCURSOR CMFCL103ListBoxOwnerDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL103ListBoxOwnerDrawDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialogEx::OnOK();
}


void CMFCL103ListBoxOwnerDrawDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnCancel();
}

// ListBox 내부항목마다 호출됨
void CMFCL103ListBoxOwnerDrawDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDCtl == IDC_DATA_LIST)
	{
		// 예외처리
		if (lpDrawItemStruct->itemID != 0xFFFFFFFF) {
			if ((lpDrawItemStruct->itemAction & ODA_DRAWENTIRE)				// 과부하방지
				|| (lpDrawItemStruct->itemAction & ODA_FOCUS)
				|| (lpDrawItemStruct->itemAction & ODA_SELECT)
				)
			{
				CDC* p_dc = CDC::FromHandle(lpDrawItemStruct->hDC);				// 깡통WrapperClass

				if (lpDrawItemStruct->itemState & ODS_SELECTED) {			// 선택시
					p_dc->FillSolidRect(&lpDrawItemStruct->rcItem, RGB(0, 200, 255));
					p_dc->SetTextColor(RGB(255, 255, 0));
				}
				else {
					p_dc->FillSolidRect(&lpDrawItemStruct->rcItem, RGB(0, 0, 128));
					p_dc->SetTextColor(RGB(200, 200, 200));
				}

				CString str;
				m_data_list.GetText(lpDrawItemStruct->itemID, str);
				// 글자

				p_dc->TextOut(lpDrawItemStruct->rcItem.left + 5, lpDrawItemStruct->rcItem.top + 6, str);
			}
		}
	}
	else { CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct); }
}

// 없는 부분도 파란색으로
HBRUSH CMFCL103ListBoxOwnerDrawDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (pWnd != nullptr && pWnd->m_hWnd == m_data_list.m_hWnd)
	{
		hbr = m_list_box_bk_brush;
	}
	else {
		hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
