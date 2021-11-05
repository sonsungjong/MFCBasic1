
// MFCBasic218Circle2Dlg.h : header file
//

#pragma once
#define PI					3.141592

// CMFCBasic218Circle2Dlg dialog
class CMFCBasic218Circle2Dlg : public CDialogEx
{
protected:
	CImage m_image;					// HDC
	CDC m_image_dc;					// HDC -> CDC

	CRect m_rect;
	CPoint m_center;

	CPen m_grid_pen, m_green_pen, m_yellow_pen;
	CBrush m_pie_brush;

// Construction
public:
	CMFCBasic218Circle2Dlg(CWnd* pParent = nullptr);	// standard constructor
	void ShowGrid();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC218CIRCLE2_DIALOG };
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
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
