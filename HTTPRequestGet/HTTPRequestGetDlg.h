
// HTTPRequestGetDlg.h : header file
//

#pragma once


// CHTTPRequestGetDlg dialog
class CHTTPRequestGetDlg : public CDialogEx
{
// Construction
public:
	CHTTPRequestGetDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HTTPREQUESTGET_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	void MobileAuthPush();
	void MobileAuthResult();

	void MobileQrGenerate();
	void MobileQrAuthResult();

	void MobileOtpSignin();

	void LoginLog();

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
	afx_msg void OnBnClickedWebcam();
	afx_msg void OnBnClickedMobilePush1();
	afx_msg void OnBnClickedMobilePush2();
	afx_msg void OnBnClickedMobileQr1();
	afx_msg void OnBnClickedMobileQr2();
	afx_msg void OnBnClickedOtp();
	afx_msg void OnBnClickedLoginLog();
};
