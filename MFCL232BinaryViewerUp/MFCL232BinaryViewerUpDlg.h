
// MFCL232BinaryViewerUpDlg.h : header file
//

#pragma once
#include "BinDataView.h"

// CMFCL232BinaryViewerUpDlg dialog
class CMFCL232BinaryViewerUpDlg : public CDialogEx
{
private:
	BinDataView m_bin_data_view;

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
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedSelectBtn();
};
