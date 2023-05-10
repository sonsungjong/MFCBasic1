#pragma once

class CBackgroundTransparent1Dlg : public CDialogEx
{
// Construction
public:
	CBackgroundTransparent1Dlg(CWnd* pParent = nullptr);	// standard constructor

	void CopyImagePattern(CImage* ap_dest, CImage* ap_src);
	void ModifyBlue();
	void ModifyGreen();
	void ModifyRed();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BACKGROUNDTRANSPARENT1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	CImage m_load_image;				// �̹��� ������ �ҷ��� CImage
	CImage m_edit_image;				// ������ ���� CImage
	CRect m_rect;						// ����

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
	afx_msg void OnBnClickedModifyBtn();
	afx_msg void OnBnClickedRestoreBtn();
	afx_msg void OnBnClickedSaveBtn();
	afx_msg void OnDestroy();
};
