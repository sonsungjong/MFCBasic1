
// MFCBasic122Timer.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCBasic122TimerApp:
// See MFCBasic122Timer.cpp for the implementation of this class
//

class CMFCBasic122TimerApp : public CWinApp
{
public:
	CMFCBasic122TimerApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCBasic122TimerApp theApp;
