
// MFCBasic201FindWindowExDlg.h : header file
//

#pragma once


// CMFCBasic201FindWindowExDlg dialog
class CMFCBasic201FindWindowExDlg : public CDialogEx
{
// Construction
public:
	CMFCBasic201FindWindowExDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC201FINDWINDOWEX_DIALOG };
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
	afx_msg void OnBnClickedFindEdit();
};
