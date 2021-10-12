
// MFCBasic206DotEditorDlg.h : header file
//

#pragma once
#define X_COUNT				30
#define Y_COUNT				30
#define RECT_INTERVAL		20

// CMFCBasic206DotEditorDlg dialog
class CMFCBasic206DotEditorDlg : public CDialogEx
{
private:
	COLORREF m_dot_color[Y_COUNT][X_COUNT];
	COLORREF m_left_color, m_right_color;
	CPen m_grid_pen;
	CRect m_left_rect, m_right_rect;
// Construction
public:
	CMFCBasic206DotEditorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC206DOTEDITOR_DIALOG };
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
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedLeftColorBtn();
	afx_msg void OnBnClickedRightColorBtn();
};
