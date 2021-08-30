#pragma once

// InnerDlg1 dialog

class InnerDlg1 : public CDialogEx
{
	DECLARE_DYNAMIC(InnerDlg1)

public:
	InnerDlg1(CWnd* pParent = nullptr);   // standard constructor
	virtual ~InnerDlg1();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INNER_DLG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnChild();
};
