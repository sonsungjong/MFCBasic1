
// MFCL222GdiPlus1Dlg.h : header file
//

#pragma once


// CMFCL222GdiPlus1Dlg dialog
class CMFCL222GdiPlus1Dlg : public CDialogEx
{
private:
	ULONG_PTR m_token;				// 나중에 GDI+ 해제를 하기위한 변수

// Construction
public:
	CMFCL222GdiPlus1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL222GDIPLUS1_DIALOG };
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
};
