#pragma once

// X-Ray �̹����� �����ֱ� ���� MFCŬ����
#include "XRayView.h"

// CXRayViewerDlg dialog
class CXRayViewerDlg : public CDialogEx
{
private:
	XRayView m_xray_view;			// �̹����� ������ ��ü
	unsigned char m_enable_colors[256];

// Construction
public:
	CXRayViewerDlg(CWnd* pParent = nullptr);	// standard constructor

	// ����ڰ� ǥ�� ������ ������ ���̺�� ����
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
