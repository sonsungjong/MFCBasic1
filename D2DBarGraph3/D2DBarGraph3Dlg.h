
// D2DBarGraph3Dlg.h : header file
//

#pragma once
#include "D2DClass.h"
#include "MyWnd1.h"
#include "MyWnd2.h"

// CD2DBarGraph3Dlg dialog
class CD2DBarGraph3Dlg : public CDialogEx
{
private:
	D2DClass m_d2d[3];
	CRect m_d2d_rect[3];
	MyWnd1 m_d2d_wnd[3];

// Construction
public:
	CD2DBarGraph3Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_D2DBARGRAPH3_DIALOG };
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
	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
