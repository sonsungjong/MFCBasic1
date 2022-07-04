
// MFCL122Hooking.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL122HookingApp:
// See MFCL122Hooking.cpp for the implementation of this class
//

class CMFCL122HookingApp : public CWinApp
{
public:
	CMFCL122HookingApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL122HookingApp theApp;
