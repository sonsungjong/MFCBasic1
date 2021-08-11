
// MFCBasic106ListBoxDlg.h : header file
//

#pragma once


// CMFCBasic106ListBoxDlg dialog
class CMFCBasic106ListBoxDlg : public CDialogEx
{
// Construction
public:
	CMFCBasic106ListBoxDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC106LISTBOX_DIALOG };
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
	// 컨트롤 변수
	CListBox m_chat_list;
	afx_msg void OnBnClickedAddBtn();
};
