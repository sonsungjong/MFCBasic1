
// MFCBasic104ControlPositionDlg.h : header file
//

#pragma once


// CMFCBasic104ControlPositionDlg dialog
class CMFCBasic104ControlPositionDlg : public CDialogEx
{
private:
	CRect m_btn_rect;
	CRect m_btn_rect2;

// Construction
public:
	CMFCBasic104ControlPositionDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC104CONTROLPOSITION_DIALOG };
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
