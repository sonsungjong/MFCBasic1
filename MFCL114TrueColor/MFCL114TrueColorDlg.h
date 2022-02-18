
// MFCL114TrueColorDlg.h : header file
//

#pragma once


// CMFCL114TrueColorDlg dialog
class CMFCL114TrueColorDlg : public CDialogEx
{
// Construction
public:
	CMFCL114TrueColorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL114TRUECOLOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CImage m_color_image;
	CImage m_draw_image;				// ±ôºýÀÓÀ» ¾ø¾Ö±âÀ§ÇÑ CImage
	CDC m_draw_dc;
	unsigned int* mp_color_pattern;
	CRect m_view_rect;
	unsigned char m_is_clicked = 0;
	CPoint m_prev_pos;

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};
