
// MFCL127VideoListDlg.h : header file
//

#pragma once
#include "COCX_PLAYER.h"


// CMFCL127VideoListDlg dialog
class CMFCL127VideoListDlg : public CDialogEx
{
// Construction
public:
	CMFCL127VideoListDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL127VIDEOLIST_DIALOG };
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
	CListBox m_video_list;
	COCX_PLAYER m_ocx_player;
	afx_msg void OnLbnDblclkVideoList();
};
