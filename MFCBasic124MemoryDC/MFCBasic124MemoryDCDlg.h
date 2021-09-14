
// MFCBasic124MemoryDCDlg.h : header file
//

#pragma once

#define MAX_COUNT				100

struct Circle
{
	int x, y, r;
	COLORREF color;
};

class _MemoryDC
{
protected:
	CDC m_memDC;
	CBitmap m_memBmp;
	int m_width;
	int m_height;

public:
	_MemoryDC() 
	{
		m_width = 0;
		m_height = 0;
	}
	~_MemoryDC()
	{
		if (m_memDC.m_hDC != NULL) {
			m_memBmp.DeleteObject();
			m_memDC.DeleteDC();
		}
	}

	void _CreateDC(CWnd* ap_wnd, int a_width, int a_height) {
		CClientDC dc(ap_wnd);
		m_width = a_width;
		m_height = a_height;
		m_memDC.CreateCompatibleDC(&dc);
		m_memBmp.CreateCompatibleBitmap(&dc, a_width, a_height);
		m_memDC.SelectObject(&m_memBmp);
	}
	void Resize(CWnd* ap_wnd, int a_width, int a_height)
	{
		m_memBmp.DeleteObject();
		m_width = a_width;
		m_height = a_height;
		CClientDC dc(ap_wnd);
		m_memBmp.CreateCompatibleBitmap(&dc, m_width, m_height);
		m_memDC.SelectObject(&m_memBmp);
	}

	inline CDC* GetDC()			// 자주쓰니깐 inline써서 스택프레임 없애기
	{
		return &m_memDC;
	}
	inline int GetWidth()
	{
		return m_width;
	}
	inline int GetHeight()
	{
		return m_height;
	}
};

// CMFCBasic124MemoryDCDlg dialog
class CMFCBasic124MemoryDCDlg : public CDialogEx
{
protected:
	int w, h, minR, maxR;
	Circle m_circleList[MAX_COUNT];
	Circle* mp;
	CRect r;
	CBrush fill_brush;
	CBrush* p_oldBrush;
	CDC m_mem_dc;
	CBitmap m_mem_bmp;

// Construction
public:
	CMFCBasic124MemoryDCDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCBASIC124MEMORYDC_DIALOG };
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
