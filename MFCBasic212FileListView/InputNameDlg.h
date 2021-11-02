#pragma once


// InputNameDlg dialog

class InputNameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(InputNameDlg)

private:
	CString m_name;
public:
	InputNameDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~InputNameDlg();
	const wchar_t* GetName() { return m_name; }

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT_NAME_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCreateBtn();
	afx_msg void OnBnClickedCancelBtn();
};
