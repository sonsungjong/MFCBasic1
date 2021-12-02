
// MFCBasic227CSocketClient.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic227CSocketClientApp:
// See MFCBasic227CSocketClient.cpp for the implementation of this class
//

class CMFCBasic227CSocketClientApp : public CWinApp
{
public:
	CMFCBasic227CSocketClientApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic227CSocketClientApp theApp;
