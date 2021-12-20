
// ELCProjectDlg.h : header file
//

#pragma once
#include "TW_DCP.h"

// CELCProjectDlg dialog
class CELCProjectDlg : public CDialogEx
{
private:
	TW_DCP m_dcp;						// 이미지 전체 구성 객체
	TW_DCP m_gate_dcp;				// 게이트 이미지를 가지고 있는 객체
	CRect m_rect;							// 그림 출력 영역

// Construction
public:
	CELCProjectDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ELCPROJECT_DIALOG };
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
