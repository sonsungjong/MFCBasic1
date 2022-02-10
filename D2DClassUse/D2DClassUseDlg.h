
// D2DClassUseDlg.h : header file
//

#pragma once
#include "TW_Direct2D.h"

class MyView : public TWD_View
{
public:
	MyView()
	{
		// 기본 글꼴의 색상과 선색을 지정
		m_def_color = ColorF(0.3f, 0.8f, 1.0f, 1.0f);
		// 기본 글꼴의 이름과 크기를 지정
		memcpy(m_def_font_name, _T("배달의민족 주아"), 18);
		m_def_font_size = 32.0f;
	}

	// View 그리기 작업을 전담할 함수
	void OnDraw()
	{
		D2D1_RECT_F r{ 30.0f, 30.0f, 450.0f, 150.0f };
		// 글꼴이 출력될 위치를 사각형으로 표시
		mp_target->DrawRectangle(r, mp_user_brush);
		// 글꼴 출력
		mp_target->DrawText(_T("미가공 파이팅!!"), 9, mp_text_format, r, mp_user_brush);
	}
};

// CD2DClassUseDlg dialog
class CD2DClassUseDlg : public CDialogEx
{
// Construction
public:
	CD2DClassUseDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_D2DCLASSUSE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	MyView m_view;

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
