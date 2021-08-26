
// MFCBasic113ALPHA.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic113ALPHAApp:
// See MFCBasic113ALPHA.cpp for the implementation of this class
//

class CMFCBasic113ALPHAApp : public CWinApp
{
public:
	CMFCBasic113ALPHAApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic113ALPHAApp theApp;
