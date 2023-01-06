
// MFCL231BinaryViewerDlg.h : header file
//

#pragma once


// CMFCL231BinaryViewerDlg dialog
class CMFCL231BinaryViewerDlg : public CDialogEx
{
private:
	CFont m_font;

// Construction
public:
	CMFCL231BinaryViewerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL231BINARYVIEWER_DIALOG };
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
private:
	CListBox m_bin_data_list;
public:
	afx_msg void OnBnClickedSelectBtn();
};
