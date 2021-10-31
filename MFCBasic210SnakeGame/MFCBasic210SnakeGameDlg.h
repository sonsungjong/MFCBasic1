
// MFCBasic210SnakeGameDlg.h : header file
//

#pragma once

// 시간복잡도 이득
// CMFCBasic210SnakeGameDlg dialog
class CMFCBasic210SnakeGameDlg : public CDialogEx
{
private:
	CImage m_draw_image;
	CDC m_draw_dc;

	COLORREF m_table[60][80] = {0,};				// y:60, x:80
	int m_count_map[60][80] = { 0, };
	POINT m_pos = { 40, 30 };
	int m_direction = 0;			// 0: left, 1: up, 2: right, 3: down
	// VK_LEFT -> VK_UP -> VK_RIGHT -> VK_RIGHT 0x25~0x28
	int m_eat_count = 0;

// Construction
public:
	CMFCBasic210SnakeGameDlg(CWnd* pParent = nullptr);	// standard constructor
	void DrawMap();
	void GameOver();

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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
