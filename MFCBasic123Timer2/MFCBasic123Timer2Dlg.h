
// MFCBasic123Timer2Dlg.h : header file
//

#pragma once

#define MAX_COUNT			50

struct CircleData
{
	int x, y;			// 중심점
	int r;				// 반지름
	COLORREF color;
};

// CMFCBasic123Timer2Dlg dialog
class CMFCBasic123Timer2Dlg : public CDialogEx
{
protected:
	CircleData m_circleList[MAX_COUNT];
	int w, h;
// Construction
public:
	CMFCBasic123Timer2Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC123TIMER2_DIALOG };
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
