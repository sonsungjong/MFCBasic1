#pragma once
#define MAX_COLUMN_COUNT				7
#define MAX_ROW_COUNT						35

class MyListCtrl : public CMFCListCtrl
{
public:
	// ���� ���� �ʱ�ȭ
	virtual void Sort(int iColumn, BOOL bAscending = TRUE, BOOL bAdd = FALSE)
	{
		for (int i = 0; i < MAX_ROW_COUNT; i++) {
			SetItemData(i, i);
		}
		CMFCListCtrl::Sort(iColumn, bAscending, bAdd);
	}

	// �����Ʈ���� �������� �� �ڵ����� ȣ��Ǵ� �޼��� ������
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

		// 1�� ���ڿ�, 5�� �Ǽ�, �������� ����
		// ���ڸ� ���� ���� ��ȯ���� �ٸ��� ������ ����
		if (iColumn == 1)				// ���ڿ� �÷� ��ȣ
		{
			//���ڿ� �÷� ��
			result = wcscmp(str1, str2);				// ���ڿ� ��
		}
		else if (iColumn == 5)				// �Ǽ� �÷� ��
		{
			// �Ǽ� �÷� ��
			result = (_wtof(str1) < _wtof(str2)) ? -1 : 1;
		}
		else
		{
			// ���� �÷� ��
			result = (_wtoi(str1) < _wtoi(str2)) ? -1 : 1;
		}
		return result;
	}


	// �� ���� �ؽ�Ʈ ������ ����
	virtual COLORREF OnGetCellTextColor(int nRow, int nColumn)
	{
		if (nColumn == 6)
		{
			// 1~5���� ��ο� �������, 31~35���� ��������
			int rank = _wtoi(GetItemText(nRow, nColumn));
			if (rank <= 5) {
				return RGB(0, 128, 0);
			}
			else if (rank >= 31) {
				return RGB(255, 0, 0);
			}
		}
		return CMFCListCtrl::OnGetCellTextColor(nRow, nColumn);				// �⺻���ڻ�
	}

	// �� ���� ��Ʈ ����
	virtual HFONT OnGetCellFont(int nRow, int nColumn, DWORD dwData = 0)
	{
		HFONT mh_font = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("���� ���"));
		if (nColumn == 6)
		{
			// 1~5��� 31~35���� �۲� ����
			int rank = _wtoi(GetItemText(nRow, nColumn));
			if (rank <= 5 || rank >= 31) {
				return afxGlobalData.fontDefaultGUIBold;				// MFC����ü (�Ǵ� ������ ��Ʈ�� ����� return �ص���)
			}
		}
		
		return mh_font;				// HFONT �Ǵ� NULL
	}

	// �� ���� ������ ����
	virtual COLORREF OnGetCellBkColor(int nRow, int nColumn)
	{
		// 6��° �÷��� ���ؼ� ���� ����
		if (nColumn == 6) {
			// 1~5���� �����, 31~35���� ��ȫ��
			int rank = _wtoi(GetItemText(nRow, nColumn));
			if (rank <= 5) {
				return RGB(255, 255, 100);				// �����
			}
			else if (rank >= 31) {
				return RGB(255, 100, 255);				// ��ȫ��
			}
		}
		return CMFCListCtrl::OnGetCellBkColor(nRow, nColumn);				// �⺻����
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
