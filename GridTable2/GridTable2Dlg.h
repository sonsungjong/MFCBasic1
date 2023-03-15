#pragma once

// 그리드의 시작 위치
#define GRID_X_POSITION					10
#define GRID_Y_POSITION					82

// 각 셀의 폭과 높이
#define GRID_WIDTH						100
#define GRID_HEIGHT					26

// CGridTable2Dlg dialog
class CGridTable2Dlg : public CDialogEx
{
private:
	// 그리드 항목의 갯수를 저장할 변수
	unsigned int m_h_count;
	unsigned int m_v_count;

	// 각 셀의 정보를 저장할 변수
	TCHAR*** mp_edit_data;

	// 에디트 컨트롤 폰트
	CFont m_font;
	// 더블클릭한 셀의 에디트컨트롤 주소
	CEdit* mp_modify_edit;
	// 선택된 셀의 위치값
	int m_select_x;
	int m_select_y;

// Construction
public:
	CGridTable2Dlg(CWnd* pParent = nullptr);	// standard constructor

	// 그리드에서 사용할 메모리 할당
	void AllocStringData(int a_h_count, int a_v_count);
	// 문자열 정보 제거
	void FreeStringData();

	// 클릭한 위치에 있는 셀의 정보를 얻음
	char GetEditObject(int* ap_select_x, int* ap_select_y, CPoint* ap_point);
	// 에디트 컨트롤 생성 함수
	void CreateEdit(CRect* ap_rect);
	// 에디트 컨트롤 삭제 함수
	void DeleteEdit();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRIDTABLE2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
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
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDeleteEdit();
	afx_msg void OnBnClickedApplyBtn();
};
