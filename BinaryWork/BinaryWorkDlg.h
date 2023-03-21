#pragma once
#include "BinDataList.h"

// CBinaryWorkDlg dialog
class CBinaryWorkDlg : public CDialogEx
{
private:
	BinDataListBox m_bin_list;
	UINT8* mp_file_data = NULL;
	UINT32 m_file_size = 0;

// Construction
public:
	CBinaryWorkDlg(CWnd* pParent = nullptr);	// standard constructor

	// 한줄 정보 구성
	BDF* MakeOneLineData(int a_index, int a_data_size, UINT8* ap_bin_data);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BINARYWORK_DIALOG };
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
