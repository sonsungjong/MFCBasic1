#pragma once
//#include "afxdialogex.h"

// InputData dialog

class InputData : public CDialogEx
{
	DECLARE_DYNAMIC(InputData)
private:
	DCP m_dcp;
	CRect m_input_data_size;
	// struct QIMData;

public:
	InputData(CWnd* pParent = nullptr);   // standard constructor
	virtual ~InputData();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT_DATA_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedLoadFileBtn();
};
