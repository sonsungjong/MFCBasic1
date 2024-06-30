
// MFCS001CTaskDialogDlg.h : header file
//

#pragma once


// CMFCS001CTaskDialogDlg dialog
class CMFCS001CTaskDialogDlg : public CDialogEx
{
// Construction
public:
	CMFCS001CTaskDialogDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCS001CTASKDIALOG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CListBox* mp_result_list;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
