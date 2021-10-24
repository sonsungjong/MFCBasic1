
// MFCBasic210SnakeGameDlg.h : header file
//

#pragma once


// CMFCBasic210SnakeGameDlg dialog
class CMFCBasic210SnakeGameDlg : public CDialogEx
{
private:
	CImage m_draw_image;
	CDC m_draw_dc;

	COLORREF m_table[60][80] = {0,};				// y:60, x:80
	POINT m_pos = { 40, 30 };
	int m_direction = 0;			// 0: left, 1: up, 2: right, 3: bottom

// Construction
public:
	CMFCBasic210SnakeGameDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC210SNAKEGAME_DIALOG };
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
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
