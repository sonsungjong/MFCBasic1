
// MFCBasic125CImageDCDlg.h : header file
//

#pragma once
#define MAX_COUNT				200

struct CircleInfo
{
	int x, y, r;
	COLORREF color;
};

// CMFCBasic125CImageDCDlg dialog
class CMFCBasic125CImageDCDlg : public CDialogEx
{
protected:
	CircleInfo m_circleList[MAX_COUNT];
	CircleInfo* m_circlePos;
	CImage m_memView;
// Construction
public:
	CMFCBasic125CImageDCDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC125CIMAGEDC_DIALOG };
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
