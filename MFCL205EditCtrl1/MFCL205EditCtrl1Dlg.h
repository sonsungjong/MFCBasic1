
// MFCL205EditCtrl1Dlg.h : header file
//

#pragma once


// CMFCL205EditCtrl1Dlg dialog
class CMFCL205EditCtrl1Dlg : public CDialogEx
{
private:
	HBRUSH mh_edit_bk_brush;
	HWND mh_old_focus = NULL;

// Construction
public:
	CMFCL205EditCtrl1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL205EDITCTRL1_DIALOG };
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
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
};
