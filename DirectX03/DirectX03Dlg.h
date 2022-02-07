
// DirectX03Dlg.h : header file
//

#pragma once
#include <math.h>
#define COVT_RADIAN		0.0174532888				// PI/180

using namespace D2D1;

// CDirectX03Dlg dialog
class CDirectX03Dlg : public CDialogEx
{
protected:
	// D2D Factory
	ID2D1Factory* mp_factory = nullptr;
	// D2D Render
	ID2D1RenderTarget* mp_target;
	// D2D Brush
	ID2D1SolidColorBrush* mp_user_brush = nullptr;
	// 점선
	ID2D1StrokeStyle* mp_stroke_style = nullptr;

	// 현재 위치와 중심좌표를 기억할 변수
	int m_degree = 0, m_x, m_y;
	
// Construction
public:
	CDirectX03Dlg(CWnd* pParent = nullptr);	// standard constructor
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
	enum { IDD = IDD_DIRECTX03_DIALOG };
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
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedOk();
};
