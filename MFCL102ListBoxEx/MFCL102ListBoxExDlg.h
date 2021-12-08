
// MFCL102ListBoxExDlg.h : header file
//

#pragma once
struct PersonData
{
	TCHAR name[32];
	TCHAR phone[32];
	int age;
};

// CMFCL102ListBoxExDlg dialog
class CMFCL102ListBoxExDlg : public CDialogEx
{
// Construction
public:
	CMFCL102ListBoxExDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL102LISTBOXEX_DIALOG };
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
	afx_msg void OnBnClickedAddBtn();
	CListBox m_data_list;
	afx_msg void OnLbnSelchangeDataList();
	afx_msg void OnDestroy();
};
