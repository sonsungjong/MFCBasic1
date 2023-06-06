
// SimpleLineGraph1Dlg.h : header file
//

#pragma once
#define X_INTERVAL				8			// 데이터 간의 x축 간격

// CSimpleLineGraph1Dlg dialog
class CSimpleLineGraph1Dlg : public CDialogEx
{
protected:
	CImage m_graph_image;
	HDC mh_graph_dc;
	CRect m_rect;

	int m_half_cy;				// 그래프 중간 높이
	int m_data_limit_count = 0;
	int m_data_count = 0;
	int* mp_data_list = NULL;

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
};
