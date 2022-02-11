
// MFCL113SetPixelDlg.h : header file
//

#pragma once


// CMFCL113SetPixelDlg dialog
class CMFCL113SetPixelDlg : public CDialogEx
{
// Construction
public:
	CMFCL113SetPixelDlg(CWnd* pParent = nullptr);	// standard constructor
	void AddTimeToList(const TCHAR* ap_msg, int a_time_value);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL113SETPIXEL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CImage m_image;
	CDC m_dc;
	unsigned int* mp_image_data;
	BITMAP m_bmp_info;

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedPixelBtn();
	CListBox m_msg_list;
	afx_msg void OnBnClickedPixelvBtn();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedMemPixelBtn();
	afx_msg void OnBnClickedMemPixelvBtn();
	afx_msg void OnBnClickedMemDirectBtn();
	afx_msg void OnBnClickedRPixelBtn();
	afx_msg void OnBnClickedRMemPixelBtn();
	afx_msg void OnBnClickedRMemDirectBtn();
	afx_msg void OnBnClickedNoiseStartBtn();
	afx_msg void OnBnClickedNoiseStopBtn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
