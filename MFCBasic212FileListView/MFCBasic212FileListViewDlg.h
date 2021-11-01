
// MFCBasic212FileListViewDlg.h : header file
//

#pragma once


// CMFCBasic212FileListViewDlg dialog
class CMFCBasic212FileListViewDlg : public CDialogEx
{
// Construction
public:
	CMFCBasic212FileListViewDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC212FILELISTVIEW_DIALOG };
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
	CListBox m_list1;
	CListBox m_list2;
};
