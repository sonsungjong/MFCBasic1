
// MFCBasic224SDI1Doc.cpp : implementation of the CMFCBasic224SDI1Doc class
// 파일 입출력을 담당하는 클래스

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCBasic224SDI1.h"
#endif

#include "MFCBasic224SDI1Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCBasic224SDI1Doc

IMPLEMENT_DYNCREATE(CMFCBasic224SDI1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCBasic224SDI1Doc, CDocument)
END_MESSAGE_MAP()


// CMFCBasic224SDI1Doc construction/destruction

CMFCBasic224SDI1Doc::CMFCBasic224SDI1Doc() noexcept
{
	// TODO: add one-time construction code here

}

CMFCBasic224SDI1Doc::~CMFCBasic224SDI1Doc()
{
}

BOOL CMFCBasic224SDI1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMFCBasic224SDI1Doc serialization
// 파일 입출력
void CMFCBasic224SDI1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		// 저장코드 추가
	}
	else
	{
		// TODO: add loading code here
		// 읽는코드 추가
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCBasic224SDI1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFCBasic224SDI1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCBasic224SDI1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCBasic224SDI1Doc diagnostics

#ifdef _DEBUG
void CMFCBasic224SDI1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCBasic224SDI1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCBasic224SDI1Doc commands
