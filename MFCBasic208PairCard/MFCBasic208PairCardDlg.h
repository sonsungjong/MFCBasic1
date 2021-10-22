
// MFCBasic208PairCardDlg.h : header file
//

#pragma once


// CMFCBasic208PairCardDlg dialog
class CMFCBasic208PairCardDlg : public CDialogEx
{
private:
	CImage m_card_image[19];			// 0:µﬁ∏È, 1~18: æ’∏È
	char m_table[36];			// 18*2
	char m_view_flag = 1;
	char m_first_pos = -1;				// -1:º±≈√æ»µ , 0~35
	char m_find_count = 0;

// Construction
public:
	CMFCBasic208PairCardDlg(CWnd* pParent = nullptr);	// standard constructor

	void EndOfGame(const wchar_t* ap_msg);
	void StartGame();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC208PAIRCARD_DIALOG };
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedHintBtn();
	CProgressCtrl m_time_progress;
};
