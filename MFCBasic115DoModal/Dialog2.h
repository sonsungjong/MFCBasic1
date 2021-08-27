#pragma once


// Dialog2 dialog

class Dialog2 : public CDialogEx
{
protected:
	int m_num;

	DECLARE_DYNAMIC(Dialog2)

public:
	void SetNum(int a_num);
	int GetNum();

	Dialog2(CWnd* pParent = nullptr);   // standard constructor
	virtual ~Dialog2();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
