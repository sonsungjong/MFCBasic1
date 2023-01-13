#pragma once
// 속성 (Inner) - 두번째 페이지
// Style : Child, Title Bar : False, System Menu : False, Border : None

// WizardPage2 dialog

class WizardPage2 : public CDialogEx
{
	DECLARE_DYNAMIC(WizardPage2)

public:
	WizardPage2(CWnd* pParent = nullptr);   // standard constructor
	virtual ~WizardPage2();
	int GetOpType();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CListBox m_op_list;
};
