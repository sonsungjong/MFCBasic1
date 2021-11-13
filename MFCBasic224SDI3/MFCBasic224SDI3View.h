
// MFCBasic224SDI3View.h : interface of the CMFCBasic224SDI3View class
//

#pragma once


class CMFCBasic224SDI3View : public CFormView
{
protected: // create from serialization only
	CMFCBasic224SDI3View() noexcept;
	DECLARE_DYNCREATE(CMFCBasic224SDI3View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MFCBASIC224SDI3_FORM };
#endif

// Attributes
public:
	CMFCBasic224SDI3Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CMFCBasic224SDI3View();
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
	virtual void OnDraw(CDC* /*pDC*/);
};

#ifndef _DEBUG  // debug version in MFCBasic224SDI3View.cpp
inline CMFCBasic224SDI3Doc* CMFCBasic224SDI3View::GetDocument() const
   { return reinterpret_cast<CMFCBasic224SDI3Doc*>(m_pDocument); }
#endif

