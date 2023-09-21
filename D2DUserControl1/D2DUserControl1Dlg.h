
// D2DUserControl1Dlg.h : header file
//

#pragma once
#include "D2DClass.h"
#include "CWndBox.h"
#include "SystemBar.h"

class CD2DUserControl1Dlg : public CDialogEx
{
private:
	int m_screen_width;
	int m_screen_height;

	CRect m_full_size, m_top_system_bar, m_left_menu_bar;
	D2DClass m_d2d[10];
	CWndBox m_wnd_full, m_wnd_menu_bar;
	SystemBar m_wnd_system_bar;

private:
	char m_flag_close_on = 0;

// Construction
public:
	CD2DUserControl1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_D2DUSERCONTROL1_DIALOG };
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
