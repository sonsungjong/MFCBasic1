
// MFCL201Menu.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL201MenuApp:
// See MFCL201Menu.cpp for the implementation of this class
//

class CMFCL201MenuApp : public CWinApp
{
public:
	CMFCL201MenuApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL201MenuApp theApp;
