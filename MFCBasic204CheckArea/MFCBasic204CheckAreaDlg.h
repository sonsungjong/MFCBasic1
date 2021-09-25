
// MFCBasic204CheckAreaDlg.h : header file
//

#pragma once


// CMFCBasic204CheckAreaDlg dialog
class CMFCBasic204CheckAreaDlg : public CDialogEx
{
protected:
	CBrush m_brush, m_select_brush;
	CPen m_pen, m_select_pen;

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
};
