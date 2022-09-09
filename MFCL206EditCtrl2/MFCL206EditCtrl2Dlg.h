
// MFCL206EditCtrl2Dlg.h : header file
//

#pragma once
#include "SJ_Edit.h"

// CMFCL206EditCtrl2Dlg dialog
class CMFCL206EditCtrl2Dlg : public CDialogEx
{
private:
	SJ_Edit m_my_edit[6];

// Construction
public:
	CMFCL206EditCtrl2Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL206EDITCTRL2_DIALOG };
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
