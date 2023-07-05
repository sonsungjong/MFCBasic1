
// GdiplusGuideDlg.h : header file
//

#pragma once
using namespace Gdiplus;
using namespace DllExports;

// CGdiplusGuideDlg dialog
class CGdiplusGuideDlg : public CDialogEx
{
private:
	// GDI+ �⺻
	ULONG_PTR m_token;

	// GDI+ ������ �ڵ� ����
	Gdiplus::GpBitmap* mp_bitmap = NULL;					// ��� ��Ʈ��
	Gdiplus::GpGraphics* mp_graphics = NULL;				// ���� �Ŀ��� dc ����
	Gdiplus::GpPen* mp_pen = NULL;							// ��
	Gdiplus::GpSolidFill* mp_brush = NULL;					// �귯��
	Gdiplus::GpImage* mp_image = NULL;					// �̹���

	// Memory DC ���� -> GpBitmap ���� ����
	//HDC mh_mem_dc = NULL;							// MemDC �ڵ鰪
	//HBITMAP mh_mem_bmp = NULL;				// MemDC�� �����ؼ� ����� ��Ʈ�� �ڵ鰪
	

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
