
// MFCL223GdiPlus2Dlg.h : header file
//

#pragma once
#include "GDI_View.h"
#include "GDI_Plus_view.h"

// CMFCL223GdiPlus2Dlg dialog
class CMFCL223GdiPlus2Dlg : public CDialogEx
{
private:
	// 인클루드해서 변수로 선언
	GDI_View m_gdi_view;
	GDI_Plus_view m_gdi_plus_view;

// Construction
public:
	CMFCL223GdiPlus2Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL223GDIPLUS2_DIALOG };
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
	afx_msg void OnBnClickedAcceptBtn();
};
