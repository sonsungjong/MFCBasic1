
// MoveRectangle1Dlg.h : header file
//

#pragma once


// CMoveRectangle1Dlg dialog
class CMoveRectangle1Dlg : public CDialogEx
{
	//CRect m_rect;
	::RECT m_rect;
	HDC m_hdc;
	HBRUSH m_brush;
	int nUp, nDown, nLeft, nRight;
	int m_last_key = 0;

// Construction
public:
	CMoveRectangle1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOVERECTANGLE1_DIALOG };
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
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};
