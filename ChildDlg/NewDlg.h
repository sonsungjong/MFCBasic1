#pragma once


// 비정형 대화상자 (Popup)
// 리소스에서 '다이얼로그 삽입' -> 다이얼로그 더블클릭하여 클래스 추가
// Visible : True
// 메인 다이얼로그에서 동적할당으로 사용

class NewDlg : public CDialogEx
{
	DECLARE_DYNAMIC(NewDlg)

public:
	NewDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~NewDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEW_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
protected:
	afx_msg LRESULT On33001(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On33002(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT On33003(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedSendSecret();
};
