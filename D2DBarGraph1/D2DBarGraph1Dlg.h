#pragma once
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>


// CD2DBarGraph1Dlg dialog
class CD2DBarGraph1Dlg : public CDialogEx
{
private:
	ID2D1Factory* m_pD2DFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pBrush;

// Construction
public:
	CD2DBarGraph1Dlg(CWnd* pParent = nullptr);	// standard constructor

	void D2DRender();
	void D2DCleanup();
	void D2DBarGraph();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_D2DBARGRAPH1_DIALOG };
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
