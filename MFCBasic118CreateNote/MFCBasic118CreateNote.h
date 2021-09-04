
// MFCBasic118CreateNote.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic118CreateNoteApp:
// See MFCBasic118CreateNote.cpp for the implementation of this class
//

class CMFCBasic118CreateNoteApp : public CWinApp
{
public:
	CMFCBasic118CreateNoteApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic118CreateNoteApp theApp;
