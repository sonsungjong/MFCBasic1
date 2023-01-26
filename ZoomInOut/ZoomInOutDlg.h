#pragma once

// 마우스 휠버튼을 이용해서 이미지를 확대/축소
// 기본적으론 삼분의 일 크기로 출력되어 있다가 휠을 통해서 사이즈가 변경되게한다 - 비례식 사용

// 물리 좌표 : 현재 화면에 디스플레이 되는 좌표 (Device Position)
// 논리 좌표 : 실제 지도 좌표 (Logical Position)

#define IMAGE_WIDTH				4896
#define IMAGE_HEIGHT				3224
// 이미지에서 크기를 받아와도 됨

// CZoomInOutDlg dialog
class CZoomInOutDlg : public CDialogEx
{
private:
	// 이미지를 읽어올 객체, 깜빡임을 방지하기 위한 객체
	CImage m_image, m_draw_image;
	// HDC를 Attach시킬 dc
	CDC m_draw_dc;

	CRect m_client_rect;
	unsigned char m_zoom_level;				// 확대와 축소 단계 (0 ~ 10)
	int m_x, m_y, m_cx, m_cy;

	unsigned char m_is_clicked;					// 좌클릭 여부 (0 : 해제, 1: 클릭)
	CPoint m_clicked_position;					// 클릭한 위치 (드래그용)

// Construction
public:
	CZoomInOutDlg(CWnd* pParent = nullptr);	// standard constructor
	
	// Dp -> Lp (장치좌표에서 논리좌표로)
	inline void DpToLp(float a_dx, float a_dy, float* ap_lx, float* ap_ly);
	// Lp -> Dp (논리좌표에서 장치좌표로)
	inline void LpToDp(float a_lx, float a_ly, float* ap_dx, float* ap_dy);

	// 시작 위치와 확대 정보를 통해 다시 그린다
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
