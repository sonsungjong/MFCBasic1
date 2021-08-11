
// MFCBasic108CalculatorsDlg.h : header file
//

#pragma once


// CMFCBasic108CalculatorsDlg dialog
class CMFCBasic108CalculatorsDlg : public CDialogEx
{
protected:
	CFont m_font;
	char m_op_flag = 0;			// 0: πÃº±≈√, 1:SUM, 2: SUB, 3:MUL, 4:DIV
	char m_reset_flag = 0;
	int m_remember_num = 0;

// Construction
public:
	CMFCBasic108CalculatorsDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC108CALCULATORS_DIALOG };
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
	void OnSetNumFunc(unsigned int a_ctrl_id);
	void OnProcessOpFunc(unsigned int a_ctrl_id);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedClearBtn();
	afx_msg void OnBnClickedOpEqualBtn();
	afx_msg void OnBnClickedBackBtn();
};
