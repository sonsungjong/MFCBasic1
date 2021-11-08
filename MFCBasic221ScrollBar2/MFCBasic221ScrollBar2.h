
// MFCBasic221ScrollBar2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic221ScrollBar2App:
// See MFCBasic221ScrollBar2.cpp for the implementation of this class
//

class CMFCBasic221ScrollBar2App : public CWinApp
{
public:
	CMFCBasic221ScrollBar2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic221ScrollBar2App theApp;
