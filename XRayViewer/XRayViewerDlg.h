#pragma once
// 속성
// Selection : Extend
// 

// OwnerDraw 버튼, 리스트박스
#include "TW_Button.h"
#include "TW_ListBox.h"
// ToolBar (Picture Control)
#include "TW_ToolBar.h"
// X-Ray 이미지를 보여주기 위한 MFC클래스
#include "XRayView.h"

class TW_ColorListBox : public TW_ListBox
{
public:
	// 오버라이딩 - 256개 색상 목록을 구성하고 XRayView 색상 정보를 사용할 수 있도록 색상별 정보 저장
	void MakeColorList(ColorInfo* ap_color_data) {
		for (int i = 0; i < 256; i++) {
			InsertString(i, _T(""));				// 리스트 박스에 항목 추가
			SetItemDataPtr(i, ap_color_data++);				// 색상별 정보를 담고 있는 메모리 주소 저장
		}
	}

	// 리스트 박스 항목 한개를 생성 (항목 갯수만큼 호출)
	virtual void DrawListItem(CDC* ap_dc, RECT* ap_rect, int a_index, void* ap_data, unsigned char a_select_flag, unsigned char a_focus_flag)
	{

	}
};

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
//	CButton m_show_select_color;				// 체크박스 삭제
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
