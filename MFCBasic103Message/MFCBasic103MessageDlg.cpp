
// MFCBasic103MessageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic103Message.h"
#include "MFCBasic103MessageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic103MessageDlg 대화 상자



CMFCBasic103MessageDlg::CMFCBasic103MessageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC103MESSAGE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic103MessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

// WindowsProc을 감춤, 메시지 전용
BEGIN_MESSAGE_MAP(CMFCBasic103MessageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMFCBasic103MessageDlg 메시지 처리기

BOOL CMFCBasic103MessageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCBasic103MessageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCBasic103MessageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 가상함수
LRESULT CMFCBasic103MessageDlg::WindowProc(unsigned int message, WPARAM wParam, LPARAM lParam)
{
	// TODO: Add your specialized code here and/or call the base class
	if (message == WM_LBUTTONDOWN) {
		CClientDC dc(this);			// 현재 윈도우에 이 대화상자의 포인터를 넘김

		// 마우스 좌표 추적
		int x = lParam & 0x0000FFFF;			// 하위 16비트 값 분리
		int y = (lParam >> 16) & 0x0000FFFF;			// 상위 16비트 값 분리

		if (wParam & MK_CONTROL) dc.Ellipse(x-50, y-50, x+50, y+50);
		else dc.Rectangle(x - 50, y - 50, x + 50, y + 50);
	}

	return CDialogEx::WindowProc(message, wParam, lParam);
}

/*
	MFC 메시지 처리
	MFC는 main함수에서 다른 함수를 호출하는 방식으로 프로그램이 진행되지 않고 운영체제가 보내주는 메시지를 처리하는 방식으로 작업이 진행된다.
	따라서, 메시지를 처리하는 방식으로 작업을 구성해야 한다.

	MFC가 어떻게 메시지를 처리하는지에 대한 설명

	wParam : 중복키
	nFlags : 중복키
*/
/*
// 메시지 변수
void CMFCBasic103MessageDlg::OnLButtonDown(unsigned int nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);

	if (nFlags & MK_CONTROL) dc.Ellipse(point.x - 50, point.y - 50, point.x + 50, point.y + 50);
	else dc.Rectangle(point.x - 50, point.y - 50, point.x + 50, point.y + 50);

	CDialogEx::OnLButtonDown(nFlags, point);
}
*/