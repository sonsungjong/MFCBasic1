#pragma once


// ������ ��ȭ���� (Popup)
// ���ҽ����� '���̾�α� ����' -> ���̾�α� ����Ŭ���Ͽ� Ŭ���� �߰�
// Visible : True
// ���� ���̾�α׿��� �����Ҵ����� ���

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
