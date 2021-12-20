
// ELCProjectDlg.h : header file
//

#pragma once
#include "TW_DCP.h"

// CELCProjectDlg dialog
class CELCProjectDlg : public CDialogEx
{
private:
	TW_DCP m_dcp;						// �̹��� ��ü ���� ��ü
	TW_DCP m_gate_dcp;				// ����Ʈ �̹����� ������ �ִ� ��ü
	CRect m_rect;							// �׸� ��� ����

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
