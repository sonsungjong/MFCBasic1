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
	// D2D���� �׸��� �׸� Ŭ���̾�Ʈ ����
	ID2D1RenderTarget* mp_target;
	// Ÿ���� �׸� �귯�� �ּ�
	ID2D1SolidColorBrush* mp_green_brush = nullptr;

	// ���� �������� ���� ���� ������ �߽� ��ǥ �� ���� ȸ���ݰ�
	int m_degree = 0, m_x, m_y, m_rot_radius;
	// ���� �߽��� ��ġ�� �� �ִ� 720�� ��ǥ
	D2D1_POINT_2F m_circle_position[720];

// Construction
public:
	CDirectX02Dlg(CWnd* pParent = nullptr);	// standard constructor

	// COM���� ������ ��ü�� ����
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
