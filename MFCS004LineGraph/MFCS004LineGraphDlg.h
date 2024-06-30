#pragma once
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")


// CMFCS004LineGraphDlg dialog
class CMFCS004LineGraphDlg : public CDialogEx
{
private:
	Gdiplus::GdiplusStartupInput m_gdiplus_startup_input;
	ULONG_PTR m_gdiplus_token;

// Construction
public:
	CMFCS004LineGraphDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCS004LINEGRAPH_DIALOG };
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
	afx_msg void OnDestroy();
};
