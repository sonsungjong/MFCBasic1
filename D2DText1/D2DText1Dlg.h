
// D2DText1Dlg.h : header file
//

#pragma once
using namespace D2D1;

// CD2DText1Dlg dialog
class CD2DText1Dlg : public CDialogEx
{
// Construction
public:
	CD2DText1Dlg(CWnd* pParent = nullptr);	// standard constructor

	// COM ��ü ���� �Լ�
	template<class Interface>void __IRelease(Interface** ap_interface_object)
	{
		if (*ap_interface_object != nullptr) {
			(*ap_interface_object)->Release();
			(*ap_interface_object) = nullptr;
		}
	}

	void UserDraw();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_D2DTEXT1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	// D2D Factory
	ID2D1Factory* mp_factory = nullptr;
	// D2D ���ڿ� ���
	IDWriteFactory* mp_write_factory = nullptr;
	// D2D �׸� ��ü
	ID2D1RenderTarget* mp_target;
	// ���ڿ� ��½� ����� �۲�
	IDWriteTextFormat* mp_text_format = nullptr;

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	afx_msg void OnDestroy();
};
