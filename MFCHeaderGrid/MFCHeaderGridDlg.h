
// MFCHeaderGridDlg.h : header file
//

#pragma once
#include "SimpleListBox.h"
#include "HeaderGrid.h"

// CMFCHeaderGridDlg dialog
class CMFCHeaderGridDlg : public CDialogEx
{
protected:
	SimpleListBox m_data_list;
	HeaderGrid m_header_grid;

// Construction
public:
	CMFCHeaderGridDlg(CWnd* pParent = nullptr);	// standard constructor
	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCHEADERGRID_DIALOG };
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
public:
	afx_msg void OnDestroy();
};
