#pragma once

// 비정형 대화상자 (Inner)
// 리소스에서 '다이얼로그 삽입' -> 다이얼로그 더블클릭하여 클래스 추가
// Visible : True, Style : Child, Border : None
// 메인 다이얼로그에서 동적할당으로 사용

class NewChild : public CDialogEx
{
	DECLARE_DYNAMIC(NewChild)

public:
	NewChild(CWnd* pParent = nullptr);   // standard constructor
	virtual ~NewChild();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEW_CHILD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedSendBtn();
	afx_msg void OnBnClickedTap1();
	afx_msg void OnBnClickedTap2();
	afx_msg void OnBnClickedTap3();
};
