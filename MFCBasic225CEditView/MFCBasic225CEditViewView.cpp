
// MFCBasic225CEditViewView.cpp : implementation of the CMFCBasic225CEditViewView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCBasic225CEditView.h"
#endif

#include "MFCBasic225CEditViewDoc.h"
#include "MFCBasic225CEditViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic225CEditViewView

IMPLEMENT_DYNCREATE(CMFCBasic225CEditViewView, CEditView)

BEGIN_MESSAGE_MAP(CMFCBasic225CEditViewView, CEditView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCBasic225CEditViewView construction/destruction

CMFCBasic225CEditViewView::CMFCBasic225CEditViewView() noexcept
{
	// TODO: add construction code here

}

CMFCBasic225CEditViewView::~CMFCBasic225CEditViewView()
{
}

BOOL CMFCBasic225CEditViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

void CMFCBasic225CEditViewView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCBasic225CEditViewView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCBasic225CEditViewView diagnostics

#ifdef _DEBUG
void CMFCBasic225CEditViewView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMFCBasic225CEditViewView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMFCBasic225CEditViewDoc* CMFCBasic225CEditViewView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCBasic225CEditViewDoc)));
	return (CMFCBasic225CEditViewDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCBasic225CEditViewView message handlers
