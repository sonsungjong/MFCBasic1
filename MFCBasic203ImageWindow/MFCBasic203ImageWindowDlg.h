
// MFCBasic203ImageWindowDlg.h : header file
//

#pragma once


// CMFCBasic203ImageWindowDlg dialog
class CMFCBasic203ImageWindowDlg : public CDialogEx
{
protected:
	CImage m_img;
	CRect m_client_rect, m_win_rect, m_btn_rect;
	int m_cx_margin, m_cy_margin, m_top_margin;			// 윈도우영역과 클라이언트영역간의 차이값
	float m_zoom_level = 0.125f;

// Construction
public:
	CMFCBasic203ImageWindowDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC203IMAGEWINDOW_DIALOG };
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
	afx_msg void OnBnClickedMul2();
	afx_msg void OnBnClickedMul4();
	afx_msg void OnBnClickedMul8();
};
