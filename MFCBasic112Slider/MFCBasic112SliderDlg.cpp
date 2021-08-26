
// MFCBasic112SliderDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic112Slider.h"
#include "MFCBasic112SliderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic112SliderDlg dialog



CMFCBasic112SliderDlg::CMFCBasic112SliderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC112SLIDER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic112SliderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER, m_slider);
	DDX_Control(pDX, IDC_EVENT_LIST, m_event_list);
}

BEGIN_MESSAGE_MAP(CMFCBasic112SliderDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER, &CMFCBasic112SliderDlg::OnNMReleasedcaptureSlider)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CMFCBasic112SliderDlg message handlers

BOOL CMFCBasic112SliderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_slider.SetRange(50, 150);			// 최소값50, 최대값150
	m_slider.SetTicFreq(10);				// 눈금간격 10

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic112SliderDlg::OnPaint()
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
HCURSOR CMFCBasic112SliderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic112SliderDlg::OnNMReleasedcaptureSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	/*
	int pos = m_slider.GetPos();		// 현재 위치값

	CString str;
	str.Format(L"%d", pos);
	int index = m_event_list.InsertString(-1, str);			// 가장 뒤쪽에
	m_event_list.SetCurSel(index);
	*/
	*pResult = 0;
}


void CMFCBasic112SliderDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar != NULL && pScrollBar->GetDlgCtrlID() == IDC_SLIDER) {
		/*if (nSBCode == SB_THUMBTRACK) {
			CString str;
			str.Format(L"%d", nPos);
			int index = m_event_list.InsertString(-1, str);
			m_event_list.SetCurSel(index);
		}
		else if (nSBCode == SB_ENDSCROLL) {
			CString str;
			str.Format(L"%d", m_slider.GetPos());
			int index = m_event_list.InsertString(-1, str);
			m_event_list.SetCurSel(index);
		}*/

		if (nSBCode == SB_THUMBTRACK || nSBCode == SB_ENDSCROLL) {
			CString str;
			str.Format(L"%d", m_slider.GetPos());
			int index = m_event_list.InsertString(-1, str);
			m_event_list.SetCurSel(index);
		}
	}
	

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
