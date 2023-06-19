#pragma once


// CResizeMoveWndDlg dialog
class CResizeMoveWndDlg : public CDialogEx
{
// Construction
public:
	CResizeMoveWndDlg(CWnd* pParent = nullptr);	// standard constructor

private:
	// 0: 클릭안됨, 1: 클릭(이동전용), 2: 클릭(top 크기 변경), 3: 클릭 (right/top 크기 변경), 4:클릭(right 크기 변경)
	// 5: 클릭(right/bottom 크기 변경), 6:클릭(bottom 크기 변경), 7:클릭(left/bottom 크기 변경)
	// 8: 클릭(left 크기 변경), 9: 클릭(left/ top 크기 변경)
	unsigned char m_is_clicked = 0;
	CPoint m_prev_pos;				// 마우스 이전 위치
	HCURSOR mh_cursor[10];				// 각 상태별로 사용할 마우스 커서 이미지 (10개)

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESIZE_MOVE_WND_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
