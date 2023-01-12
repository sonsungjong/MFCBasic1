
// MFCL234CaptionOverrideDlg.h : header file
//

#pragma once


// CMFCL234CaptionOverrideDlg dialog
class CMFCL234CaptionOverrideDlg : public CDialogEx
{
private:
	// 현재 윈도우의 활성화 여부를 기억할 변수 (0:비활성화, 1:활성화)
	char m_is_active;
	// 캡션에 사용할 글꼴
	CFont m_font;
	// 캡션으로 사용되는 영역
	CRect m_caption_rect;


// Construction
public:
	CMFCL234CaptionOverrideDlg(CWnd* pParent = nullptr);	// standard constructor

	// 캡션 영역 계산
	void MakeWindowCaptionRect();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL234CAPTIONOVERRIDE_DIALOG };
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
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnNcPaint();
};
