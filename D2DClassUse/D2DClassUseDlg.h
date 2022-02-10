
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
		m_def_color = ColorF(0.3f, 0.8f, 1.0f, 1.0f);
		// �⺻ �۲��� �̸��� ũ�⸦ ����
		memcpy(m_def_font_name, _T("����ǹ��� �־�"), 18);
		m_def_font_size = 32.0f;
	}

	// View �׸��� �۾��� ������ �Լ�
	void OnDraw()
	{
		D2D1_RECT_F r{ 30.0f, 30.0f, 450.0f, 150.0f };
		// �۲��� ��µ� ��ġ�� �簢������ ǥ��
		mp_target->DrawRectangle(r, mp_user_brush);
		// �۲� ���
		mp_target->DrawText(_T("�̰��� ������!!"), 9, mp_text_format, r, mp_user_brush);
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
