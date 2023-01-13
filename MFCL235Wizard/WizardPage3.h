#pragma once
// 加己 (Inner) - 技锅掳 其捞瘤
// Style : Child, Title Bar : False, System Menu : False, Border : None

// WizardPage3 dialog

class WizardPage3 : public CDialogEx
{
	DECLARE_DYNAMIC(WizardPage3)

public:
	WizardPage3(CWnd* pParent = nullptr);   // standard constructor
	virtual ~WizardPage3();
	void SetResultValue(int a_result);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
