
// MFCBasic211SnakeGameTDlg.h : header file
//

#pragma once
#define MAX_EAT_COUNT			300				// 최대 먹이갯수
#define MAX_LENGTH					250				// 뱀 최대길이

// 공간복잡도 이득
struct MapPoint
{
	char x;
	char y;
};				// 8byte -> 2byte

// CMFCBasic211SnakeGameTDlg dialog
class CMFCBasic211SnakeGameTDlg : public CDialogEx
{
protected:
	CImage m_draw_image;
	CDC m_draw_dc;

	// 전체 판이 아닌 사용하는 부분만 기억하도록 수정
	MapPoint m_eat_pos[MAX_EAT_COUNT];
	MapPoint m_snake_pos[MAX_LENGTH];

	MapPoint m_pos = {40,30};		// 0:left, 1:up, 2:right, 3:down
	int m_direction = 0;
	int m_eat_count = 0;
	int m_remain_count = MAX_EAT_COUNT;

// Construction
public:
	CMFCBasic211SnakeGameTDlg(CWnd* pParent = nullptr);	// standard constructor
	void DrawMap();
	void GameOver();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC211SNAKEGAMET_DIALOG };
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
