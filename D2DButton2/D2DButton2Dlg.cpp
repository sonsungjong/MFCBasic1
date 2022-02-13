
// D2DButton2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "D2DButton2.h"
#include "D2DButton2Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 디폴트 D2D 객체를 전역 변수로 생성해서 자동 초기화 시킨다.
TWD_Core g_tw_d2d_core;


// CD2DButton2Dlg dialog
CD2DButton2Dlg::CD2DButton2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_D2DBUTTON2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CD2DButton2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CD2DButton2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CD2DButton2Dlg::OnBnClickedOk)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(27000, &CD2DButton2Dlg::On27000)
END_MESSAGE_MAP()


// CD2DButton2Dlg message handlers

BOOL CD2DButton2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// 클라이언트 영역을 저장
	::RECT r;
	::GetClientRect(m_hWnd, &r);
	// D2D 출력 영역 구성
	m_view.Create(m_hWnd, &r);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CD2DButton2Dlg::OnPaint()
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
		m_view.OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CD2DButton2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CD2DButton2Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CD2DButton2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


void CD2DButton2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	for (int i = 0; i < 3; i++) {
		// 눌려진 버튼을 체크한다
		if (TW_PtInRectF(m_view.GetBtnRect(i), &point)) {
			// 선택한 버튼의 인덱스를 기억한다.
			m_view.SetSelectedBtn(i);
			// 선택한 버튼의 상태를 1로 변경한다.
			m_view.SetBtnState(i, 1);
			// 선택 상황이 반영되도록 버튼을 다시 그린다.
			m_view.UpdateView();
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CD2DButton2Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	unsigned char index = m_view.GetSelectedBtn();

	// 선택한 버튼이 있는지 체크한다.
	if (index != 0xFF) {
		// 버튼의 상태가 1인 경우에만 클릭 상태를 통보한다.
		// 이미 0이라면 버튼 밖에 마우스가 있는 상태라서 다시 그리지 않는다.
		if (m_view.GetBtnState(index) == 1) {
			if (TW_PtInRectF(m_view.GetBtnRect(index), &point)) {
				PostMessage(27000, index);
			}
			m_view.SetBtnState(index, 0);
			m_view.UpdateView();
		}
		// 버튼 선택 상태를 초기화한다.
		m_view.SetSelectedBtn(0xFF);
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CD2DButton2Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	unsigned char index = m_view.GetSelectedBtn();

	// 선택된 버튼이 있는지 체크한다.
	if (index != 0xFF) {
		// 버튼 내부에 마우스가 있는지 체크한다.
		if (TW_PtInRectF(m_view.GetBtnRect(index), &point)) {
			// 내부에 있다하더라도 이미 1인 상태라면 상태를 갱신하지 않는다.
			if (m_view.GetBtnState(index) == 0) {
				m_view.SetBtnState(index, 1);
				m_view.UpdateView();
			}
		}
		else {
			// 외부에 있더라도 이미 0인 상태라면 상태를 갱신하지 않는다.
			if (m_view.GetBtnState(index) == 1) {
				m_view.SetBtnState(index, 0);
				m_view.UpdateView();
			}
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


afx_msg LRESULT CD2DButton2Dlg::On27000(WPARAM wParam, LPARAM lParam)
{
	const TCHAR* p_msg_list[3] = { _T("손성종"), _T("미가공"), _T("네글자임")};
	AfxMessageBox(p_msg_list[wParam]);
	return 0;
}
