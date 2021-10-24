
// MFCBasic210SnakeGameDlg.h : header file
//

#pragma once


// CMFCBasic210SnakeGameDlg dialog
class CMFCBasic210SnakeGameDlg : public CDialogEx
{
// Construction
public:
	CMFCBasic210SnakeGameDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC210SNAKEGAME_DIALOG };
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
};
