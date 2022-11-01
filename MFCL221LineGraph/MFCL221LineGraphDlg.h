
// MFCL221LineGraphDlg.h : header file
//

#pragma once
#include "LineGraph.h"

// CMFCL221LineGraphDlg dialog
class CMFCL221LineGraphDlg : public CDialogEx
{
	LineGraph m_graph;

// Construction
public:
	CMFCL221LineGraphDlg(CWnd* pParent = nullptr);	// standard constructor


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL221LINEGRAPH_DIALOG };
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
};
