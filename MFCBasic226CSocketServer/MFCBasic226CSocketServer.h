
// MFCBasic226CSocketServer.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic226CSocketServerApp:
// See MFCBasic226CSocketServer.cpp for the implementation of this class
//

class CMFCBasic226CSocketServerApp : public CWinApp
{
public:
	CMFCBasic226CSocketServerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic226CSocketServerApp theApp;
