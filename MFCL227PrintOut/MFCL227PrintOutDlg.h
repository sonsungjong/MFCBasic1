
// MFCL227PrintOutDlg.h : header file
//

#pragma once


// CMFCL227PrintOutDlg dialog
class CMFCL227PrintOutDlg : public CDialogEx
{
private:
	CFont m_title_font;
	CFont m_normal_font;

// Construction
public:
	CMFCL227PrintOutDlg(CWnd* pParent = nullptr);	// standard constructor
	// 시스템에 설치된 프린터 목록을 구성하는 함수
	void GetRegisteredPrinterList();
	// 현재 사용자가 선택한 프린터에서 드라이버 이름과 장치 이름을 얻는 함수
	void GetPrinterName(CString* ap_driver_name, CString* ap_device_name);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL227PRINTOUT_DIALOG };
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
	afx_msg void OnBnClickedTestBtn();
	CComboBox m_printer_list;
};
