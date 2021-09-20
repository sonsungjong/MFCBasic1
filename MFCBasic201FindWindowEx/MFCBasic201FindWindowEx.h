
// MFCBasic201FindWindowEx.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic201FindWindowExApp:
// See MFCBasic201FindWindowEx.cpp for the implementation of this class
//

class CMFCBasic201FindWindowExApp : public CWinApp
{
public:
	CMFCBasic201FindWindowExApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic201FindWindowExApp theApp;
