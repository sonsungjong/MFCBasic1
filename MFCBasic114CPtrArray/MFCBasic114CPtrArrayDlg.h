
// MFCBasic114CPtrArrayDlg.h : header file
//

#pragma once

// CMFCBasic114CPtrArrayDlg dialog
class CMFCBasic114CPtrArrayDlg : public CDialogEx
{
protected:
	CPtrArray m_pos_list;			// java의 ArrayList와 유사, 배열기반 클래스
	//CPtrList m_pos_list;				// Linked List 기반의 클래스

// Construction
public:
	CMFCBasic114CPtrArrayDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC114CPTRARRAY_DIALOG };
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};
