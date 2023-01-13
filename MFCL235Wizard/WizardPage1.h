#pragma once
// 속성 (Inner) - 첫페이지
// Visible : True, Style : Child, Title Bar : False, System Menu : False, Border : None

// WizardPage1 dialog

class WizardPage1 : public CDialogEx
{
	DECLARE_DYNAMIC(WizardPage1)

public:
	WizardPage1(CWnd* pParent = nullptr);   // standard constructor
	virtual ~WizardPage1();
	void GetNumData(int* ap_num1, int* ap_num2);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
};
