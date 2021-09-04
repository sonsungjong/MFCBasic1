
// MFCBasic119CalenderDlg.h : header file
//

#pragma once


// CMFCBasic119CalenderDlg dialog
class CMFCBasic119CalenderDlg : public CDialogEx
{
protected:
	CFont font;
// Construction
public:
	CMFCBasic119CalenderDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC119CALENDER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMonthCalCtrl calendar;
	afx_msg void OnMcnSelchangeCalendar(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSet();
	CStatic date_static;
	void ShowNote();
};
