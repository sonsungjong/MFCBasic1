
// MFCBasic203ImageWindow.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic203ImageWindowApp:
// See MFCBasic203ImageWindow.cpp for the implementation of this class
//

class CMFCBasic203ImageWindowApp : public CWinApp
{
public:
	CMFCBasic203ImageWindowApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic203ImageWindowApp theApp;
