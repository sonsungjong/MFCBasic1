
// MFCBasic107CommandRangeDlg.h : header file
//

#pragma once


// CMFCBasic107CommandRangeDlg dialog
class CMFCBasic107CommandRangeDlg : public CDialogEx
{
// Construction
public:
	CMFCBasic107CommandRangeDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC107COMMANDRANGE_DIALOG };
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void OnSetNumFunc(unsigned int a_ctrl_id);		// On_Command_Range 가 구분해주는 아이디값을 받음
};
