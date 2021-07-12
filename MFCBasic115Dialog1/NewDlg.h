#pragma once


// NewDlg dialog

class NewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(NewDlg)

public:
	NewDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~NewDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEW_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
