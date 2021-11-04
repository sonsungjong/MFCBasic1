
// MFCBasic217CircleDlg.h : header file
//

#pragma once


// CMFCBasic217CircleDlg dialog
class CMFCBasic217CircleDlg : public CDialogEx
{
protected:
	CImage m_image;
	CDC m_image_dc;

	CRect m_rect;
	CPoint m_center;

	CPen m_grid_pen, m_green_pen, m_gray_pen;
	CBrush m_green_brush, m_gray_brush;
	int m_degree = 0, m_sub_degree = 75, m_grid_flag = 0;

// Construction
public:
	CMFCBasic217CircleDlg(CWnd* pParent = nullptr);	// standard constructor
	void ShowGrid();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC217CIRCLE_DIALOG };
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
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
