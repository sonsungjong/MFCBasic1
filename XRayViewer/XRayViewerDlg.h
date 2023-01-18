#pragma once

// X-Ray 이미지를 보여주기 위한 MFC클래스
#include "XRayView.h"

// CXRayViewerDlg dialog
class CXRayViewerDlg : public CDialogEx
{
private:
	XRayView m_xray_view;			// 이미지를 보여줄 객체
	unsigned char m_enable_colors[256];

// Construction
public:
	CXRayViewerDlg(CWnd* pParent = nullptr);	// standard constructor

	// 사용자가 표시 해제한 색상을 테이블로 구성
	void MakeEnableColorTable();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XRAYVIEWER_DIALOG };
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
private:
	CListBox m_color_list;
	CButton m_show_select_color;
public:
	afx_msg void OnBnClickedGetColorBtn();
	afx_msg void OnBnClickedShowSelectColor();
	afx_msg void OnLbnSelchangeColorList();
	afx_msg void OnLbnDblclkColorList();
};
