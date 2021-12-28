#pragma once
#include <cmath>
#define PI			3.141592

using namespace D2D1;

// CDirectX02Dlg dialog
class CDirectX02Dlg : public CDialogEx
{
private:
	// D2D Factory
	ID2D1Factory* mp_factory = nullptr;
	// D2D에서 그림을 그릴 클라이언트 영역
	ID2D1RenderTarget* mp_target;
	// 타원을 그릴 브러시 주소
	ID2D1SolidColorBrush* mp_green_brush = nullptr;

	// 현재 진행중인 각과 현재 윈도우 중심 좌표 및 원의 회전반경
	int m_degree = 0, m_x, m_y, m_rot_radius;
	// 원의 중심이 위치할 수 있는 720개 좌표
	D2D1_POINT_2F m_circle_position[720];

// Construction
public:
	CDirectX02Dlg(CWnd* pParent = nullptr);	// standard constructor

	// COM으로 생성된 객체를 해제
	template<class Interface>
	void IRelease(Interface** ap_interface_object)
	{
		if (*ap_interface_object != nullptr) 
		{
			(*ap_interface_object)->Release();
			(*ap_interface_object) = nullptr;
		}
	}

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIRECTX02_DIALOG };
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
		};
