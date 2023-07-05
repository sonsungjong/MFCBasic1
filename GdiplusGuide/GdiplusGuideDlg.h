
// GdiplusGuideDlg.h : header file
//

#pragma once
using namespace Gdiplus;
using namespace DllExports;

// CGdiplusGuideDlg dialog
class CGdiplusGuideDlg : public CDialogEx
{
private:
	// GDI+ 기본
	ULONG_PTR m_token;

	// GDI+ 윈도우 핸들 연결
	Gdiplus::GpBitmap* mp_bitmap = NULL;					// 출력 비트맵
	Gdiplus::GpGraphics* mp_graphics = NULL;				// 연결 후에는 dc 역할
	Gdiplus::GpPen* mp_pen = NULL;							// 펜
	Gdiplus::GpSolidFill* mp_brush = NULL;					// 브러시
	Gdiplus::GpImage* mp_image = NULL;					// 이미지

	// Memory DC 연결 -> GpBitmap 으로 변경
	//HDC mh_mem_dc = NULL;							// MemDC 핸들값
	//HBITMAP mh_mem_bmp = NULL;				// MemDC에 연결해서 사용할 비트맵 핸들값
	

// Construction
public:
	CGdiplusGuideDlg(CWnd* pParent = nullptr);	// standard constructor
	void SetMemDC();
	void DeleteMemDC();
	

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GDIPLUSGUIDE_DIALOG };
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
