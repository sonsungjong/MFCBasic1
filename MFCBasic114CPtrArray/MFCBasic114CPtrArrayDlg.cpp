
// MFCBasic114CPtrArrayDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic114CPtrArray.h"
#include "MFCBasic114CPtrArrayDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic114CPtrArrayDlg dialog



CMFCBasic114CPtrArrayDlg::CMFCBasic114CPtrArrayDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC114CPTRARRAY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic114CPtrArrayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic114CPtrArrayDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CMFCBasic114CPtrArrayDlg message handlers

BOOL CMFCBasic114CPtrArrayDlg::OnInitDialog()
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

void CMFCBasic114CPtrArrayDlg::OnPaint()
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
		POINT* p;
		int count = m_pos_list.GetCount();

		for (int i = 0; i < count; i++)
		{
			p = (POINT*)m_pos_list.GetAt(i);
			if (p != NULL) {
				dc.Rectangle(p->x - 10, p->y - 10, p->x + 10, p->y + 10);
			}
		}
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic114CPtrArrayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic114CPtrArrayDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	POINT* p = new POINT;		// 좌표를 저장하는 구조체 한개를 동적으로 할당
	p->x = point.x;
	p->y = point.y;
	m_pos_list.Add(p);			// 순차적으로 저장해서 관리해줌

	CClientDC dc(this);
	dc.Rectangle(point.x - 10, point.y - 10, point.x +10, point.y +10);
	

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCBasic114CPtrArrayDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	int count = m_pos_list.GetCount();
	POINT* p;

	for (int i = 0; i < count; i++)
	{
		p = (POINT*)m_pos_list.GetAt(i);
		if(p!=NULL) delete p;
	}
}


void CMFCBasic114CPtrArrayDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	POINT* p;
	int count = m_pos_list.GetCount();
	CRect r;

	for (int i = 0; i < count; i++) {
		p = (POINT*)m_pos_list.GetAt(i);
		if (p != NULL) {
			r.SetRect(p->x - 10, p->y - 10, p->x + 10, p->y + 10);			// 사각형을 새로 하나 그리고
			if (r.PtInRect(point)) {		// 사각형 안에 point가 있으면
				delete p;								// 해당 index를 해제하고
				m_pos_list.SetAt(i, NULL);			// NULL을 넣음 (버그방지)
				break;
			}
		}
	}
	Invalidate();
	CDialogEx::OnRButtonDown(nFlags, point);
}
