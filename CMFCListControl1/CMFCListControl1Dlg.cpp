
// CMFCListControl1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "CMFCListControl1.h"
#include "CMFCListControl1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCMFCListControl1Dlg::CCMFCListControl1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CMFCLISTCONTROL1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCMFCListControl1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCORE_LIST, m_score_list);
}

BEGIN_MESSAGE_MAP(CCMFCListControl1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCMFCListControl1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CCMFCListControl1Dlg::OnBnClickedCancel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCMFCListControl1Dlg message handlers

BOOL CCMFCListControl1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// 컬럼 명
	const wchar_t* p_column_name[MAX_COLUMN_COUNT] = {
		L"학번", L"이름", L"국어", L"수학", L"영어", L"평균", L"석차"
	};
	// 컬럼 크기
	int column_width_list[MAX_COLUMN_COUNT] = { 70, 90, 60, 60, 60, 60, 60 };
	// 리스트 컨트롤에 컬럼 추가
	for (int i = 0; i < MAX_COLUMN_COUNT; i++) {
		m_score_list.InsertColumn(i, p_column_name[i], LVCFMT_CENTER, column_width_list[i]);
	}

	// 이름
	const wchar_t* p_name_list[MAX_ROW_COUNT] = {
		L"한민준", L"김서준", L"이도윤", L"서예준", L"이시우", L"박하준", L"강주원",
		L"김지호", L"송지후", L"서준우", L"이준서", L"이건우", L"김도현", L"김현우",
		L"이지훈", L"박우진", L"김선우", L"이서진", L"박유준", L"김연우", L"박민재",
		L"박현준", L"이은우", L"민정우", L"윤시윤", L"박승우", L"이승현", L"김준혁",
		L"서지환", L"백윤우", L"도승민", L"황유찬", L"강지우", L"도이준", L"박민성",
	};

	wchar_t student_number[7] = { 0, };				// 학번
	wchar_t score_value[8] = { 0, };

	// 난수 기준값
	srand(GetTickCount64());
	int value = 0, total = 0, ranking_list[MAX_ROW_COUNT] = { 1, };
	double average_list[MAX_ROW_COUNT] = { 0.0, };

	for (int i = 0; i < MAX_ROW_COUNT; i++) {
		memset(student_number, 0, sizeof(student_number));
		swprintf_s(student_number, 7, L"%06d", 230301 + i);						// 학번
		m_score_list.InsertItem(i, student_number);				// 0번 항목 (학번)
		m_score_list.SetItemText(i, 1, p_name_list[i]);				// i번째 열에 1번 항목으로 추가 (이름)

		// 난수(30~100)으로 국어,수학,영어 점수 생성 + 총점계산
		total = 0;
		for (int j = 2; j <= 4; j++) {
			value = 30 + rand() % 71;				// 30~100
			total += value;
			memset(score_value, 0, sizeof(score_value));
			swprintf_s(score_value, 8, L"%d", value);
			m_score_list.SetItemText(i, j, score_value);
		}

		// 평균 계산
		average_list[i] = total / 3.0;
		ranking_list[i] = 1;
		memset(score_value, 0, sizeof(score_value));
		swprintf_s(score_value, 8, L"%.2f", average_list[i]);
		m_score_list.SetItemText(i, 5, score_value);
	}

	// 평균으로 석차 계산 (sorting)
	for (int i = 0; i < MAX_ROW_COUNT; i++) {
		for (int sub_i = i + 1; sub_i < MAX_ROW_COUNT; sub_i++) {
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

	// 석차값 대입
	for (int i = 0; i < MAX_ROW_COUNT; i++) {
		memset(score_value, 0, sizeof(score_value));
		swprintf_s(score_value, 8, L"%d", ranking_list[i]);
		m_score_list.SetItemText(i, 6, score_value);				// 6번째 컬럼으로 석차값 추가
	}

	// CMFCListControl 속성추가
	m_score_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	m_score_list.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_score_list.EnableMarkSortedColumn();				// 선택 컬럼 색상표시 (기본값 : 밝은 회색)
	m_score_list.SetSortColumn(0);							// 0번째 컬럼 기준으로 오름차순 정렬

	return TRUE;
}

void CCMFCListControl1Dlg::OnPaint()
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
HCURSOR CCMFCListControl1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCMFCListControl1Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//CDialogEx::OnOK();
}


void CCMFCListControl1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CCMFCListControl1Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here

}
