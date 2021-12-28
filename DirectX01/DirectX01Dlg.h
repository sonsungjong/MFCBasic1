
// DirectX01Dlg.h : header file
//

#pragma once
using namespace D2D1;

// CDirectX01Dlg dialog
class CDirectX01Dlg : public CDialogEx
{
private:
	// D2D ���� ��ü�� �����ϴ� Factory
	ID2D1Factory* mp_factory = nullptr;
	// D2D���� ������ Ŭ���̾�Ʈ ������ �׸��� �׸� ��ü
	ID2D1RenderTarget* mp_target;

// Construction
public:
	CDirectX01Dlg(CWnd* pParent = nullptr);	// standard constructor

	// COM���� ������ ��ü�� ����
	template<class Interface> void IRelease(Interface** ap_interface_object)
	{
		if (*ap_interface_object != nullptr) {
			(*ap_interface_object)->Release();
			(*ap_interface_object) = nullptr;
		}
	}

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIRECTX01_DIALOG };
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
