
// PalaDog3Dlg.h : header file
//

#pragma once
#define MAX_WALK_COUNT			12				// 이동모션 이미지수
#define MAX_WAIT_COUNT				12				// 대기모션 이미지수


// CPalaDog3Dlg dialog
class CPalaDog3Dlg : public CDialogEx
{
private:
	CImage m_mem_image;						// 게임 상태 이미지가 저장될 객체
	HDC m_hdc;										// m_mem_image 에 그림을 그릴 DC핸들값
	unsigned char m_walk_flag = 0;				// (0: 정지, 1: 이동)
	int m_cx, m_cy;						// 게임화면 폭과 높이
	int m_hero_x = 100;					// 현재 위치

	CImage m_walk_image[MAX_WALK_COUNT];						// 이동 이미지를 저장할 객체 12개
	int m_walk_index;						// 이동모션 애니메이션 순서

	CImage m_wait_image[MAX_WAIT_COUNT];				// 대기 이미지 저장 12개
	int m_wait_index = 0;						// 대기모션 애니메이션 순서
	CImage m_stage_bk_image;					// 배경
	CImage m_main_panel_image, m_tool_cover_image;
	CImage m_move_key_image[4];			// 이동키
	unsigned char m_left_key_flag = 1, m_right_key_flag = 1;				// 이동키 눌린지 체크할 플래그

// Construction
public:
	CPalaDog3Dlg(CWnd* pParent = nullptr);	// standard constructor

	// 이미지의 일부를 잘라서 PNG로 만드는 함수
	void MakeClipImage();
	// 이미지 생성 함수
	void MakeGameImage();
	// 이동 애니메이션 구현함수
	void HeroMoving();
	// 이미지 읽는 함수
	void LoadGameImage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PALADOG3_DIALOG };
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
