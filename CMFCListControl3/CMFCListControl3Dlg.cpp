#include "pch.h"
#include "framework.h"
#include "CMFCListControl3.h"
#include "CMFCListControl3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCMFCListControl3Dlg::CCMFCListControl3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CMFCLISTCONTROL3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCMFCListControl3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCORE_LIST, m_score_list);				// 리소스와 멤버변수 연결
}

BEGIN_MESSAGE_MAP(CCMFCListControl3Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCMFCListControl3Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCMFCListControl3Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_START_BTN, &CCMFCListControl3Dlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_STOP_BTN, &CCMFCListControl3Dlg::OnBnClickedStopBtn)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


BOOL CCMFCListControl3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// 컬럼명
	const TCHAR* p_column_name[MAX_COLUMN_COUNT] = {
		L"학번", L"이름", L"국어", L"수학", L"영어", L"평균", L"석차"
	};

	// 컬럼 크기
	int column_width_list[MAX_COLUMN_COUNT] = { 70, 90, 60, 60, 60, 60, 60 };

	// 컬럼 생성 (InsertColumn)
	for (int i = 0; i < MAX_COLUMN_COUNT; i++) {
		m_score_list.InsertColumn(i, p_column_name[i], LVCFMT_CENTER, column_width_list[i]);
	}

	// 학번
	TCHAR student_number[7] = { 0, };

	// 이름
	const TCHAR* p_name_list[MAX_ROW_COUNT] = {
		L"한민준", L"김서준", L"이도윤", L"서예준", L"이시우", L"박하준", L"강주원",
		L"김지호", L"송지후", L"서준우", L"이준서", L"이건우", L"김도현", L"김현우",
		L"이지훈", L"박우진", L"김선우", L"이서진", L"박유준", L"김연우", L"박민재",
		L"박현준", L"이은우", L"민정우", L"윤시윤", L"박승우", L"이승현", L"김준혁",
		L"서지환", L"백윤우", L"도승민", L"황유찬", L"강지우", L"도이준", L"박민성",
	};

	// 점수
	TCHAR score_value[8] = { 0, };


	// 점수 계산 (국어, 수학, 영어, 총점, 평균, 랭킹)
	srand(GetTickCount64());			// 난수 기준
	int value = 0, total = 0, ranking_list[MAX_ROW_COUNT] = { 0, };
	double average_list[MAX_ROW_COUNT] = { 0.0, };

	// 난수 (30~100)
	for (int i = 0; i < MAX_ROW_COUNT; i++) {
		memset(student_number, 0, sizeof(student_number));
		swprintf_s(student_number, 7, L"%06d", 230301 + i);
		m_score_list.InsertItem(i, student_number);				// 행 생성 (학번)
		m_score_list.SetItemText(i, 1, p_name_list[i]);			// 이름 추가

		// 점수 추가
		total = 0;
		for (int sub_i = 2; sub_i < 5; ++sub_i) {
			value = 30 + rand() % 71;
			total += value;
			memset(score_value, 0, sizeof(score_value));
			swprintf_s(score_value, 8, L"%d", value);
			m_score_list.SetItemText(i, sub_i, score_value);
		}

		average_list[i] = total / 3.0;
		ranking_list[i] = 1;						// 기본값을 1로
		memset(score_value, 0, sizeof(score_value));
		swprintf_s(score_value, 8, L"%.2f", average_list[i]);
		m_score_list.SetItemText(i, 5, score_value);
	}

	// 평균으로 랭킹값 저장
	for (int i = 0; i < MAX_ROW_COUNT; ++i) {
		for (int sub_i = i + 1; sub_i < MAX_ROW_COUNT; ++sub_i) {
			if (average_list[i] != average_list[sub_i]) {
				if (average_list[i] > average_list[sub_i]) {
					ranking_list[sub_i]++;
				}
				else {
					ranking_list[i]++;
				}
			}
		}
	}

	// 랭킹 추가
	for (int i = 0; i < MAX_ROW_COUNT; ++i) {
		memset(score_value, 0, sizeof(score_value));
		swprintf_s(score_value, 8, L"%d", ranking_list[i]);
		m_score_list.SetItemText(i, 6, score_value);
	}

	// CMFCListControl 속성
	m_score_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);				 // report 속성
	m_score_list.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER);			// 행기준선택 및 그리드 속성 + 더블버퍼링 추가
	m_score_list.EnableMarkSortedColumn();					// 선택한 컬럼 색상표시
	m_score_list.SetSortColumn(0);				// 0번째 컬럼 기준으로 오름차순
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCMFCListControl3Dlg::OnPaint()
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
HCURSOR CCMFCListControl3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCMFCListControl3Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CCMFCListControl3Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CCMFCListControl3Dlg::OnBnClickedStartBtn()
{
	SetTimer(1, 100, NULL);
}


void CCMFCListControl3Dlg::OnBnClickedStopBtn()
{
	KillTimer(1);
}


void CCMFCListControl3Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) {
		// 갱신하는 부분만 새로 SetItemText

		// 점수
		TCHAR score_value[8] = { 0, };

		// 점수 계산 (국어, 수학, 영어, 총점, 평균, 랭킹)
		srand(GetTickCount64());			// 난수 기준
		int value = 0, total = 0, ranking_list[MAX_ROW_COUNT] = { 0, };
		double average_list[MAX_ROW_COUNT] = { 0.0, };

		// 점수를 난수로 (30~100)
		for (int i = 0; i < MAX_ROW_COUNT; i++) {
			total = 0;
			for (int sub_i = 2; sub_i < 5; ++sub_i) {
				value = 30 + rand() % 71;
				total += value;
				memset(score_value, 0, sizeof(score_value));
				swprintf_s(score_value, 8, L"%d", value);
				m_score_list.SetItemText(i, sub_i, score_value);				// 점수 덮어쓰기
			}

			average_list[i] = total / 3.0;
			ranking_list[i] = 1;						// 기본값을 1로
			memset(score_value, 0, sizeof(score_value));
			swprintf_s(score_value, 8, L"%.2f", average_list[i]);
			m_score_list.SetItemText(i, 5, score_value);				// 평균 덮어쓰기
		}

		// 평균으로 랭킹값 저장
		for (int i = 0; i < MAX_ROW_COUNT; ++i) {
			for (int sub_i = i + 1; sub_i < MAX_ROW_COUNT; ++sub_i) {
				if (average_list[i] != average_list[sub_i]) {
					if (average_list[i] > average_list[sub_i]) {
						ranking_list[sub_i]++;
					}
					else {
						ranking_list[i]++;
					}
				}
			}
		}

		// 랭킹 추가
		for (int i = 0; i < MAX_ROW_COUNT; ++i) {
			memset(score_value, 0, sizeof(score_value));
			swprintf_s(score_value, 8, L"%d", ranking_list[i]);
			m_score_list.SetItemText(i, 6, score_value);				// 랭킹 덮어쓰기
		}

	}
	else {
		CDialogEx::OnTimer(nIDEvent);
	}
}


void CCMFCListControl3Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	KillTimer(1);
}
