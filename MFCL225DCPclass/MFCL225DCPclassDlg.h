
// MFCL225DCPclassDlg.h : header file
//

#pragma once
#include "DCP.h"

// CMFCL225DCPclassDlg dialog
class CMFCL225DCPclassDlg : public CDialogEx
{
	DCP m_dcp;
// Construction
public:
	CMFCL225DCPclassDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL225DCPCLASS_DIALOG };
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
};
