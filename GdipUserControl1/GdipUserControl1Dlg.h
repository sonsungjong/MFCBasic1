#pragma once
#include "DCP.h"

class CGdipUserControl1Dlg : public CDialogEx
{
private:
	// 범위
	int m_screen_width;
	int m_screen_height;
	CRect m_full_size, m_top_system_bar, m_menu_bar, m_search_rect, m_table_rect, m_graph_rect;				// row
	CRect m_close_rect;				// col
	CRect m_menu_btn_rect[8];
	int m_menu_btn_size = 120;
	
private:
	// 플래그
	char m_flag_close_on = 0;
	TCHAR m_close_path[MAX_PATH];

public:
	// 데이터
	DCP m_dcp;


public:
	CGdipUserControl1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GDIPUSERCONTROL1_DIALOG };
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
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClose();
};
