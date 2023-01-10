
// MFCL232BinaryViewerUpDlg.h : header file
//

#pragma once


// CMFCL232BinaryViewerUpDlg dialog
class CMFCL232BinaryViewerUpDlg : public CDialogEx
{
// Construction
public:
	CMFCL232BinaryViewerUpDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL232BINARYVIEWERUP_DIALOG };
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
