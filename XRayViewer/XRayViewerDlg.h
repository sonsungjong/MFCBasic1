#pragma once
// �Ӽ�
// Selection : Extend
// 

// OwnerDraw ��ư, ����Ʈ�ڽ�
#include "TW_Button.h"
#include "TW_ListBox.h"
// ToolBar (Picture Control)
#include "TW_ToolBar.h"
// X-Ray �̹����� �����ֱ� ���� MFCŬ����
#include "XRayView.h"

class TW_ColorListBox : public TW_ListBox
{
public:
	// �������̵� - 256�� ���� ����� �����ϰ� XRayView ���� ������ ����� �� �ֵ��� ���� ���� ����
	void MakeColorList(ColorInfo* ap_color_data) {
		for (int i = 0; i < 256; i++) {
			InsertString(i, _T(""));				// ����Ʈ �ڽ��� �׸� �߰�
			SetItemDataPtr(i, ap_color_data++);				// ���� ������ ��� �ִ� �޸� �ּ� ����
		}
	}

	// ����Ʈ �ڽ� �׸� �Ѱ��� ���� (�׸� ������ŭ ȣ��)
	virtual void DrawListItem(CDC* ap_dc, RECT* ap_rect, int a_index, void* ap_data, unsigned char a_select_flag, unsigned char a_focus_flag)
	{

	}
};

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
	void ChangeListBoxItemString(int a_index, const TCHAR* ap_string);
	void ImageUpdateAccordingToColorRangeChange();

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
//	CButton m_show_select_color;				// üũ�ڽ� ����
public:
	afx_msg void OnBnClickedGetColorBtn();
	afx_msg void OnBnClickedShowSelectColor();
	afx_msg void OnLbnSelchangeColorList();
	afx_msg void OnLbnDblclkColorList();
	afx_msg void OnBnClickedSelectAllBtn();
	afx_msg void OnBnClickedToggleBtn();
	afx_msg void OnBnClickedColorEnableBtn();
	afx_msg void OnBnClickedColorDisableBtn();
};
