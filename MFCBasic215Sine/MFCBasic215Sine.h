
// MFCBasic215Sine.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic215SineApp:
// See MFCBasic215Sine.cpp for the implementation of this class
//

class CMFCBasic215SineApp : public CWinApp
{
public:
	CMFCBasic215SineApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic215SineApp theApp;
