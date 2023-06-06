
// SimpleLineGraph1Dlg.h : header file
//

#pragma once
#define X_INTERVAL				8			// ������ ���� x�� ����

// CSimpleLineGraph1Dlg dialog
class CSimpleLineGraph1Dlg : public CDialogEx
{
protected:
	CImage m_graph_image;
	HDC mh_graph_dc;
	CRect m_rect;

	int m_start_flag = 0;				// �׷��� ���� ���� (0:����, 1: ����)
	int m_half_cy;				// �׷��� �߰� ����
	int m_data_limit_count = 0;
	int m_scroll_index = 0;
	int m_data_count = 0;
	int* mp_data_list = NULL;
	POINT* mp_pos_list = NULL;				// ������

// Construction
public:
	CSimpleLineGraph1Dlg(CWnd* pParent = nullptr);	// standard constructor
	void DrawGraph();


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SIMPLELINEGRAPH1_DIALOG };
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
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedStartBtn();
	afx_msg void OnBnClickedStopBtn();
};
