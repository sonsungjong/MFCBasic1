
// DirectX05Dlg.h : header file
//

#pragma once
using namespace D2D1;

// CDirectX05Dlg dialog
class CDirectX05Dlg : public CDialogEx
{
protected:
	// D2D Factory
	ID2D1Factory* mp_factory = nullptr;
	// D2D Render
	ID2D1RenderTarget* mp_target;
	// D2D Brush
	ID2D1SolidColorBrush* mp_user_brush = nullptr;
	// D2D 수평, 수직 점선
	ID2D1StrokeStyle* mp_stroke_style = nullptr;
	// D2D 기하도형
	ID2D1PathGeometry* mp_geometry = nullptr;

	// 현재 진행중인 위치와 중심좌표를 저장할 변수
	int m_degree = 0;
	int m_x, m_y;

// Construction
public:
	CDirectX05Dlg(CWnd* pParent = nullptr);	// standard constructor

	// COM으로 생성된 객체를 해제하는 함수
	template<class Interface> void __IRelease(Interface** ap_interface_object)
	{
		if (*ap_interface_object != nullptr) {
			(*ap_interface_object)->Release();
			(*ap_interface_object) = nullptr;
		}
	}

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIRECTX05_DIALOG };
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

	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
