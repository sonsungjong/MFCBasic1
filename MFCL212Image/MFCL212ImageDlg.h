
// MFCL212ImageDlg.h : header file
//

#pragma once


// CMFCL212ImageDlg dialog
class CMFCL212ImageDlg : public CDialogEx
{
private:
	CRect m_rect;
	CImage m_image;
	CString m_select_name, m_select_path;

// Construction
public:
	CMFCL212ImageDlg(CWnd* pParent = nullptr);	// standard constructor
	void DirToList(const TCHAR* ap_path);
	void AddLogString(const TCHAR* ap_string);
	// 11
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL212IMAGE_DIALOG };
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
	CListBox m_list_image;
public:
	afx_msg void OnLbnDblclkListImage();
	afx_msg void OnLbnSelchangeListImage();
private:
	CComboBox m_log_list;
public:
	afx_msg void OnBnClickedButtonResize();
};
