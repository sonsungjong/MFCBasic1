
// MFCBasic105EditControl.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic105EditControlApp:
// See MFCBasic105EditControl.cpp for the implementation of this class
//

class CMFCBasic105EditControlApp : public CWinApp
{
public:
	CMFCBasic105EditControlApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic105EditControlApp theApp;
