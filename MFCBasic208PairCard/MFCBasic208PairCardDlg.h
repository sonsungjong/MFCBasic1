
// MFCBasic208PairCardDlg.h : header file
//

#pragma once


// CMFCBasic208PairCardDlg dialog
class CMFCBasic208PairCardDlg : public CDialogEx
{
private:
	CImage m_card_image[19];			// 0:µÞ¸é, 1~18: Ä«µå
	char m_table[36];			// 18*2
	char m_view_flag = 1;

// Construction
public:
	CMFCBasic208PairCardDlg(CWnd* pParent = nullptr);	// standard constructor

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
};
