#pragma once
#include <d2d1.h>
#include <wincodec.h>
#pragma comment(lib, "D2D1.lib")
using namespace D2D1;

// Picture dialog

class __Picture : public CDialogEx
{
	DECLARE_DYNAMIC(__Picture)

	ID2D1Factory* mp_factory;
	ID2D1HwndRenderTarget* mp_render_target;
	ID2D1Bitmap* mp_bitmap;
	D2D1_RECT_F m_image_rect;

public:
	__Picture(CWnd* pParent = nullptr);   // standard constructor
	virtual ~__Picture();

	int LoadMyImage(ID2D1RenderTarget* ap_target, const TCHAR* ap_path);
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INNER1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
};
