
// MFCL122HookingDlg.h : header file
//

#pragma once


// CMFCL122HookingDlg dialog
class CMFCL122HookingDlg : public CDialogEx
{
private:
	HINSTANCE m_hook_dll;
// Construction
public:
	CMFCL122HookingDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL122HOOKING_DIALOG };
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
	CListBox m_event_list;
	afx_msg void OnDestroy();
protected:
	afx_msg LRESULT On27001(WPARAM wParam, LPARAM lParam);
public:
	CEdit m_show_edit;
	afx_msg void OnBnClickedOk();
};
