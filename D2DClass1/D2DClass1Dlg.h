#pragma once
#include "MFC_D2D.h"

class MyView : public D2D_View
{
public:
	MyView()
	{
		// 기본 글꼴의 색상과 선색을 지정
		m_def_color = ColorF(0.3f, 0.8f, 1.0f, 1.0f);
		// 기본 글꼴의 이름과 크기를 지정
		memcpy(m_font_name, _T("맑은 고딕"), 12);
		m_font_size = 32.0f;
	}

	// View 그리기 작업을 전담할 함수
	void d2dDraw()
	{
		D2D1_RECT_F r{ 30.0f, 30.0f, 450.0f, 150.0f };
		// 글꼴이 출력될 위치를 사각형으로 표시
		mp_target->DrawRectangle(r, mp_user_brush);
		// 글꼴 출력
		mp_target->DrawText(_T("미가공 파이팅!!"), 9, mp_text_format, r, mp_user_brush);
	}
};

// CD2DClass1Dlg dialog
class CD2DClass1Dlg : public CDialogEx
{
private:
	MyView m_view;
	//D2D_View m_view;

// Construction
public:
	CD2DClass1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_D2DCLASS1_DIALOG };
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
};
