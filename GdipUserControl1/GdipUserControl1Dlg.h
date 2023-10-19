#pragma once
#include "MqttManager.h"

class CGdipUserControl1Dlg : public CDialogEx
{
private:
	// UI
	int m_screen_width, m_screen_height;
	CRect m_full_size, m_row1, m_row2, m_row3, m_row4, m_row5;				// row
	CRect m_min_rect, m_close_rect;											// row1
	CRect m_menu_btn_rect[2], m_search_rect;							// row2
	CRect m_listctrl_rect, m_listbox_rect;										// row3
	CRect m_temp_graph_rect, m_info_rect1;								// row4
	CRect m_vib_graph_rect, m_info_rect2;									// row5
	int m_menu_btn_size = 160;
	int m_font_size = 7;

private:
	// 컨트롤
	CButton m_btn_load_data, m_btn_setting;
	CListCtrl m_listctrl;					// 통합DB 테이블
	CListBox m_listbox;				// 연동장치 테이블
	CEdit m_edit_ctrl;
	HFONT m_font_edit;
	
private:
	// 플래그
	char m_flag_close_on = 0, m_flag_min_on = 0;
	TCHAR m_close_path[MAX_PATH];

public:
	// 데이터
	DCP m_dcp;
	MqttManager* mp_mqtt;
	void TestMethod();

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
	afx_msg void OnBnClickedLoadData();
	afx_msg void OnBnClickedSetting();
};
