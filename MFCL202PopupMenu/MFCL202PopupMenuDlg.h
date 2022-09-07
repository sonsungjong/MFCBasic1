
// MFCL202PopupMenuDlg.h : header file
//

#pragma once


// CMFCL202PopupMenuDlg dialog
class CMFCL202PopupMenuDlg : public CDialogEx
{
// Construction
public:
	CMFCL202PopupMenuDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL202POPUPMENU_DIALOG };
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
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMyOpen();
	afx_msg void OnMyClose();
};
