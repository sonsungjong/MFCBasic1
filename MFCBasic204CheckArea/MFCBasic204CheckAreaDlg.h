
// MFCBasic204CheckAreaDlg.h : header file
//

#pragma once
#define BOX_COUNT		18

// CMFCBasic204CheckAreaDlg dialog
class CMFCBasic204CheckAreaDlg : public CDialogEx
{
protected:
	CBrush m_brush, m_select_brush;
	CBrush* mp_old_brush;
	CPen m_pen, m_select_pen;
	CPen* mp_old_pen;

	int m_idx_x = -1;
	int m_idx_y = -1;

// Construction
public:
	CMFCBasic204CheckAreaDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC204CHECKAREA_DIALOG };
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
