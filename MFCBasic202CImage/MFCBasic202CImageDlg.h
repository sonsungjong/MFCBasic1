
// MFCBasic202CImageDlg.h : header file
//

#pragma once


// CMFCBasic202CImageDlg dialog
class CMFCBasic202CImageDlg : public CDialogEx
{
protected:
	CImage m_img;
	CRect m_rect;

// Construction
public:
	CMFCBasic202CImageDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC202CIMAGE_DIALOG };
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
	afx_msg void OnBnClickedSelectImg();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
