
// MFCBasic203ImageWindowDlg.h : header file
//

#pragma once


// CMFCBasic203ImageWindowDlg dialog
class CMFCBasic203ImageWindowDlg : public CDialogEx
{
// Construction
public:
	CMFCBasic203ImageWindowDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC203IMAGEWINDOW_DIALOG };
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
