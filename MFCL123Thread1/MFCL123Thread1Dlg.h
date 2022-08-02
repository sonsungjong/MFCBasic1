
// MFCL123Thread1Dlg.h: 헤더 파일
//

#pragma once
struct ThreadData
{
	CListBox* p_list_box;
	HANDLE h_kill_event;
	HANDLE h_thread;
};


// CMFCL123Thread1Dlg 대화 상자
class CMFCL123Thread1Dlg : public CDialogEx
{
private:
	ThreadData m_thread_data;
	//HANDLE mh_thread = NULL;
// 생성입니다.
public:
	CMFCL123Thread1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCL123THREAD1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CListBox m_data_list;
	afx_msg void OnBnClickedTestBtn();
	afx_msg void OnDestroy();
};
