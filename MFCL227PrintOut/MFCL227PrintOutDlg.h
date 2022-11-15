
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
	// �ý��ۿ� ��ġ�� ������ ����� �����ϴ� �Լ�
	void GetRegisteredPrinterList();
	// ���� ����ڰ� ������ �����Ϳ��� ����̹� �̸��� ��ġ �̸��� ��� �Լ�
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
