
// MFCL123Thread1Dlg.h: 헤더 파일
//

#pragma once
struct ThreadData
{
	HWND h_wnd;
	unsigned int step;
	CListBox* p_list_box;
	HANDLE h_kill_event;
	HANDLE h_thread;
	DWORD thread_id;
};


// CMFCL123Thread1Dlg 대화 상자
class CMFCL123Thread1Dlg : public CDialogEx
{
private:
	
	//HANDLE mh_thread = NULL;
	unsigned int m_step = 20000;
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
	afx_msg void OnBnClickedStopBtn();
	afx_msg void OnBnClickedAllStopBtn();
	CListBox m_thread_list;
protected:
	afx_msg LRESULT On27001(WPARAM wParam, LPARAM lParam);
};
