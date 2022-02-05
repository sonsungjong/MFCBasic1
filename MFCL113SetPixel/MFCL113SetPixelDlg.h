
// MFCL113SetPixelDlg.h : header file
//

#pragma once


// CMFCL113SetPixelDlg dialog
class CMFCL113SetPixelDlg : public CDialogEx
{
// Construction
public:
	CMFCL113SetPixelDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL113SETPIXEL_DIALOG };
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
