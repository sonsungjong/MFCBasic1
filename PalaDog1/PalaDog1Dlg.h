
// PalaDog1Dlg.h : header file
//

#pragma once
#define MAX_WALK_COUNT		12					// �̵��ϴ� �̹��� 12��

// CPalaDog1Dlg dialog
class CPalaDog1Dlg : public CDialogEx
{
private:
	CImage m_mem_image;
	HDC m_hdc;
	unsigned char m_walk_flag = 0;				// 0 : ����, 1 : �̵� ��
	int m_cx, m_cy;				// ����ȭ���� ���� ����
	int m_hero_x = 100;					// ĳ������ ���� ��ġ

	CImage m_walk_image[MAX_WALK_COUNT];				// �̵� �̹��� ��ü�� ������ �̹�����ü
	int m_cur_index = 0;			// �ִϸ��̼� �̹��� ����

// Construction
public:
	CPalaDog1Dlg(CWnd* pParent = nullptr);	// standard constructor
	// ���� �̹������� ���ϴ� ������ �̹����� �߶� PNG ���Ϸ� ����� �Լ�
	void MakeClipImage();

	// ���� �̹��� ����
	void MakeGameImage();

	// ĳ���� �̵��� ���� �ִϸ��̼�
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
