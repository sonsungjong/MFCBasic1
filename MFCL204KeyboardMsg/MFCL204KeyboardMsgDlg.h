
// MFCL204KeyboardMsgDlg.h : header file
//

#pragma once


// CMFCL204KeyboardMsgDlg dialog
class CMFCL204KeyboardMsgDlg : public CDialogEx
{
private:
	unsigned int m_start_flag;
	HACCEL m_acc_key;					// 리소스에서 Accelerator 추가
// Construction
public:
	CMFCL204KeyboardMsgDlg(CWnd* pParent = nullptr);	// standard constructor
	void UpdateMenu();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL204KEYBOARDMSG_DIALOG };
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
	afx_msg void OnBnClickedStartBtn();
	afx_msg void OnBnClickedStopBtn();
	
	afx_msg void OnExitMenu();
	afx_msg void OnStartMenu();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEditClearCmd();
};
