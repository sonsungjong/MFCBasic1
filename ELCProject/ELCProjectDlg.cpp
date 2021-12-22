
// ELCProjectDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "ELCProject.h"
#include "ELCProjectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void TWAPI_MakeGateImage(TW_DCP* ap_dcp);
void TWAPI_DrawGateImage(TW_DCP* ap_dcp, int a_x, int a_y, TW_DCP* ap_gate_dcp, int a_gate_id, int a_mode);

// 연결리스트 보관중인 게이트 정보 한개 제거할 때마다 호출
void DeleteGate(void* ap_data)
{
	delete (GateData*)ap_data;
}

// CELCProjectDlg dialog
CELCProjectDlg::CELCProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ELCPROJECT_DIALOG, pParent), m_gate_list(DeleteGate)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CELCProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CELCProjectDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CELCProjectDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CELCProjectDlg::OnBnClickedCancel)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_ADD_OR_BTN, IDC_ADD_NOT_BTN, &CELCProjectDlg::OnBnClickedAddGateBtn)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CELCProjectDlg message handlers

BOOL CELCProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	GetDlgItem(IDC_DRAW_RECT)->GetWindowRect(m_rect);
	ScreenToClient(m_rect);
	//GDI+ : 회로
	m_dcp.CreateDCP(m_rect.Width(), m_rect.Height());
	//GDI+ : 게이트 이미지
	m_gate_dcp.CreateDCP(700, 280);

	// 어두운 회색
	m_dcp.Clear(RGB24(18, 21, 29));

	TWAPI_MakeGateImage(&m_gate_dcp);

	DrawBoard();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CELCProjectDlg::DrawBoard()
{
	m_dcp.Clear(RGB24(18, 21, 29));
	int y_step = m_rect.Height() / GRID_INTERVAL;
	int x_step = m_rect.Width() / GRID_INTERVAL;
	int x, y;

	m_dcp.SetDCPenColor(Gdiplus::DashStyleSolid, 1, RGB32(32, 128, 128, 128));
	for (y = 0; y < y_step; y++)
	{
		m_dcp.DrawLine(0, y * GRID_INTERVAL, m_rect.right, y * GRID_INTERVAL);
	}
	for (x = 0; x < x_step; x++)
	{
		m_dcp.DrawLine(x * GRID_INTERVAL, 0, x * GRID_INTERVAL, m_rect.bottom);
	}
	node* p_node = m_gate_list.GetHead();
	GateData* p_gate;
	while (p_node) {
		p_gate = (GateData*)p_node->p_data;
		TWAPI_DrawGateImage(&m_dcp, p_gate->pos.x, p_gate->pos.y, &m_gate_dcp, p_gate->type, 0);
		p_node = p_node->p_next;
	}
	if (mp_selected_gate) {
		TWAPI_DrawGateImage(&m_dcp, mp_selected_gate->pos.x, mp_selected_gate->pos.y,
			&m_gate_dcp, mp_selected_gate->type, 1);
	}
}

void CELCProjectDlg::OnPaint()
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
		m_dcp.Draw(dc, m_rect.left, m_rect.top);
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CELCProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CELCProjectDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CELCProjectDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CELCProjectDlg::OnBnClickedAddGateBtn(UINT a_ctrl_id)
{
	UINT gate_id = a_ctrl_id - IDC_ADD_OR_BTN;

	// 추가할 게이트정보 저장할 메모리할당
	GateData* p_gate = new GateData;
	p_gate->type = gate_id;			// 게이트 종류
	p_gate->label_index = 0;			// 사용 안함
	p_gate->state = 0;				// 실행시 사용할 게이트 상태
	p_gate->contact_count = 0;		// 선과 연결된 위치정보
	p_gate->pos.x = ((m_rect.Width() - 100)/GRID_INTERVAL) / GRID_INTERVAL;
	p_gate->pos.y = GRID_INTERVAL*5;

m_gate_list.AddNode(p_gate);		// 끝에 추가
DrawBoard();
//TWAPI_DrawGateImage(&m_dcp, 28, 28, &m_gate_dcp, gate_id, 0);

InvalidateRect(m_rect, 0);
}

void CELCProjectDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_is_clicked)
	{
		// 마우스 시작위치 보정
		point.x -= m_rect.left;
		point.y -= m_rect.top;

		mp_selected_gate = nullptr;
		node* p_node = m_gate_list.GetHead();
		GateData* p_gate;
		while (p_node) {
			p_gate = (GateData*)p_node->p_data;
			if (p_gate->pos.x <= point.x && point.x <= (p_gate->pos.x + 82)
				&& p_gate->pos.y <= point.y && point.y <= (p_gate->pos.y + 70))
			{
				// 선택된 게이트 주소 저장
				mp_selected_gate = p_gate;
				m_is_clicked = 1;
				SetCapture();
				m_prev_position = point;
				break;
			}
			p_node = p_node->p_next;
		}
		DrawBoard();
		InvalidateRect(m_rect, 0);
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CELCProjectDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked) {
		point.x -= m_rect.left;
		point.y -= m_rect.top;

		int cx = point.x - m_prev_position.x;
		int cy = point.y - m_prev_position.y;

		mp_selected_gate->pos.x += cx;
		mp_selected_gate->pos.y += cy;

		mp_selected_gate->pos.x = ((mp_selected_gate->pos.x + GRID_INTERVAL / 2) / GRID_INTERVAL) * GRID_INTERVAL;
		mp_selected_gate->pos.y = ((mp_selected_gate->pos.y + GRID_INTERVAL / 2) / GRID_INTERVAL) * GRID_INTERVAL;
		DrawBoard();
		InvalidateRect(m_rect, 0);

		ReleaseCapture();
		m_is_clicked = 0;
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CELCProjectDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_is_clicked) {
		point.x -= m_rect.left;
		point.y -= m_rect.top;
		int cx = point.x - m_prev_position.x;
		int cy = point.y - m_prev_position.y;
		mp_selected_gate->pos.x += cx;
		mp_selected_gate->pos.y += cy;
		DrawBoard();
		InvalidateRect(m_rect, 0);

		m_prev_position = point;
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL CELCProjectDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (mp_selected_gate && pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam >= VK_LEFT && pMsg->wParam <= VK_DOWN) {
			if (pMsg->wParam == VK_LEFT) {
				if (mp_selected_gate->pos.x >= GRID_INTERVAL) {
					mp_selected_gate->pos.x -= GRID_INTERVAL;
				}
			}
			else if (pMsg->wParam == VK_RIGHT) {
				mp_selected_gate->pos.x += GRID_INTERVAL;
			}
			else if (pMsg->wParam == VK_UP) {
				if (mp_selected_gate->pos.y >= GRID_INTERVAL){
					mp_selected_gate->pos.y -= GRID_INTERVAL;
				}
			}
			else if (pMsg->wParam == VK_DOWN) {
				mp_selected_gate->pos.y += GRID_INTERVAL;
			}
			DrawBoard();
			InvalidateRect(m_rect, 0);
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
