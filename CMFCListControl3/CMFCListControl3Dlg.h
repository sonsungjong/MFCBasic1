#pragma once
#define MAX_COLUMN_COUNT				7
#define MAX_ROW_COUNT						35

class MyListCtrl : public CMFCListCtrl
{
public:
	// 정렬 기준 초기화
	virtual void Sort(int iColumn, BOOL bAscending = TRUE, BOOL bAdd = FALSE)
	{
		for (int i = 0; i < MAX_ROW_COUNT; i++) {
			SetItemData(i, i);
		}
		CMFCListCtrl::Sort(iColumn, bAscending, bAdd);
	}

	// 헤더컨트롤을 선택했을 때 자동으로 호출되는 메서드 재정의
	virtual int OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn)
	{
		int result = 0;
		CString str1, str2;

		if (lParam1 < lParam2) {
			str1 = GetItemText(lParam1, iColumn);
			str2 = GetItemText(lParam2, iColumn);
		}
		else {
			str2 = GetItemText(lParam1, iColumn);
			str1 = GetItemText(lParam2, iColumn);
		}

		// 1번 문자열, 5번 실수, 나머지는 정수
		// 문자를 비교할 때는 반환값이 다르기 때문에 주의
		if (iColumn == 1)				// 문자열 컬럼 번호
		{
			//문자열 컬럼 비교
			result = wcscmp(str1, str2);				// 문자열 비교
		}
		else if (iColumn == 5)				// 실수 컬럼 비교
		{
			// 실수 컬럼 비교
			result = (_wtof(str1) < _wtof(str2)) ? -1 : 1;
		}
		else
		{
			// 정수 컬럼 비교
			result = (_wtoi(str1) < _wtoi(str2)) ? -1 : 1;
		}
		return result;
	}


	// 각 셀의 텍스트 색상을 결정
	virtual COLORREF OnGetCellTextColor(int nRow, int nColumn)
	{
		if (nColumn == 6)
		{
			// 1~5등은 어두운 녹색글자, 31~35등은 빨간글자
			int rank = _wtoi(GetItemText(nRow, nColumn));
			if (rank <= 5) {
				return RGB(0, 128, 0);
			}
			else if (rank >= 31) {
				return RGB(255, 0, 0);
			}
		}
		return CMFCListCtrl::OnGetCellTextColor(nRow, nColumn);				// 기본글자색
	}

	// 각 셀의 폰트 지정
	virtual HFONT OnGetCellFont(int nRow, int nColumn, DWORD dwData = 0)
	{
		HFONT mh_font = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("맑은 고딕"));
		if (nColumn == 6)
		{
			// 1~5등과 31~35등은 글꼴 변경
			int rank = _wtoi(GetItemText(nRow, nColumn));
			if (rank <= 5 || rank >= 31) {
				return afxGlobalData.fontDefaultGUIBold;				// MFC볼드체 (또는 변수로 폰트를 만들어 return 해도됨)
			}
		}
		
		return mh_font;				// HFONT 또는 NULL
	}

	// 각 셀의 배경색을 결정
	virtual COLORREF OnGetCellBkColor(int nRow, int nColumn)
	{
		// 6번째 컬럼에 대해서 색상 적용
		if (nColumn == 6) {
			// 1~5등은 노란색, 31~35등은 분홍색
			int rank = _wtoi(GetItemText(nRow, nColumn));
			if (rank <= 5) {
				return RGB(255, 255, 100);				// 노란색
			}
			else if (rank >= 31) {
				return RGB(255, 100, 255);				// 분홍색
			}
		}
		return CMFCListCtrl::OnGetCellBkColor(nRow, nColumn);				// 기본배경색
	}
};

class CCMFCListControl3Dlg : public CDialogEx
{
// Construction
public:
	CCMFCListControl3Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMFCLISTCONTROL3_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedStartBtn();
	afx_msg void OnBnClickedStopBtn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	MyListCtrl m_score_list;
	afx_msg void OnDestroy();
};
