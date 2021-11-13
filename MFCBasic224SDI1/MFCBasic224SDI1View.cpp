
// MFCBasic224SDI1View.cpp : implementation of the CMFCBasic224SDI1View class
// Áß¾Ó Èò»öºÎºÐ

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCBasic224SDI1.h"
#endif

#include "MFCBasic224SDI1Doc.h"
#include "MFCBasic224SDI1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBasic224SDI1View

IMPLEMENT_DYNCREATE(CMFCBasic224SDI1View, CView)

BEGIN_MESSAGE_MAP(CMFCBasic224SDI1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCBasic224SDI1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCBasic224SDI1View construction/destruction

CMFCBasic224SDI1View::CMFCBasic224SDI1View() noexcept
{
	// TODO: add construction code here

}

CMFCBasic224SDI1View::~CMFCBasic224SDI1View()
{
}

BOOL CMFCBasic224SDI1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCBasic224SDI1View drawing
// == OnPaint
void CMFCBasic224SDI1View::OnDraw(CDC* pDC)
{
	CMFCBasic224SDI1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	pDC->Rectangle(10, 10, 100, 100);
}


// CMFCBasic224SDI1View printing


void CMFCBasic224SDI1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCBasic224SDI1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCBasic224SDI1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCBasic224SDI1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCBasic224SDI1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCBasic224SDI1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCBasic224SDI1View diagnostics

#ifdef _DEBUG
void CMFCBasic224SDI1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCBasic224SDI1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCBasic224SDI1Doc* CMFCBasic224SDI1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCBasic224SDI1Doc)));
	return (CMFCBasic224SDI1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCBasic224SDI1View message handlers

// == OnInitDialog
void CMFCBasic224SDI1View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
}
