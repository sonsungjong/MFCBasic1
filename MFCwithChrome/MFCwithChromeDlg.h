
// MFCwithChromeDlg.h : header file
//

#pragma once
#include <include/cef_app.h>
#include <include/cef_client.h>
#include <include/cef_browser.h>


// CMFCwithChromeDlg dialog
class CMFCwithChromeDlg : public CDialogEx
{
private:
	CRect m_rect;
	CefRefPtr<CefBrowser> m_browser;
	CefRefPtr<CefClient> m_client;
	CefWindowInfo m_window_info;
	CefBrowserSettings m_browser_settings;

// Construction
public:
	CMFCwithChromeDlg(CWnd* pParent = nullptr);	// standard constructor


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCWITHCHROME_DIALOG };
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
};
