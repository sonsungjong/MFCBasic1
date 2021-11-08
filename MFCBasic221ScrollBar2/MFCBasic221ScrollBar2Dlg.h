
// MFCBasic221ScrollBar2Dlg.h : header file
//

#pragma once


// CMFCBasic221ScrollBar2Dlg dialog
class CMFCBasic221ScrollBar2Dlg : public CDialogEx
{
protected:
	CImage m_img;
	CRect m_rect;

// Construction
public:
	CMFCBasic221ScrollBar2Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC221SCROLLBAR2_DIALOG };
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
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButton1();
};
