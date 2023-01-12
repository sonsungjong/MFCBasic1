#pragma once

// ������ ��ȭ���� (Inner)
// ���ҽ����� '���̾�α� ����' -> ���̾�α� ����Ŭ���Ͽ� Ŭ���� �߰�
// Visible : True, Style : Child, Border : None
// ���� ���̾�α׿��� �����Ҵ����� ���

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
