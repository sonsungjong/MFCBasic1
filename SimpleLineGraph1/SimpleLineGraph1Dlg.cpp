
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
	ON_BN_CLICKED(IDC_START_BTN, &CSimpleLineGraph1Dlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_STOP_BTN, &CSimpleLineGraph1Dlg::OnBnClickedStopBtn)
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
	mp_pos_list = new POINT[m_data_limit_count];

	int x = m_rect.Width() - 5;					// ���� ��ġ
	// x��ǥ�� �����̱� ������ �̸� ����س��´�
	for (int i = 0; i < m_data_limit_count; i++, x -= X_INTERVAL) {
		mp_pos_list[i].x = x;
	}

	DrawGraph();

	

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
	OnBnClickedStopBtn();
	delete[] mp_data_list;
	delete[] mp_pos_list;
	m_graph_image.ReleaseDC();
	m_graph_image.Destroy();
}

// �׷��� �׸���
void CSimpleLineGraph1Dlg::DrawGraph()
{
	::SetDCBrushColor(mh_graph_dc, RGB(0, 0, 0));
	::SetDCPenColor(mh_graph_dc, RGB(0, 0, 0));
	::Rectangle(mh_graph_dc, 0, 0, m_rect.Width(), m_rect.Height());

	// �߾Ӽ� �׸�
	::SetDCPenColor(mh_graph_dc, RGB(64, 64, 64));
	::MoveToEx(mh_graph_dc, 0, m_half_cy, NULL);
	::LineTo(mh_graph_dc, m_rect.Width(), m_half_cy);

	// �����Ͱ� 2�� �̻��̸� ���׷����� �׸�
	if (m_data_count >= 2) {
		::SetDCPenColor(mh_graph_dc, RGB(0, 118, 0));

		POINT* p_pos = mp_pos_list;
		POINT* p_limit = p_pos + m_data_count;

		// �� ���� ��ġ
		p_pos->y = m_half_cy - *(mp_data_list + m_scroll_index);
		p_pos++;

		if (m_data_count < m_data_limit_count) {
			for (int i = 1; i < m_data_count; i++) {
				p_pos->y = m_half_cy - *(mp_data_list + i);
				p_pos++;
			}
		}
		else {
			for (int i = 1; i < m_data_count; i++) {
				p_pos->y = m_half_cy - *(mp_data_list + (m_scroll_index + i) % m_data_limit_count);
				p_pos++;
			}
		}
		Polyline(mh_graph_dc, mp_pos_list, m_data_count);

		::SetDCPenColor(mh_graph_dc, RGB(0, 228, 0));
		p_pos = mp_pos_list;			// ó�� ��ġ�� �ٽ� ����
		while (p_pos < p_limit) {
			::Ellipse(mh_graph_dc, p_pos->x - 3, p_pos->y - 3, p_pos->x + 3, p_pos->y + 3);
			p_pos++;
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
			// �����Ͱ� ���� á�� ���
			// �޸� �̵� (ù��° �޸𸮺��� ���۵Ǵ� �޸� ����� 0��°�� �ű�)
			*(mp_data_list + m_scroll_index) = rand() % 201 - 100;
			m_scroll_index = (m_scroll_index + 1) % m_data_limit_count;
		}
		DrawGraph();				// dc�� �׸�

		// WM_PAINT�� �Ȱ�ġ�� dc�� �����ؼ� �ٷ� �׸�
		CClientDC dc(this);
		m_graph_image.Draw(dc, m_rect);

	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}
}


void CSimpleLineGraph1Dlg::OnBnClickedStartBtn()
{
	if (!m_start_flag) {
		m_start_flag = 1;
		SetTimer(1, 100, NULL);
	}

}


void CSimpleLineGraph1Dlg::OnBnClickedStopBtn()
{
	if (m_start_flag) {
		m_start_flag = 0;
		KillTimer(1);
	}

}
