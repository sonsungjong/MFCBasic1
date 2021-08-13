
// MFCBasic109ListControlDlg.h : header file
//

#pragma once


// CMFCBasic109ListControlDlg dialog
class CMFCBasic109ListControlDlg : public CDialogEx
{
// Construction
public:
	CMFCBasic109ListControlDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC109LISTCONTROL_DIALOG };
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
	afx_msg void OnBnClickedAddBtn();
	CListCtrl m_data_list;
	CEdit m_name_edit_ctrl;
	afx_msg void OnLvnItemchangedDataList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedModifyBtn();
};
