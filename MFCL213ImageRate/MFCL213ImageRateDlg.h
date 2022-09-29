
// MFCL213ImageRateDlg.h : header file
//

#pragma once


// CMFCL213ImageRateDlg dialog
class CMFCL213ImageRateDlg : public CDialogEx
{
private:
	CButton m_check_rate;
	CRect m_rect;							// ������ ��ǥ ���
	CRect m_rate_size;					// ���� �׸��� ��µ� ������ ũ�� (����)
	CImage m_image;

// Construction
public:
	CMFCL213ImageRateDlg(CWnd* pParent = nullptr);	// standard constructor
	void MakeDisplayImageRect();
	void ResizeByWidth(int a_width, int a_height);
	void ResizeByHeight(int a_width, int a_height);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL213IMAGERATE_DIALOG };
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
	afx_msg void OnBnClickedCheckRate();
};
