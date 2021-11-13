
// MFCBasic224SDI3View.cpp : implementation of the CMFCBasic224SDI3View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCBasic224SDI3.h"
#endif

#include "MFCBasic224SDI3Doc.h"
#include "MFCBasic224SDI3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic224SDI3View

IMPLEMENT_DYNCREATE(CMFCBasic224SDI3View, CFormView)

BEGIN_MESSAGE_MAP(CMFCBasic224SDI3View, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCBasic224SDI3View construction/destruction

CMFCBasic224SDI3View::CMFCBasic224SDI3View() noexcept
	: CFormView(IDD_MFCBASIC224SDI3_FORM)
{
	// TODO: add construction code here

}

CMFCBasic224SDI3View::~CMFCBasic224SDI3View()
{
}

void CMFCBasic224SDI3View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CMFCBasic224SDI3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CMFCBasic224SDI3View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

void CMFCBasic224SDI3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCBasic224SDI3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCBasic224SDI3View diagnostics

#ifdef _DEBUG
void CMFCBasic224SDI3View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCBasic224SDI3View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCBasic224SDI3Doc* CMFCBasic224SDI3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCBasic224SDI3Doc)));
	return (CMFCBasic224SDI3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCBasic224SDI3View message handlers


void CMFCBasic224SDI3View::OnDraw(CDC* pDC)
{
	// TODO: Add your specialized code here and/or call the base class
	pDC->Rectangle(0, 0, 100, 100);
}
