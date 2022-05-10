
// MFCL117PaintBrushDlg.h : header file
//

#pragma once
#include "SJ_ListBox.h"
#include "DrawWnd.h"

#ifdef _DEBUG
#pragma comment(lib, "SJ_ListBoxD.lib")
#else
#pragma comment(lib, "SJ_ListBox.lib")
#endif

class MyColorList : public SJ_ListBox
{
public:
	void DrawUserItem(CDC* ap_dc, RECT* ap_rect, int a_index, void* ap_data,
		unsigned char a_select_flag, unsigned char a_focus_flag)
	{
		COLORREF color = GetItemData(a_index);
		CRect r(ap_rect->left + 2, ap_rect->top + 2, ap_rect->right - 2, ap_rect->bottom - 2);
		ap_dc->FillSolidRect(r, color);
	}
};

// CMFCL117PaintBrushDlg dialog
class CMFCL117PaintBrushDlg : public CDialogEx
{
private:
	DrawWnd m_draw_wnd;
	MyColorList m_color_list;

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
