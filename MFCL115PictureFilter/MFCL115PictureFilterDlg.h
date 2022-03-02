
// MFCL115PictureFilterDlg.h : header file
//

#pragma once


// CMFCL115PictureFilterDlg dialog
class CMFCL115PictureFilterDlg : public CDialogEx
{
protected:
	CImage m_image, m_commit_image;				// 사진 출력을 위한 CImage
	BITMAP m_bmp_info;				// 사진크기 조정을 위한 비트맵
	unsigned char* mp_image_pattern, *mp_commit_pattern;				// 24bit

// Construction
public:
	CMFCL115PictureFilterDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL115PICTUREFILTER_DIALOG };
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
	afx_msg void OnBnClickedGrayBtn();
	afx_msg void OnBnClickedFilter1Btn();
	afx_msg void OnBnClickedFilter2Btn();
	afx_msg void OnBnClickedFilter3Btn();
	afx_msg void OnBnClickedRestoreBtn();
	afx_msg void OnBnClickedCommitBtn();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
