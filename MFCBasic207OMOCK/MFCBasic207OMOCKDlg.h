
// MFCBasic207OMOCKDlg.h : header file
//

#pragma once


// CMFCBasic207OMOCKDlg dialog
class CMFCBasic207OMOCKDlg : public CDialogEx
{
protected:


// Construction
public:
	CMFCBasic207OMOCKDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC207OMOCK_DIALOG };
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
};
