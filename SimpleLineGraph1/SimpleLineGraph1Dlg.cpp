
// SimpleLineGraph1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "SimpleLineGraph1.h"
#include "SimpleLineGraph1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimpleLineGraph1Dlg dialog



CSimpleLineGraph1Dlg::CSimpleLineGraph1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SIMPLELINEGRAPH1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimpleLineGraph1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSimpleLineGraph1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSimpleLineGraph1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSimpleLineGraph1Dlg::OnBnClickedCancel)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSimpleLineGraph1Dlg message handlers

BOOL CSimpleLineGraph1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	srand(GetTickCount64());

	GetDlgItem(IDC_GRAPH_RECT)->GetWindowRect(m_rect);
	ScreenToClient(m_rect);

	m_half_cy = m_rect.Height() / 2;

	m_graph_image.Create(m_rect.Width(), m_rect.Height(), 32);
	mh_graph_dc = m_graph_image.GetDC();

	::SelectObject(mh_graph_dc, ::GetStockObject(DC_BRUSH));
	::SelectObject(mh_graph_dc, ::GetStockObject(DC_PEN));

	m_data_limit_count = m_rect.Width() / X_INTERVAL + 1;
	mp_data_list = new int[m_data_limit_count];

	DrawGraph();

	SetTimer(1, 100, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSimpleLineGraph1Dlg::OnPaint()
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
		m_graph_image.Draw(dc, m_rect);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSimpleLineGraph1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSimpleLineGraph1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CSimpleLineGraph1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CSimpleLineGraph1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);
	delete[] mp_data_list;
	m_graph_image.ReleaseDC();
	m_graph_image.Destroy();
}

// 그래프 그리기
void CSimpleLineGraph1Dlg::DrawGraph()
{
	::SetDCBrushColor(mh_graph_dc, RGB(0, 0, 0));
	::SetDCPenColor(mh_graph_dc, RGB(0, 0, 0));
	::Rectangle(mh_graph_dc, 0, 0, m_rect.Width(), m_rect.Height());

	// 중앙선 그림
	::SetDCPenColor(mh_graph_dc, RGB(64, 64, 64));
	::MoveToEx(mh_graph_dc, 0, m_half_cy, NULL);
	::LineTo(mh_graph_dc, m_rect.Width(), m_half_cy);

	// 데이터가 2개 이상이면 선그래프를 그림
	if (m_data_count >= 2) {
		::SetDCPenColor(mh_graph_dc, RGB(0, 228, 0));

		// 선 시작 위치
		int x = m_rect.right;				// 오른쪽 시작 (성종)
		::MoveToEx(mh_graph_dc, x, m_half_cy - *(mp_data_list + 0), NULL);

		// 그 다음 선들을 이어서 그림
		for (int i = 1; i < m_data_count; i++) {
			x -= X_INTERVAL;				// x 위치 변경 (-8만큼 이동) (성종)
			::LineTo(mh_graph_dc, x, m_half_cy - *(mp_data_list + i));
		}
	}
}

void CSimpleLineGraph1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		if (m_data_count < m_data_limit_count) {
			*(mp_data_list + m_data_count) = rand() % 201 - 100;
			m_data_count++;
		}
		else {
			// 데이터가 가득 찼을 경우
			// 메모리 이동 (첫번째 메모리부터 시작되는 메모리 사이즈를 0번째로 옮김)
			memmove(mp_data_list + 0, mp_data_list + 1, sizeof(int) * (m_data_count - 1));
			*(mp_data_list + m_data_count - 1) = rand() % 201 - 100;
		}
		DrawGraph();				// dc에 그림

		// WM_PAINT를 안거치고 dc를 생성해서 바로 그림
		CClientDC dc(this);
		m_graph_image.Draw(dc, m_rect);
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}

}
