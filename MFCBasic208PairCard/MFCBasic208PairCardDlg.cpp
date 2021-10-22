
// MFCBasic208PairCardDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCBasic208PairCard.h"
#include "MFCBasic208PairCardDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic208PairCardDlg dialog



CMFCBasic208PairCardDlg::CMFCBasic208PairCardDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCBASIC208PAIRCARD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCBasic208PairCardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TIME_PROGRESS, m_time_progress);
}

BEGIN_MESSAGE_MAP(CMFCBasic208PairCardDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCBasic208PairCardDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCBasic208PairCardDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_HINT_BTN, &CMFCBasic208PairCardDlg::OnBnClickedHintBtn)
END_MESSAGE_MAP()


// CMFCBasic208PairCardDlg message handlers

BOOL CMFCBasic208PairCardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CString str;

	for (int i = 0; i < 19; i++) {
		str.Format(L".\\card_image\\%03d.bmp", i);
		m_card_image[i].Load(str);			// 19장의 카드를 읽음
	}

	srand((unsigned int)time(NULL));
	m_time_progress.SetRange(0, 60);				// 0~60

	StartGame();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCBasic208PairCardDlg::OnPaint()
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
		CString str;
		int card_index = 0;
		for (int i = 0; i < 36; i++)
		{
			if (m_table[i] == 0) continue;			// 1회성취소 : 제거된 카드

			if (m_view_flag == 1) {
				card_index = m_table[i];
			}
			m_card_image[card_index].Draw(dc, (i%6)*36, i/6*56);

			str.Format(L"%d", m_table[i]);
			dc.TextOutW(5 + (i % 6) * 36, 5 + i / 6 * 56, str);
		}
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCBasic208PairCardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCBasic208PairCardDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CMFCBasic208PairCardDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CMFCBasic208PairCardDlg::EndOfGame(const wchar_t* ap_msg)
{
	KillTimer(10);
	if (IDOK == MessageBox(L"게임을 다시 시작하시겠습니까?", ap_msg, MB_OKCANCEL | MB_ICONQUESTION)) {
		StartGame();
		Invalidate();				// 이전화면 제거
	}
	else {
		EndDialog(IDOK);				// 대화상자 제거
	}
}

void CMFCBasic208PairCardDlg::StartGame()
{
	SetDlgItemInt(IDC_HINT_BTN, 3);			// 힌트횟수 3

	for (int i = 0; i < 18; i++) {
		m_table[i] = i + 1;			// 카드번호
		m_table[18 + i] = i + 1;
	}

	
	int first, second, temp;
	for (int i = 0; i < 100; i++) {			// 카드섞기
		first = rand() % 36;
		second = rand() % 36;
		if (first != second) {
			// m_table[first] <-> m_table[second]
			temp = m_table[first];
			m_table[first] = m_table[second];
			m_table[second] = temp;
		}
	}
	
	m_time_progress.SetPos(60);						// 초기상태 60

	SetTimer(1, 3000, NULL);				// 카드 공개
	SetTimer(10, 1000, NULL);				// 프로그레스
}

void CMFCBasic208PairCardDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {					//3초
		KillTimer(1);			// 1회용 타이머로 만듦
		m_view_flag = 0;
		Invalidate();
	}
	else if (nIDEvent == 2) {			// 1초
		KillTimer(2);
		m_view_flag = 0;			// 클릭 가능하게 만들어줌
		Invalidate();
	}
	else if (nIDEvent == 10) {				// 1초
		int num = m_time_progress.GetPos()-1;
		if (num > 0) m_time_progress.SetPos(num);
		else {		// 타임오버 게임종료
			EndOfGame(L"타임오버 Fail");
		}
	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}
}

void CMFCBasic208PairCardDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (m_view_flag != 0) return;				// 뒷면이 아니면 버튼을 리턴해버림

	int x = point.x / 36;			// x인덱스
	int y = point.y / 56;			// y인덱스
	
	if (x < 6 && y < 6) {
		int select_pos = y * 6 + x;			// 0~35
		if (m_table[select_pos] == 0)			// 이미 사라진 카드(예외처리)
			return;
		
		if (m_first_pos == -1) {
			m_first_pos = select_pos;			// 첫번째 카드 선택
		}
		else {
			if (m_first_pos == select_pos)				// 같은 위치의 카드일때(예외처리)
				return;

			// 첫번째 카드 선택된 상태
			if (m_table[m_first_pos] == m_table[select_pos]) {				// 카드가 같다면 0을 넣어 사라지는 효과를 준다.
				m_table[m_first_pos] = m_table[select_pos] = 0;
				Invalidate();
				m_find_count++;
				if (m_find_count == 18) {				// 게임 종료
					EndOfGame(L"승리!");
				}
			}	else {
				m_view_flag = 2;				// 2로 바꿔서 
				SetTimer(2, 1000, NULL);			// 2번타이머 : 1초
			}
			m_first_pos = -1;
		}

		CClientDC dc(this);
		int card_index = m_table[select_pos];
		m_card_image[card_index].Draw(dc, (select_pos%6)*36, select_pos/6*56);
	}


	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCBasic208PairCardDlg::OnBnClickedHintBtn()
{
	// TODO: Add your control notification handler code here
	int num = GetDlgItemInt(IDC_HINT_BTN);
	if (num > 0) {
		SetDlgItemInt(IDC_HINT_BTN, num - 1);
		m_view_flag = 1;				// 앞면 플래그
		Invalidate();
		SetTimer(1, 3000, NULL);
	}
}
