
// MFCBasic109ListControl.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic109ListControlApp:
// See MFCBasic109ListControl.cpp for the implementation of this class
//

class CMFCBasic109ListControlApp : public CWinApp
{
public:
	CMFCBasic109ListControlApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic109ListControlApp theApp;
