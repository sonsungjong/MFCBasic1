
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


// CGridListCtrl2Dlg dialog



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
		int index = lpDrawItemStruct->itemID;

		if (index >= 0 && index < grid_view.GetItemCount())
		{
			CDC* dc = CDC::FromHandle(lpDrawItemStruct->hDC);
			CRect r = lpDrawItemStruct->rcItem;

			if (lpDrawItemStruct->itemState & ODS_SELECTED)
			{
				// 선택 라인에 대해 글자색과 영역색
				dc->SetTextColor(RGB(30, 30, 250));
				dc->FillSolidRect(r, RGB(188, 231, 241));
			}
			else 
			{
				// 선택이 안된 경우
				dc->SetTextColor(RGB(0, 0, 0));
				dc->FillSolidRect(r, RGB(255, 255, 255));
			}

			LV_COLUMN column_data;
			column_data.mask = LVCF_WIDTH;

			CString str;
			// 각 컬럼은 앞쪽 5만큼 여백을 갖고 문자열을 출력한다
			// 리스트 컨트롤이 갖고 있는 헤더 컨트롤의 포인터를 얻어서 컬럼수를 구한다
			int blank = 5;
			int header_count = grid_view.GetHeaderCtrl()->GetItemCount();

			// 반복문을 돌려 TextOut으로 그린다 (만약 마지막 컬럼만 다른 컨트롤로 주고 싶으면 -1)
			for (int i = 0; i < header_count; i++)
			{
				CRect rcSubItem;
				grid_view.GetSubItemRect(index, i, LVIR_BOUNDS, rcSubItem);

				// 데이터를 얻는다
				str = grid_view.GetItemText(index, i);
				if (i == 0) {
					dc->TextOut(r.left + blank, r.top, str);
				}
				else if (i == header_count-1)
				{
					COLORREF old_color = dc->SetTextColor(RGB(255, 255, 255));
					dc->FillSolidRect(&rcSubItem, RGB(0, 100, 255));
					dc->DrawText(_T("상세 보기"), &rcSubItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
					dc->SetTextColor(old_color);
				}
				else {
					dc->DrawText(str, &rcSubItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
				}


			}
		}
	}
	
	else
	{
		CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
	}
}
