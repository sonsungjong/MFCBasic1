
// MFCBasic226CSocketClient.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic226CSocketClientApp:
// See MFCBasic226CSocketClient.cpp for the implementation of this class
//

class CMFCBasic226CSocketClientApp : public CWinApp
{
public:
	CMFCBasic226CSocketClientApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic226CSocketClientApp theApp;
