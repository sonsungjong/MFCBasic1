
// MFCL117PaintBrushDlg.h : header file
//

#pragma once
#include "DrawWnd.h"

// CMFCL117PaintBrushDlg dialog
class CMFCL117PaintBrushDlg : public CDialogEx
{
private:
	DrawWnd m_draw_wnd;

// Construction
public:
	CMFCL117PaintBrushDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL117PAINTBRUSH_DIALOG };
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
	afx_msg void OnClose();
	CButton m_pen_radio;
	CButton m_line_radio;
	CButton m_rect_radio;
	afx_msg void OnBnClickedPenRadio();
	afx_msg void OnBnClickedLineRadio();
	afx_msg void OnBnClickedRectRadio();
};
