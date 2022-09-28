
// MFCL209DragDropDlg.h : header file
//

#pragma once
#include "TW_ListBox.h"

class TW_FileListBox : public TW_ListBox
{
private:
	char m_simple_mode = 0;
	TCHAR m_base_path[MAX_PATH];
	int m_path_len;

public:
	void SetBasePath(const TCHAR* ap_path, int a_length)
	{
		m_path_len = a_length;
		memcpy(m_base_path, ap_path, (unsigned long long)a_length + 1);
	}

	void SetSimpleMode(char a_is_simple)
	{
		if (m_simple_mode != a_is_simple) {
			m_simple_mode = a_is_simple;
			Invalidate();
		}
	}

	virtual void DrawUserItem(CDC* ap_dc, RECT* ap_rect, int a_index, void* ap_data, unsigned char a_select_flag, unsigned char a_focus_flag)
	{
		CString str;
		GetText(a_index, str);

		if (GetItemData(a_index)) {
			ap_dc->SetTextColor(RGB(255, 255, 128));
		}
		else {
			ap_dc->SetTextColor(RGB(128, 200, 200));
		}
		if (m_simple_mode) {
			ap_dc->TextOut(ap_rect->left + 5, ap_rect->top + 3, static_cast<const TCHAR*>(str)+m_path_len, str.GetLength() - m_path_len);
		}
		else {
			ap_dc->TextOut(ap_rect->left + 5, ap_rect->top + 3, str);
		}
	}


};

// CMFCL209DragDropDlg dialog
class CMFCL209DragDropDlg : public CDialogEx
{
// Construction
public:
	CMFCL209DragDropDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL209DRAGDROP_DIALOG };
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
	//CListBox m_drop_list;
	TW_FileListBox m_drop_list;
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	void MakeFileList();
	void GetFilesInDirectory(TCHAR* ap_path, int a_insert_index);
	afx_msg void OnBnClickedHidePathCheck();
};
