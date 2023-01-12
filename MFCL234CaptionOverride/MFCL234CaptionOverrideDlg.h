
// MFCL234CaptionOverrideDlg.h : header file
//

#pragma once


// CMFCL234CaptionOverrideDlg dialog
class CMFCL234CaptionOverrideDlg : public CDialogEx
{
private:
	// ���� �������� Ȱ��ȭ ���θ� ����� ���� (0:��Ȱ��ȭ, 1:Ȱ��ȭ)
	char m_is_active;
	// ĸ�ǿ� ����� �۲�
	CFont m_font;
	// ĸ������ ���Ǵ� ����
	CRect m_caption_rect;


// Construction
public:
	CMFCL234CaptionOverrideDlg(CWnd* pParent = nullptr);	// standard constructor

	// ĸ�� ���� ���
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
