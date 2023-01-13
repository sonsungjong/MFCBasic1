
// 속성
// 버튼 비활성화 Disabled : True

#pragma once
#include "WizardPage1.h"
#include "WizardPage2.h"
#include "WizardPage3.h"

// 고정된 3개의 페이지
#define MAX_PAGE_COUNT			3

// CMFCL235WizardDlg dialog
class CMFCL235WizardDlg : public CDialogEx
{
private:
	// 다형성 적용
	CDialogEx* mp_page[3];				// 페이지 3개
	CRect m_wizard_rect;
	int m_page_index = 0;				// 현재 페이지 번호

	int m_num1 = 0, m_num2 = 0;

// Construction
public:
	CMFCL235WizardDlg(CWnd* pParent = nullptr);	// standard constructor
	void AddPage(CDialogEx* ap_page, int a_index, int a_dlg_id);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL235WIZARD_DIALOG };
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
	afx_msg void OnBnClickedPrevBtn();
	afx_msg void OnBnClickedNextBtn();
};
