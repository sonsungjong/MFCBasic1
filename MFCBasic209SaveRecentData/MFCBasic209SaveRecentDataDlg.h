
// MFCBasic209SaveRecentDataDlg.h : header file
//

#pragma once


// CMFCBasic209SaveRecentDataDlg dialog
class CMFCBasic209SaveRecentDataDlg : public CDialogEx
{
private:
	CPtrList m_data_list;

	int m_move_data[10];
	int m_data_count = 0;			// 실제 데이터의 갯수

	int m_index_data[10];
	int m_index = 0;

// Construction
public:
	CMFCBasic209SaveRecentDataDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC209SAVERECENTDATA_DIALOG };
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
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
