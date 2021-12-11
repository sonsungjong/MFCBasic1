
// MFCL104ListBoxOwnerDrawLibDlg.h : header file
//

#pragma once


// CMFCL104ListBoxOwnerDrawLibDlg dialog
class CMFCL104ListBoxOwnerDrawLibDlg : public CDialogEx
{
// Construction
public:
	CMFCL104ListBoxOwnerDrawLibDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL104LISTBOXOWNERDRAWLIB_DIALOG };
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
	CListBox m_data_list;
};
