#ifndef ADD_ITEM_DLG_H_
#define ADD_ITEM_DLG_H_
#include "afxdialogex.h"

// AddItemDlg dialog

class AddItemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddItemDlg)
private:
	CImage m_item_image;				// ����� �������� �̹���
	CRect m_rect;							// ������ �̹����� ����� ����

	// �������� �ѱ��̸�, �����̸� �̹��� ���
	CString m_name_kor;
	CString m_name_eng;
	CString m_image_path;

	// ������ ����
	int m_price = 0;

public:
	AddItemDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AddItemDlg();

	// ��ϵ� �׸� ������ �����ϱ� ���� �Լ�
	void SetKidData(const TCHAR* ap_name_kor, const TCHAR* ap_name_eng, const TCHAR* ap_image_path, int a_price);
	const TCHAR* GetNameKor();
	const TCHAR* GetNameEng();
	const TCHAR* GetImagePath();
	int GetPrice();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD_ITEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedSelectImageBtn();
};
#endif