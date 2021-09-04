
// MFCBasic121GradationDlg.h : header file
//

#pragma once


// CMFCBasic121GradationDlg dialog
class CMFCBasic121GradationDlg : public CDialogEx
{
// Construction
public:
	CMFCBasic121GradationDlg(CWnd* pParent = nullptr);	// standard constructor
	void GradationRect(CDC* dc, int x1, int y1, int x2, int y2, COLORREF start_color, COLORREF end_color, int orientation);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC121GRADATION_DIALOG };
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
};
