
// MFCL105OwnerDrawBtnDlg.h : header file
//

#pragma once


// CMFCL105OwnerDrawBtnDlg dialog
class CMFCL105OwnerDrawBtnDlg : public CDialogEx
{
private:
	COLORREF m_user_color = RGB(0,0,255);

// Construction
public:
	CMFCL105OwnerDrawBtnDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL105OWNERDRAWBTN_DIALOG };
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedSelectColorBtn();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};
