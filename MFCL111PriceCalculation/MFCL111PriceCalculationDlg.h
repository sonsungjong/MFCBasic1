
// MFCL111PriceCalculationDlg.h : header file
//

#pragma once


// CMFCL111PriceCalculationDlg dialog
class CMFCL111PriceCalculationDlg : public CDialogEx
{
// Construction
public:
	CMFCL111PriceCalculationDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL111PRICECALCULATION_DIALOG };
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
	void CalcTotalPrice();
	DECLARE_MESSAGE_MAP()
public:
	void ChangeText(CListBox* ap_list_box, int a_index, const TCHAR* ap_string);
	void OnLbnSelchangeItemList();

	// ListBox¿¡ OwnerDraw¿Í hasString => Fixed, TRUE
	CCheckListBox m_item_list;
	CListBox m_count_list;
	
	CRect m_spin_rect;
	CSpinButtonCtrl m_count_spin;
	afx_msg void OnDeltaposCountSpin(NMHDR* pNMHDR, LRESULT* pResult);
};
