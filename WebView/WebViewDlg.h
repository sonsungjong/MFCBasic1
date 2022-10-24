
// WebViewDlg.h : header file
//

#pragma once
#include <MsHTML.h>

// CWebViewDlg dialog
class CWebViewDlg : public CDialogEx
{
private:
	CWnd m_web_browser_control;
	// 웹브라우저 기능 수행
	IWebBrowser2* mp_browser_app;

// Construction
public:
	CWebViewDlg(CWnd* pParent = nullptr);	// standard constructor

	// 지정한 URL을 띄워주는 함수
	void OpenHtmlPage(const TCHAR* ap_page_url);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WEBVIEW_DIALOG };
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
	afx_msg void OnBnClickedGoBtn();
	afx_msg void OnBnClickedHomeBtn();
	afx_msg void OnBnClickedPrevBtn();
	afx_msg void OnBnClickedNextBtn();
	afx_msg void OnBnClickedGetSrcBtn();
	afx_msg void OnBnClickedGetLinkBtn();
};
