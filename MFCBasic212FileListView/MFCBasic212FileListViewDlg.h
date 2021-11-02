
// MFCBasic212FileListViewDlg.h : header file
//

#pragma once


// CMFCBasic212FileListViewDlg dialog
class CMFCBasic212FileListViewDlg : public CDialogEx
{
// Construction
public:
	CMFCBasic212FileListViewDlg(CWnd* pParent = nullptr);	// standard constructor
	void DirToList(CListBox* ap_list_box, CString a_path);
	void ChangeDir(CListBox* ap_list_box, int a_path_ctrl_id);

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
	afx_msg void OnLbnDblclkList1();
	afx_msg void OnLbnDblclkList2();
	afx_msg void OnBnClickedLeftToRight();
	afx_msg void OnBnClickedCreateDir2();
	afx_msg void OnBnClickedOpenDir2();
	afx_msg void OnBnClickedDelBtn2();
};
