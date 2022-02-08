
// D2DButton1Dlg.h : header file
//

#pragma once
using namespace D2D1;


// CD2DButton1Dlg dialog
class CD2DButton1Dlg : public CDialogEx
{
// Construction
public:
	CD2DButton1Dlg(CWnd* pParent = nullptr);	// standard constructor
	void UserDraw();
	// COM���� ������ ��ü�� �����ϴ� �Լ�
	template<class Interface> void __IRelease(Interface** ap_interface_object)
	{
		if (*ap_interface_object != nullptr) {
			(*ap_interface_object)->Release();
			(*ap_interface_object) = nullptr;
		}
	}

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_D2DBUTTON1_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	// D2D Factory
	ID2D1Factory* mp_factory = nullptr;
	// D2D ���ڿ� ����ϴ� Factory ��ü
	IDWriteFactory* mp_write_factory = nullptr;
	// D2D RenderTarget (�׸��׸��� ��ü)
	ID2D1RenderTarget* mp_target;
	// D2D Brush
	ID2D1SolidColorBrush* mp_user_brush = nullptr;
	// ���ڿ� ��½� ����� �۲� ����
	IDWriteTextFormat* mp_text_format = nullptr;

	// ��ư�� �ؽ�Ʈ ���� ( 0: �ȴ���, 1: ����)
	D2D1_COLOR_F m_text_color[2] = {
		{0.35f, 0.85f, 1.0f, 1.0f},
		{0.75f, 0.95f, 1.0f, 1.0f}
	};									// RGBA
	// ��ư�� �׵θ� ���� ( 0: �ȴ���, 1: ����)
	D2D1_COLOR_F m_btn_border_color[2] = {
		{0.2f, 0.7f, 0.9f, 1.0f},
		{0.6f, 0.9f, 0.95f, 1.0f}
	};									// RGBA

	// ��ư ��ġ ���� (3�� �������)
	D2D1_RECT_F m_btn_rect[3] = {
		{30.0f, 30.0f, 180.0f, 75.0f},
		{210.0f, 30.0f, 360.0f, 75.0f},
		{390.0f, 30.0f, 540.0f, 75.0f}
	};

	// ��ư�� ���� ���� üũ
	UINT8 m_btn_state[3] = { 0, 0, 0 };
	// ���� ���õ� ��ư�� �ε��� ��
	UINT8 m_selected_btn = 0xFF;

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

	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	afx_msg LRESULT On27000(WPARAM wParam, LPARAM lParam);
};
