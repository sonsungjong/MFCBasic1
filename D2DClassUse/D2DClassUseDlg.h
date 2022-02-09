
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

		// 기본 글꼴의 이름과 크기를 지정

	}

	// View 그리기 작업을 전담할 함수
	void OnDraw()
	{

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
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
