
// TableCtrlDlg.h : header file
//

#pragma once
#define GRID_X_POS				10					// 시작위치x
#define GRID_Y_POS				82					// 시작위치y
#define GRID_WIDTH				100				// 가로크기
#define GRID_HEIGHT			26					// 세로크기

// CTableCtrlDlg dialog
class CTableCtrlDlg : public CDialogEx
{
private:
	unsigned int m_h_count, m_v_count;
	TCHAR*** mp_edit_data;

	CFont m_font;				// Edit컨트롤의 폰트
	CEdit* mp_modify_edit;					// 더블클릭으로 생성한 에디트컨트롤의 주소
	int m_select_x, m_select_y;
// Construction
public:
	CTableCtrlDlg(CWnd* pParent = nullptr);	// standard constructor
	void AllocStringData(int a_h_count, int a_v_count);
	void FreeStringData();

	char GetEditObject(int* ap_select_x, int* ap_select_y, CPoint* ap_point);
	void CreateEdit(CRect* ap_rect);
	void DeleteEdit();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABLECTRL_DIALOG };
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
	afx_msg LRESULT OnDeleteEdit(WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedApplyBtn();
};
