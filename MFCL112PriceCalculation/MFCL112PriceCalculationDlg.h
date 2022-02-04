
// MFCL112PriceCalculationDlg.h : header file
//

#pragma once
#include "MyListBox.h"

#define MAX_COUNT				8
#define TEXT_HEIGHT			24

// CMFCL112PriceCalculationDlg dialog
class CMFCL112PriceCalculationDlg : public CDialogEx
{
// Construction
public:
	CMFCL112PriceCalculationDlg(CWnd* pParent = nullptr);	// standard constructor
	void CalcTotalPrice();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL112PRICECALCULATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	MyListBox m_item_list;
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	// ListBox¸¦ OwnerDraw¿Í HasString => Fixed, TRUE
	//CCheckListBox m_item_list;
	CSpinButtonCtrl m_count_spin;
	CRect m_spin_rect;
	CFont m_font;

public:
	afx_msg void OnLbnSelchangeItemList();
	afx_msg void OnDeltaposCountSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
};
