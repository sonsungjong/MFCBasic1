
// MFCImageProcessingDlg.h : header file
//

#pragma once


// CMFCImageProcessingDlg dialog
class CMFCImageProcessingDlg : public CDialogEx
{
protected:
	CImage m_img;
	unsigned char *mp_org_image, *mp_cur_image;
	UINT32 m_image_size, m_image_cx, m_image_cy, m_line_size;

	int m_max = 220, m_min = 170;

	POINT* mp_point_list;
// Construction
public:
	CMFCImageProcessingDlg(CWnd* pParent = nullptr);	// standard constructor
	void ModifyGrayPattern();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCIMAGEPROCESSING_DIALOG };
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
	CSliderCtrl m_min_slider;
	CSliderCtrl m_max_slider;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDestroy();
	
	int CheckObjectPos(RECT* p_target_rect, int a_x, int a_y,
		unsigned int a_org_color, unsigned int a_change_color,
		unsigned int* ap_image_data, int a_image_width, int a_image_height);
	afx_msg void OnBnClickedPipeCheckBtn();
};
