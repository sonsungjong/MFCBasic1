
// MFCBasic219Circle3Dlg.h : header file
//

#pragma once


// CMFCBasic219Circle3Dlg dialog
class CMFCBasic219Circle3Dlg : public CDialogEx
{
// Construction
public:
	CMFCBasic219Circle3Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC219CIRCLE3_DIALOG };
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
};
