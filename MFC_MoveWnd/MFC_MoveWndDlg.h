
// MFC_MoveWndDlg.h : header file
//

#pragma once


// CMFCMoveWndDlg dialog
class CMFCMoveWndDlg : public CDialogEx
{
private:
	// 0 : Å¬¸¯¾ÈµÊ, 1 : Å¬¸¯µÊ
	unsigned char m_is_clicked = 0;
	CPoint m_prev_point;

// Construction
public:
	CMFCMoveWndDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_MOVEWND_DIALOG };
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
