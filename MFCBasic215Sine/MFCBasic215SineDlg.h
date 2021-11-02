
// MFCBasic215SineDlg.h : header file
//

#pragma once

// x축은 같지만 y축은 반대
// CMFCBasic215SineDlg dialog
class CMFCBasic215SineDlg : public CDialogEx
{
private:
	CImage m_image;				// 메모리DC
	CDC m_image_dc;

	CRect m_rect;
	CPoint m_center;					// 중심좌표를 기억할 포인트
	
	CPen m_grid_pen, m_sine_pen;
	CBrush m_red_brush;

	int m_step = 1;
// Construction
public:
	CMFCBasic215SineDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC215SINE_DIALOG };
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
};
