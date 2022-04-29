
// MoveRectangle1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MoveRectangle1.h"
#include "MoveRectangle1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMoveRectangle1Dlg dialog



CMoveRectangle1Dlg::CMoveRectangle1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MOVERECTANGLE1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMoveRectangle1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMoveRectangle1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMoveRectangle1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMoveRectangle1Dlg::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
//	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// CMoveRectangle1Dlg message handlers

BOOL CMoveRectangle1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//m_rect.SetRect(50, 50, 100, 100);
	m_hdc = ::GetDC(m_hWnd);
	m_brush = ::CreateSolidBrush(RGB(0, 255, 0));
	nUp = 50, nDown = 100, nLeft = 50, nRight = 100;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMoveRectangle1Dlg::OnPaint()
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
		//CDialogEx::OnPaint();
		//dc.FillSolidRect(m_rect, RGB(0, 255,0));
		if (m_last_key) {
			::SetBkMode(m_hdc, TRANSPARENT);
			::SetTextColor(m_hdc, RGB(0, 255, 0));
			::SelectObject(m_hdc, GetFont());

			if (m_last_key == VK_LEFT) {
				::TextOut(m_hdc, nLeft - 15, nUp + 19, _T("◀"), 1);
			}else if (m_last_key == VK_UP) {
				::TextOut(m_hdc, nLeft + 19, nUp - 14, _T("▲"), 1);
			}else if (m_last_key == VK_RIGHT) {
				::TextOut(m_hdc, nRight + 2, nUp + 19, _T("▶"), 1);
			}else if (m_last_key == VK_DOWN) {
				::TextOut(m_hdc, nLeft + 19, nDown + 1, _T("▼"), 1);
			}
		}
		::SetRect(&m_rect, nLeft, nUp, nRight, nDown);
		::FillRect(m_hdc, &m_rect, m_brush);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMoveRectangle1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMoveRectangle1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMoveRectangle1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnCancel();
}


void CMoveRectangle1Dlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	::PostQuitMessage(0);

	CDialogEx::OnClose();
}


void CMoveRectangle1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	::ReleaseDC(m_hWnd, m_hdc);
}

// 대화상자보다 먼저 메시지를 가로챔
BOOL CMoveRectangle1Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN) {
		if(pMsg->wParam >= VK_LEFT && pMsg->wParam <= VK_DOWN){
			if (pMsg->wParam == VK_LEFT) {
				nLeft--;
				nRight--;
			}
			else if (pMsg->wParam == VK_RIGHT) {
				nLeft++;
				nRight++;
			}
			else if (pMsg->wParam == VK_UP) {
				nUp--;
				nDown--;
			}
			else if (pMsg->wParam == VK_DOWN) {
				nUp++;
				nDown++;
			}

			m_last_key = pMsg->wParam;
			::InvalidateRect(m_hWnd, &m_rect, TRUE);
			return 1;				// 리턴을 해서 대화상자에서 해당 메시지적용이 안되게 처리
		}
	}
	else if (pMsg->message == WM_KEYUP) {
		if (pMsg->wParam >= VK_LEFT && pMsg->wParam <= VK_DOWN) {
			m_last_key = 0;
			::InvalidateRect(m_hWnd, &m_rect, TRUE);
			return 1;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


//void CMoveRectangle1Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: Add your message handler code here and/or call default
//	switch (nChar)
//	{
//	case VK_LEFT:
//		nLeft--;
//		--nRight;
//		::InvalidateRect(m_hWnd, &m_rect, TRUE);
//		break;
//
//	case VK_RIGHT:
//		nLeft++;
//		nRight++;
//		::InvalidateRect(m_hWnd, &m_rect, TRUE);
//		break;
//
//	case VK_UP:
//		nUp--;
//		nDown--;
//		::InvalidateRect(m_hWnd, &m_rect, TRUE);
//		break;
//
//	case VK_DOWN:
//		nUp++;
//		++nDown;
//		::InvalidateRect(m_hWnd, &m_rect, TRUE);
//		break;
//	}
//
//	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
//}
