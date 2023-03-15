#pragma once

// ���콺 �ٹ�ư�� �̿��ؼ� �̹����� Ȯ��/���
// �⺻������ ����� �� ũ��� ��µǾ� �ִٰ� ���� ���ؼ� ����� ����ǰ��Ѵ� - ��ʽ� ���

// ���� ��ǥ : ���� ȭ�鿡 ���÷��� �Ǵ� ��ǥ (Device Position)
// �� ��ǥ : ���� ���� ��ǥ (Logical Position)

#define IMAGE_WIDTH				4896
#define IMAGE_HEIGHT				3224
// �̹������� ũ�⸦ �޾ƿ͵� ��

// CZoomInOutDlg dialog
class CZoomInOutDlg : public CDialogEx
{
private:
	// �̹����� �о�� ��ü, �������� �����ϱ� ���� ��ü
	CImage m_image, m_draw_image;
	// HDC�� Attach��ų dc
	CDC m_draw_dc;

	CRect m_client_rect;
	unsigned char m_zoom_level;				// Ȯ��� ��� �ܰ� (0 ~ 10)
	int m_x, m_y, m_cx, m_cy;

	unsigned char m_is_clicked;					// ��Ŭ�� ���� (0 : ����, 1: Ŭ��)
	CPoint m_clicked_position;					// Ŭ���� ��ġ (�巡�׿�)

// Construction
public:
	CZoomInOutDlg(CWnd* pParent = nullptr);	// standard constructor
	
	// Dp -> Lp (��ġ��ǥ���� ����ǥ��)
	inline void DpToLp(float a_dx, float a_dy, float* ap_lx, float* ap_ly);
	// Lp -> Dp (����ǥ���� ��ġ��ǥ��)
	inline void LpToDp(float a_lx, float a_ly, float* ap_dx, float* ap_dy);

	// ���� ��ġ�� Ȯ�� ������ ���� �ٽ� �׸���
	void RedrawMapImage();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZOOMINOUT_DIALOG };
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
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
