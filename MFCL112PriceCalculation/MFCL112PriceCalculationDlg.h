
// MFCL112PriceCalculationDlg.h : header file
//

#pragma once
#define MAX_COUNT				8
#define TEXT_HEIGHT			24

// CMFCL112PriceCalculationDlg dialog
class CMFCL112PriceCalculationDlg : public CDialogEx
{
// Construction
public:
	CMFCL112PriceCalculationDlg(CWnd* pParent = nullptr);	// standard constructor
	void CalcTotalPrice();
	void ChangeText(CListBox* ap_list_box, int a_index, const TCHAR* ap_string);
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL112PRICECALCULATION_DIALOG };
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
	// ListBox¸¦ OwnerDraw¿Í HasString => Fixed, TRUE
	CCheckListBox m_item_list;
	CListBox m_count_list;
	CSpinButtonCtrl m_count_spin;
	CRect m_spin_rect;
public:
	afx_msg void OnLbnSelchangeItemList();
	afx_msg void OnDeltaposCountSpin(NMHDR* pNMHDR, LRESULT* pResult);
};
