
// MFCBasic122TimerDlg.h : header file
//

#pragma once


// CMFCBasic122TimerDlg dialog
class CMFCBasic122TimerDlg : public CDialogEx
{
protected:
	char timer_flag = 0;
// Construction
public:
	CMFCBasic122TimerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC122TIMER_DIALOG };
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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedGetTime();
	
	afx_msg void OnBnClickedMfcTime();
	afx_msg void OnBnClickedSystemTime();
	afx_msg void OnBnClickedStartTimer();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedStopTimer();
	afx_msg void OnBnClickedCallbackTime();
};
