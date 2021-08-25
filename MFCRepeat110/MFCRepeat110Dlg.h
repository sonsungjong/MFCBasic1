
// MFCRepeat110Dlg.h : header file
//

#pragma once


// CMFCRepeat110Dlg dialog
class CMFCRepeat110Dlg : public CDialogEx
{
protected:
	CRect m_rect;
	int m_clicked_flag = m_clicked_flag ^ m_clicked_flag;
	CPoint m_prev_pos;

// Construction
public:
	CMFCRepeat110Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCREPEAT110_DIALOG };
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
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
