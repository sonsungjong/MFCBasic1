
// MFCBasic207OMOCKDlg.h : header file
//

#pragma once
#define X_COUNT					19
#define Y_COUNT					19
#define GRID_LEN					30					// GRID_LENGTH

// CMFCBasic207OMOCKDlg dialog
class CMFCBasic207OMOCKDlg : public CDialogEx
{
protected:
	CPen m_grid_pen;
	unsigned char m_step = 0;			// 0:흑돌, 1:백돌
	char m_dol[Y_COUNT][X_COUNT];		// 0:돌없음, 1:흑돌있음, 2:백돌있음

// Construction
public:
	CMFCBasic207OMOCKDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC207OMOCK_DIALOG };
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
