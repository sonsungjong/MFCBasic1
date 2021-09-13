
// MFCBasic124MemoryDCDlg.h : header file
//

#pragma once

#define MAX_COUNT				100

struct Circle
{
	int x, y, r;
	COLORREF color;
};

// CMFCBasic124MemoryDCDlg dialog
class CMFCBasic124MemoryDCDlg : public CDialogEx
{
protected:
	int w, h, minR, maxR;
	Circle m_circleList[MAX_COUNT];
	Circle* mp;
	CRect r;
	CBrush fill_brush;
	CBrush* p_oldBrush;

// Construction
public:
	CMFCBasic124MemoryDCDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC124MEMORYDC_DIALOG };
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
};
