
// MFCL201MenuDlg.h : header file
//

#pragma once


// CMFCL201MenuDlg dialog
class CMFCL201MenuDlg : public CDialogEx
{
private:
	int m_start_flag = 0;

// Construction
public:
	CMFCL201MenuDlg(CWnd* pParent = nullptr);	// standard constructor
	void UpdateMenu();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL201MENU_DIALOG };
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
	afx_msg void OnStartCmd();
	afx_msg void OnExitCmd();
};
