
// MFCL205EditCtrl1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCL205EditCtrl1.h"
#include "MFCL205EditCtrl1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCL205EditCtrl1Dlg dialog



CMFCL205EditCtrl1Dlg::CMFCL205EditCtrl1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCL205EDITCTRL1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCL205EditCtrl1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCL205EditCtrl1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCL205EditCtrl1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCL205EditCtrl1Dlg::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCL205EditCtrl1Dlg message handlers

BOOL CMFCL205EditCtrl1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// 컨트롤이 그려질때 특정 메시지를 날려주면 색상을 바꿀 수 있음 WM_CTLCOLOR
	mh_edit_bk_brush = ::CreateSolidBrush(RGB(93, 93, 93));

	for (int i = 0; i < 6; i++) {
		SetDlgItemText(IDC_EDIT1+i, _T("안녕하세요 손성종 입니다^^"));
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCL205EditCtrl1Dlg::OnPaint()
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
HCURSOR CMFCL205EditCtrl1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCL205EditCtrl1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCL205EditCtrl1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


HBRUSH CMFCL205EditCtrl1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	int control_id = pWnd->GetDlgCtrlID();
	if (control_id >= IDC_EDIT1 && control_id <= IDC_EDIT6) {
		HWND cur_focus = ::GetFocus();
		if (cur_focus == pWnd->m_hWnd) {
			if (mh_old_focus != cur_focus) {
				if(mh_old_focus != NULL){
					::InvalidateRect(mh_old_focus, NULL, TRUE);
				}
				mh_old_focus = cur_focus;
			}
			pDC->SetTextColor(RGB(128, 255, 128));				// 글자색 바꾸기
		}
		else {
			pDC->SetTextColor(RGB(255, 228, 0));				// 글자색 바꾸기
		}
		pDC->SetBkColor(RGB(93, 93, 93));					// 배경색 바꾸기
		return mh_edit_bk_brush;
	}

	return hbr;
}


void CMFCL205EditCtrl1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	DeleteObject(mh_edit_bk_brush);
}
