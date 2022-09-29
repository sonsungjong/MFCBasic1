
// MFCBasic212FileListViewDlg.h : header file
//

#pragma once
#include "TW_ListBox.h"

typedef struct FileItemInformation
{
	unsigned int attr;
	unsigned int h_size;
	unsigned int l_size;
	TCHAR* p_name;
	unsigned short name_len;
} FII;

class TW_FileListBox : public TW_ListBox
{
public:
	virtual void DrawUserItem(CDC* ap_dc, RECT* ap_rect, int a_index, void* ap_data, unsigned char a_select_flag, unsigned char a_focus_flag)
	{
		FII *p = (FII*)ap_data;

		if (p->attr & FILE_ATTRIBUTE_DIRECTORY) {
			ap_dc->SetTextColor(RGB(255, 255, 128));
			ap_dc->TextOut(ap_rect->left + 5, ap_rect->top + 3, p->p_name, p->name_len);
		}
		else {
			ap_dc->SetTextColor(RGB(128, 200, 200));
			ap_dc->TextOut(ap_rect->left + 5, ap_rect->top + 3, p->p_name, p->name_len);
			CString str;
			str.Format(_T("%d"), p->l_size);
			ap_dc->DrawText(str, ap_rect, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
		}


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
	void ResetFII(CListBox* ap_list_box);

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
	afx_msg void OnDestroy();
};
