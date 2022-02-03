
// MFCL110PriceCalculationDlg.h : header file
//

#pragma once
#define MAX_ITEM_COUNT			8

// CMFCL110PriceCalculationDlg dialog
class CMFCL110PriceCalculationDlg : public CDialogEx
{
// Construction
public:
	CMFCL110PriceCalculationDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL110PRICECALCULATION_DIALOG };
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

	// ListBox에 OwnerDraw와 HasString을 켜줘야함
	CCheckListBox m_item_list;
public:
	afx_msg void OnLbnSelchangeItemList();
};
