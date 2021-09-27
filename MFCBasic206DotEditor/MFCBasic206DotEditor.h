
// MFCBasic206DotEditor.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic206DotEditorApp:
// See MFCBasic206DotEditor.cpp for the implementation of this class
//

class CMFCBasic206DotEditorApp : public CWinApp
{
public:
	CMFCBasic206DotEditorApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic206DotEditorApp theApp;
