
// MFCL126VideoPlayerDlg.h : header file
//

#pragma once


// CMFCL126VideoPlayerDlg dialog
class CMFCL126VideoPlayerDlg : public CDialogEx
{
// Construction
public:
	CMFCL126VideoPlayerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL126VIDEOPLAYER_DIALOG };
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
};
