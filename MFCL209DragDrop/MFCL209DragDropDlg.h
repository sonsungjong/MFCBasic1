
// MFCL209DragDropDlg.h : header file
//

#pragma once


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
	CListBox m_drop_list;
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	void MakeFileList();
	void GetFilesInDirectory(TCHAR* ap_path, int a_insert_index);
};
