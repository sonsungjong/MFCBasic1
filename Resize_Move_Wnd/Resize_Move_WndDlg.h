#pragma once


// CResizeMoveWndDlg dialog
class CResizeMoveWndDlg : public CDialogEx
{
// Construction
public:
	CResizeMoveWndDlg(CWnd* pParent = nullptr);	// standard constructor

private:
	// 0: Ŭ���ȵ�, 1: Ŭ��(�̵�����), 2: Ŭ��(top ũ�� ����), 3: Ŭ�� (right/top ũ�� ����), 4:Ŭ��(right ũ�� ����)
	// 5: Ŭ��(right/bottom ũ�� ����), 6:Ŭ��(bottom ũ�� ����), 7:Ŭ��(left/bottom ũ�� ����)
	// 8: Ŭ��(left ũ�� ����), 9: Ŭ��(left/ top ũ�� ����)
	unsigned char m_is_clicked = 0;
	CPoint m_prev_pos;				// ���콺 ���� ��ġ
	HCURSOR mh_cursor[10];				// �� ���º��� ����� ���콺 Ŀ�� �̹��� (10��)

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
