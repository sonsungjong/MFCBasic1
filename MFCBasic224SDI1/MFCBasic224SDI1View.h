
// MFCBasic224SDI1View.h : interface of the CMFCBasic224SDI1View class
//

#pragma once


class CMFCBasic224SDI1View : public CView
{
protected: // create from serialization only
	CMFCBasic224SDI1View() noexcept;
	DECLARE_DYNCREATE(CMFCBasic224SDI1View)

// Attributes
public:
	CMFCBasic224SDI1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMFCBasic224SDI1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in MFCBasic224SDI1View.cpp
inline CMFCBasic224SDI1Doc* CMFCBasic224SDI1View::GetDocument() const
   { return reinterpret_cast<CMFCBasic224SDI1Doc*>(m_pDocument); }
#endif

