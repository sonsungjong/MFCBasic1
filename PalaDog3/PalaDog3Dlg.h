
// PalaDog3Dlg.h : header file
//

#pragma once
#define MAX_WALK_COUNT			12				// �̵���� �̹�����
#define MAX_WAIT_COUNT				12				// ����� �̹�����


// CPalaDog3Dlg dialog
class CPalaDog3Dlg : public CDialogEx
{
private:
	CImage m_mem_image;						// ���� ���� �̹����� ����� ��ü
	HDC m_hdc;										// m_mem_image �� �׸��� �׸� DC�ڵ鰪
	unsigned char m_walk_flag = 0;				// (0: ����, 1: �̵�)
	int m_cx, m_cy;						// ����ȭ�� ���� ����
	int m_hero_x = 100;					// ���� ��ġ

	CImage m_walk_image[MAX_WALK_COUNT];						// �̵� �̹����� ������ ��ü 12��
	int m_walk_index;						// �̵���� �ִϸ��̼� ����

	CImage m_wait_image[MAX_WAIT_COUNT];				// ��� �̹��� ���� 12��
	int m_wait_index = 0;						// ����� �ִϸ��̼� ����
	CImage m_stage_bk_image;					// ���
	CImage m_main_panel_image, m_tool_cover_image;
	CImage m_move_key_image[4];			// �̵�Ű
	unsigned char m_left_key_flag = 1, m_right_key_flag = 1;				// �̵�Ű ������ üũ�� �÷���

// Construction
public:
	CPalaDog3Dlg(CWnd* pParent = nullptr);	// standard constructor

	// �̹����� �Ϻθ� �߶� PNG�� ����� �Լ�
	void MakeClipImage();
	// �̹��� ���� �Լ�
	void MakeGameImage();
	// �̵� �ִϸ��̼� �����Լ�
	void HeroMoving();
	// �̹��� �д� �Լ�
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
