
// MFCBasic211SnakeGameTDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic211SnakeGameT.h"
#include "MFCBasic211SnakeGameTDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic211SnakeGameTDlg dialog



CMFCBasic211SnakeGameTDlg::CMFCBasic211SnakeGameTDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC211SNAKEGAMET_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic211SnakeGameTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCBasic211SnakeGameTDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCBasic211SnakeGameTDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCBasic211SnakeGameTDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCBasic211SnakeGameTDlg message handlers
void CMFCBasic211SnakeGameTDlg::DrawMap()
{
	m_draw_dc.SelectStockObject(DC_BRUSH);
	m_draw_dc.SelectStockObject(DC_PEN);
	m_draw_dc.SetDCPenColor(RGB(48, 48, 12));
	m_draw_dc.SetDCBrushColor(RGB(0, 0, 0));

	// 맵 그리기
	m_draw_dc.SetDCBrushColor(RGB(0, 0, 0));
	for (int y = 0; y < 60; y++) {
		for (int x = 0; x < 80; x++) {
			m_draw_dc.Rectangle(x * 10, y * 10, x * 10 + 11, y * 10 + 11);
		}
	}

	// 먹이 그리기
	MapPoint* p = m_eat_pos;
	m_draw_dc.SetDCBrushColor(RGB(255, 0, 0));
	for (int i = 0; i < MAX_LENGTH - m_eat_count; i++, p++) {
		m_draw_dc.Rectangle(p->x * 10, p->y * 10, p->x * 10 + 11, p->y * 10 + 11);
	}

	// 뱀 그리기
	p = m_snake_pos;
	m_draw_dc.SetDCBrushColor(RGB(0, 255, 0));
	for (int i = 0; i <= m_eat_count; i++, p++)
	{
		m_draw_dc.Rectangle(p->x * 10, p->y * 10, p->x * 10 + 11, p->y * 10 + 11);
	}
}

void CMFCBasic211SnakeGameTDlg::GameOver()
{
	KillTimer(1);
	MessageBox(_T("게임 오버"), _T("Game Over"), MB_ICONSTOP);
}

BOOL CMFCBasic211SnakeGameTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_draw_image.Create(801, 601, 32);
	m_draw_dc.Attach(m_draw_image.GetDC());

	srand((unsigned int)time(NULL));
	
	MapPoint *p = m_eat_pos, *p_check;			// 배열의 시작주소
	for (int i = 0; i < MAX_EAT_COUNT; i++, p++){
		p->x = rand() % 80;
		p->y = rand() % 60;

		p_check = m_eat_pos;
		for (int sub_i = 0; sub_i < i; sub_i++, p_check++){
			if (p_check->x == p->x && p_check->y == p->y){
				i--;
				p--;
				break;
			}
		}
	}
	DrawMap();

	SetTimer(1, 200, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic211SnakeGameTDlg::OnPaint()
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
		m_draw_image.Draw(dc, 0, 0);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic211SnakeGameTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic211SnakeGameTDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCBasic211SnakeGameTDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CMFCBasic211SnakeGameTDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1)
	{
		if (m_direction == 0) m_pos.x--;					// left
		else if (m_direction == 1) m_pos.y--;			// up
		else if (m_direction == 2) m_pos.x++;		// right
		else m_pos.y++;										// down

		if (m_pos.x >= 0 && m_pos.x <= 79 && m_pos.y >= 0 && m_pos.y <= 59) {
			MapPoint* p = m_eat_pos;
			int eat_flag = 0;

			// 먹이를 먹음
			for (int i = 0; i < m_remain_count; i++, p++)
			{
				if (p->x == m_pos.x && p->y == m_pos.y) {
					m_eat_count++;
					m_remain_count--;
					SetDlgItemInt(IDC_EAT_COUNT_EDIT, m_eat_count);
					if (m_remain_count > 0 && i<m_remain_count) {
						p->x = m_eat_pos[m_remain_count].x;
						p->y = m_eat_pos[m_remain_count].y;
					}
					eat_flag = 1;
					break;
				}
			}

			// 먹이를 먹지 못한 경우 꼬리와 부딪혔는지 체크
			if (m_eat_count) {
				if (eat_flag == 0) {
					p = m_snake_pos;
					for (int i = 0; i < m_eat_count; i++, p++) {
						if (p->x == m_pos.x && p->y == m_pos.y) {
							GameOver();
							return;
						}
					}
				}
				p = m_snake_pos + m_eat_count;			// 끝번째 방을 가리키게함
				for (int i = 0; i < m_eat_count; i++, p--) {
					*p = *(p-1);				// 앞쪽방의 역참조값을 현재방의 역참조값에 넣음
				}
			}

			m_snake_pos[0].x = m_pos.x;
			m_snake_pos[0].y = m_pos.y;

			DrawMap();

			CClientDC dc(this);
			m_draw_image.Draw(dc, 0,0);
		}
		else {
			GameOver();
		}
	}
	else
	{
		CDialogEx::OnTimer(nIDEvent);
	}
}


void CMFCBasic211SnakeGameTDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(1);
	m_draw_dc.Detach();
	m_draw_image.ReleaseDC();			// 메모리DC 해제
}

// 키보드 가로채기
BOOL CMFCBasic211SnakeGameTDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam >= VK_LEFT && pMsg->wParam <= VK_DOWN) {
			int old_direction = m_direction;
			m_direction = pMsg->wParam - VK_LEFT;
			if (old_direction - m_direction > 0) {
				if ((old_direction - m_direction) == 2) m_direction = old_direction;
			}
			else {
				if ((m_direction - old_direction) == 2) m_direction = old_direction;
			}
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
