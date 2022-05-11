
// PalaDog1Dlg.h : header file
//

#pragma once
#define MAX_WALK_COUNT		12					// 이동하는 이미지 12개

// CPalaDog1Dlg dialog
class CPalaDog1Dlg : public CDialogEx
{
private:
	CImage m_mem_image;
	HDC m_hdc;
	unsigned char m_walk_flag = 0;				// 0 : 멈춤, 1 : 이동 중
	int m_cx, m_cy;				// 게임화면의 폭과 높이
	int m_hero_x = 100;					// 캐릭터의 현재 위치

	CImage m_walk_image[MAX_WALK_COUNT];				// 이동 이미지 전체를 저장할 이미지객체
	int m_cur_index = 0;			// 애니메이션 이미지 순서

// Construction
public:
	CPalaDog1Dlg(CWnd* pParent = nullptr);	// standard constructor
	// 원본 이미지에서 원하는 영역의 이미지를 잘라 PNG 파일로 만드는 함수
	void MakeClipImage();

	// 게임 이미지 생성
	void MakeGameImage();

	// 캐릭터 이동에 대한 애니메이션
	void HeroMoving();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PALADOG1_DIALOG };
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
