
// MFCL106ListBoxOwnerDraw2Dlg.h : header file
//

#pragma once
#include "SJ_ListBox.h"

#ifdef _DEBUG
#pragma comment(lib, "SJ_ListBoxD.lib")
#else
#pragma comment(lib, "SJ_ListBox.lib")
#endif

class MyColorList : public SJ_ListBox
{
public:
	void DrawUserItem(CDC* ap_dc, RECT* ap_rect, int a_index, void* ap_data, unsigned char a_select_flag, unsigned char a_focus_flag)
	{
		COLORREF color = GetItemData(a_index);
		ap_dc->FillSolidRect(ap_rect, color);
	}
};

// CMFCL106ListBoxOwnerDraw2Dlg dialog
class CMFCL106ListBoxOwnerDraw2Dlg : public CDialogEx
{
private:
	MyColorList m_color_list;
// Construction
public:
	CMFCL106ListBoxOwnerDraw2Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL106LISTBOXOWNERDRAW2_DIALOG };
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
};
