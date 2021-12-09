
// MFCL103ListBoxOwnerDrawDlg.h : header file
//

#pragma once


// CMFCL103ListBoxOwnerDrawDlg dialog
class CMFCL103ListBoxOwnerDrawDlg : public CDialogEx
{
// Construction
public:
	CMFCL103ListBoxOwnerDrawDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL103LISTBOXOWNERDRAW_DIALOG };
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
	virtual void OnOK();
	virtual void OnCancel();
};
