
// DirectX04Dlg.h : header file
//

#pragma once
#include <cmath>
#define COVT_RADIAN			0.0174532888			// (PI/180)
using namespace D2D1;

// CDirectX04Dlg dialog
class CDirectX04Dlg : public CDialogEx
{
protected:
	// D2D 팩토리
	ID2D1Factory* mp_factory = nullptr;
	// D2D 랜더
	ID2D1RenderTarget* mp_target;
	// D2D 브러시
	ID2D1SolidColorBrush* mp_user_brush = nullptr;
	// D2D 선
	ID2D1StrokeStyle* mp_stroke_style = nullptr;
	// 현재 위치와 중심좌표를 저장할 변수
	int m_degree = 0;
	int m_x, m_y;

// Construction
public:
	CDirectX04Dlg(CWnd* pParent = nullptr);	// standard constructor
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
	enum { IDD = IDD_DIRECTX04_DIALOG };
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
