
// D2DClassUseDlg.h : header file
//

#pragma once
#include "TW_Direct2D.h"

class MyView : public TWD_View
{
public:
	MyView()
	{
		// �⺻ �۲��� ����� ������ ����

		// �⺻ �۲��� �̸��� ũ�⸦ ����

	}

	// View �׸��� �۾��� ������ �Լ�
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
