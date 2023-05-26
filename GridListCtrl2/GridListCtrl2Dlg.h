
// GridListCtrl2Dlg.h : header file
//

#pragma once
#include "MY_GridListCtrl.h"

// CGridListCtrl2Dlg dialog
class CGridListCtrl2Dlg : public CDialogEx
{
// Construction
public:
	CGridListCtrl2Dlg(CWnd* pParent = nullptr);	// standard constructor

private:
	MY_GridListCtrl grid_view;
	int m_test = 0;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRIDLISTCTRL2_DIALOG };
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
	afx_msg void OnBnClickedSetBtn();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
};
