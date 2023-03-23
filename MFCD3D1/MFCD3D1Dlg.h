
// MFCD3D1Dlg.h : header file
//

#pragma once
#include <d3d11.h>
//#include <d3dx11.h>
#include <d3dcompiler.h>
//#include <xnamath.h>

// CMFCD3D1Dlg dialog
class CMFCD3D1Dlg : public CDialogEx
{
private:
	ID3D11Device* pd3dDevice;
	ID3D11DeviceContext* pImmediateContext;
	IDXGISwapChain* pSwapChain;
	ID3D11RenderTargetView* pRenderTargetView;

// Construction
public:
	CMFCD3D1Dlg(CWnd* pParent = nullptr);	// standard constructor
	void Render();
	void Cleanup();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCD3D1_DIALOG };
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
