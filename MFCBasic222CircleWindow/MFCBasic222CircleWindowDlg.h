
// MFCBasic222CircleWindowDlg.h : header file
//

#pragma once


// CMFCBasic222CircleWindowDlg dialog
class CMFCBasic222CircleWindowDlg : public CDialogEx
{
protected:
	CPoint m_prevPosition;
	char m_clickFlag = 0;

// Construction
public:
	CMFCBasic222CircleWindowDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC222CIRCLEWINDOW_DIALOG };
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
