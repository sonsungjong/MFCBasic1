
// MFCBasic225CEditViewView.h : interface of the CMFCBasic225CEditViewView class
//

#pragma once


class CMFCBasic225CEditViewView : public CEditView
{
protected: // create from serialization only
	CMFCBasic225CEditViewView() noexcept;
	DECLARE_DYNCREATE(CMFCBasic225CEditViewView)

// Attributes
public:
	CMFCBasic225CEditViewDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMFCBasic225CEditViewView();
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
};

#ifndef _DEBUG  // debug version in MFCBasic225CEditViewView.cpp
inline CMFCBasic225CEditViewDoc* CMFCBasic225CEditViewView::GetDocument() const
   { return reinterpret_cast<CMFCBasic225CEditViewDoc*>(m_pDocument); }
#endif

