#pragma once

// 표의 시작위치를 정한다
#define GRID_X_POSITION						10
#define GRID_Y_POSITION						36

// 각 셀의 폭과 높이
#define GRID_WIDTH							100
#define GRID_HEIGHT						26

// 그리드의 갯수를 정한다
#define MAX_GRID_X_COUNT					5
#define MAX_GRID_Y_COUNT					3

// CGridTableDlg dialog
class CGridTableDlg : public CDialogEx
{
private:
	// 그리드 정보를 저장할 변수
	TCHAR* mp_edit_data[MAX_GRID_Y_COUNT][MAX_GRID_X_COUNT];

	// Edit 컨트롤을 생성했을 때 사용할 폰트
	CFont m_font;
	// 더블 클릭으로 생성한 에디트 컨트롤의 주소를 기억할 변수
	CEdit* mp_modify_edit;
	// 현재 선택된 그리드 항목의 위치값을 저장할 변수
	int m_select_x;
	int m_select_y;

// Construction
public:
	CGridTableDlg(CWnd* pParent = nullptr);	// standard constructor

	// 클릭한 위치에 있는 셀의 정보를 얻음
	char GetEditObject(int* ap_select_x, int* ap_select_y, CPoint* ap_point);
	// 에디트 컨트롤 생성 함수
	void CreateEdit(CRect* ap_rect);
	// 에디트 컨트롤을 삭제하는 함수
	void DeleteEdit();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRIDTABLE_DIALOG };
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
};
