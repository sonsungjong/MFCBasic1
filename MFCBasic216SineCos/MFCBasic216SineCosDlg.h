
// MFCBasic216SineCosDlg.h : header file
//

#pragma once
#define PI					3.141592

// CMFCBasic216SineCosDlg dialog
class CMFCBasic216SineCosDlg : public CDialogEx
{
protected:
	CImage m_image;
	CDC m_image_dc;

	CRect m_rect;
	CPoint m_center_pos;

	CPen m_grid_pen, m_sine_pen, m_cos_pen, m_circle_pen;
	CBrush m_red_brush, m_green_brush, m_yellow_brush;

	int m_step = 1;
	int m_sin_x, m_sin_y, m_cos_x, m_cos_y;

// Construction
public:
	CMFCBasic216SineCosDlg(CWnd* pParent = nullptr);	// standard constructor
	void ShowGrid();
	void ShowSine();
	void ShowCos();
	void ShowYCos();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC216SINECOS_DIALOG };
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};
