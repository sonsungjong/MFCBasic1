
// TTSDialog1Dlg.h : header file
//

#pragma once
#pragma warning(disable:4996)
#include <sapi.h>
#include <sphelper.h>

// CTTSDialog1Dlg dialog
class CTTSDialog1Dlg : public CDialogEx
{
private:
	CComPtr<ISpVoice> mp_voice_engine;
	char m_engine_flag = 0;
// Construction
public:
	CTTSDialog1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TTSDIALOG1_DIALOG };
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
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton1();
};
