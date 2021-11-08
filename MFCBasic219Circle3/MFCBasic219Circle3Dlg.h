
// MFCBasic219Circle3Dlg.h : header file
//

#pragma once
#define PI 3.141592


// CMFCBasic219Circle3Dlg dialog
class CMFCBasic219Circle3Dlg : public CDialogEx
{
protected:
	CImage m_image;
	CDC m_image_dc;

	CPen m_green_pen;
	CBrush m_green_brush;

	CRect m_rect;
	
	char m_is_clicked = 0;
	CPoint m_start_pos;

// Construction
public:
	CMFCBasic219Circle3Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC219CIRCLE3_DIALOG };
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
