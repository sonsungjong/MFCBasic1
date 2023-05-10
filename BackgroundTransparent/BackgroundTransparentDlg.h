#pragma once

class CBackgroundTransparentDlg : public CDialogEx
{
// Construction
public:
	CBackgroundTransparentDlg(CWnd* pParent = nullptr);	// standard constructor


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BACKGROUNDTRANSPARENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	CImage m_draw_image;				// CImage�� ��Ʈ�ʰ� DC�� MemDC�� Ȱ��
	HDC mh_draw_dc;						// �׸��� �׸� DC
	CRect m_rect;				// ����

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
};
