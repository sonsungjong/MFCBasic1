
// MFCL104ListBoxOwnerDrawLibDlg.h : header file
//

#pragma once
#include "SJ_ListBox.h"

// CMFCL104ListBoxOwnerDrawLibDlg dialog
class CMFCL104ListBoxOwnerDrawLibDlg : public CDialogEx
{
private:
	SJ_ListBox m_data_list;
	//CListBox m_data_list;

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

	//afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
