
// MFCBasic225CEditViewDoc.cpp : implementation of the CMFCBasic225CEditViewDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCBasic225CEditView.h"
#endif

#include "MFCBasic225CEditViewDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCBasic225CEditViewDoc

IMPLEMENT_DYNCREATE(CMFCBasic225CEditViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCBasic225CEditViewDoc, CDocument)
END_MESSAGE_MAP()


// CMFCBasic225CEditViewDoc construction/destruction

CMFCBasic225CEditViewDoc::CMFCBasic225CEditViewDoc() noexcept
{
	// TODO: add one-time construction code here

}

CMFCBasic225CEditViewDoc::~CMFCBasic225CEditViewDoc()
{
}

// 새로만들기버튼
BOOL CMFCBasic225CEditViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	if (!m_viewList.IsEmpty())
	{
		// Document에서 View를 작업할 때
		reinterpret_cast<CEditView*>(m_viewList.GetHead())->SetWindowText(nullptr);
	}

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CMFCBasic225CEditViewDoc serialization
// 읽기 또는 저장하기
void CMFCBasic225CEditViewDoc::Serialize(CArchive& ar)		// CArchive클래스로 읽기 또는 저장
{
	// CEditView contains an edit control which handles all serialization
	if (!m_viewList.IsEmpty())
	{
		// Doc에서 View에 접근
		reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);
	}
#ifdef SHARED_HANDLERS

	if (m_viewList.IsEmpty() && ar.IsLoading())
	{
		CFile* pFile = ar.GetFile();
		pFile->Seek(0, FILE_BEGIN);
		ULONGLONG nFileSizeBytes = pFile->GetLength();
		ULONGLONG nFileSizeChars = nFileSizeBytes/sizeof(TCHAR);
		LPTSTR lpszText = (LPTSTR)malloc(((size_t)nFileSizeChars + 1) * sizeof(TCHAR));
		if (lpszText != nullptr)
		{
			ar.Read(lpszText, (UINT)nFileSizeBytes);
			lpszText[nFileSizeChars] = '\0';
			m_strThumbnailContent = lpszText;
			m_strSearchContent = lpszText;
		}
	}
#endif
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCBasic225CEditViewDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(m_strThumbnailContent, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFCBasic225CEditViewDoc::InitializeSearchContent()
{
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// Use the entire text file content as the search content.
	SetSearchContent(m_strSearchContent);
}

void CMFCBasic225CEditViewDoc::SetSearchContent(const CString& value)
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

// CMFCBasic225CEditViewDoc diagnostics

#ifdef _DEBUG
void CMFCBasic225CEditViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCBasic225CEditViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCBasic225CEditViewDoc commands
