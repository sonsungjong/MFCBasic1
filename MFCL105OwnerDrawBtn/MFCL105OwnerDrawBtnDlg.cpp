
// MFCL105OwnerDrawBtnDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL105OwnerDrawBtn.h"
#include "MFCL105OwnerDrawBtnDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL105OwnerDrawBtnDlg dialog



CMFCL105OwnerDrawBtnDlg::CMFCL105OwnerDrawBtnDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL105OWNERDRAWBTN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL105OwnerDrawBtnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL105OwnerDrawBtnDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_SELECT_COLOR_BTN, &CMFCL105OwnerDrawBtnDlg::OnBnClickedSelectColorBtn)
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CMFCL105OwnerDrawBtnDlg message handlers

BOOL CMFCL105OwnerDrawBtnDlg::OnInitDialog()
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

void CMFCL105OwnerDrawBtnDlg::OnPaint()
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
		//dc.Rectangle(10, 10, 100, 100);
		dc.FillSolidRect(10, 10, 50, 30, m_user_color);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCL105OwnerDrawBtnDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL105OwnerDrawBtnDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	/*
	CRect r(10, 10, 60, 40);
	if (r.PtInRect(point)) {
		CColorDialog color_dlg;							// 윈도우 색상선택 대화상자
		color_dlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
		color_dlg.m_cc.rgbResult = m_user_color;
		if (IDOK == color_dlg.DoModal())			// 정형대화상자 실행
		{
			m_user_color = color_dlg.GetColor();
			InvalidateRect(r);
		}
	}
	*/
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCL105OwnerDrawBtnDlg::OnBnClickedSelectColorBtn()
{
	// TODO: Add your control notification handler code here
	CColorDialog color_dlg;							// 윈도우 색상선택 대화상자
	color_dlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
	color_dlg.m_cc.rgbResult = m_user_color;
	if (IDOK == color_dlg.DoModal())			// 정형대화상자 실행
	{
		m_user_color = color_dlg.GetColor();
		GetDlgItem(IDC_SELECT_COLOR_BTN)->Invalidate();
		InvalidateRect(CRect(10, 10, 60, 40));
	}
}


void CMFCL105OwnerDrawBtnDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDCtl == IDC_SELECT_COLOR_BTN) {
		CDC* p_dc = CDC::FromHandle(lpDrawItemStruct->hDC);
		p_dc->FillSolidRect(&lpDrawItemStruct->rcItem, RGB(228, 228, 228));
		CString str;
		GetDlgItemText(IDC_SELECT_COLOR_BTN, str);
		CRect r(lpDrawItemStruct->rcItem);
		CRect color_rect(lpDrawItemStruct->rcItem.left + 3, lpDrawItemStruct->rcItem.top + 3, lpDrawItemStruct->rcItem.right - 3, lpDrawItemStruct->rcItem.bottom - 3);

		if (lpDrawItemStruct->itemState & ODS_SELECTED) {					// 버튼을 눌렀을 때
			r.left--; r.top--; r.right--; r.bottom--;
			color_rect -= CPoint(1, 1);
			p_dc->Draw3dRect(&lpDrawItemStruct->rcItem, RGB(210, 210, 210), RGB(238, 238, 238));			// 색반전
		}
		else {
			p_dc->Draw3dRect(&lpDrawItemStruct->rcItem, RGB(248, 248, 248), RGB(168, 168, 168));
		}

		p_dc->SetBkMode(TRANSPARENT);								// 글자배경 투명화
		p_dc->SetTextColor(m_user_color);
		p_dc->DrawText(str, r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);				// 글자출력
		p_dc->Draw3dRect(color_rect, m_user_color, m_user_color);
	}

	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
