
// MFCBasic212FileListViewDlg.h : header file
//

#pragma once
#include "TW_ListBox.h"
class TW_FileListBox : public TW_ListBox
{
public:
	virtual void DrawUserItem(CDC* ap_dc, RECT* ap_rect, int a_index, void* ap_data, unsigned char a_select_flag, unsigned char a_focus_flag)
	{
		CString str;
		GetText(a_index, str);

		if (str[0] == '[') ap_dc->SetTextColor(RGB(255, 255, 128));
		else ap_dc->SetTextColor(RGB(128, 200, 200));


		ap_dc->TextOut(ap_rect->left + 5, ap_rect->top + 3, str);
	}
};

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
	TW_FileListBox m_list1;
	TW_FileListBox m_list2;
	afx_msg void OnLbnDblclkList1();
	afx_msg void OnLbnDblclkList2();
	afx_msg void OnBnClickedLeftToRight();
	afx_msg void OnBnClickedCreateDir2();
	afx_msg void OnBnClickedOpenDir2();
	afx_msg void OnBnClickedDelBtn2();
};
