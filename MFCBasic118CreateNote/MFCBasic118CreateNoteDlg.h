
// MFCBasic118CreateNoteDlg.h : header file
//

#pragma once


// CMFCBasic118CreateNoteDlg dialog
class CMFCBasic118CreateNoteDlg : public CDialogEx
{
// Construction
public:
	CMFCBasic118CreateNoteDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC118CREATENOTE_DIALOG };
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
	afx_msg void OnBnClickedOpenBtn();
	afx_msg void OnBnClickedSaveBtn();
};
