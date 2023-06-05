#pragma once


// CWOLWakeOnLanDlg dialog
class CWOLWakeOnLanDlg : public CDialogEx
{
// Construction
public:
	CWOLWakeOnLanDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WOL_WAKEONLAN_DIALOG };
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
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedWakeBtn();
	afx_msg void OnBnClickedGetMacAddress();
	afx_msg void OnBnClickedGetIp();
};
