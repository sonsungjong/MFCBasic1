
// MFCL225DCPclass.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL225DCPclassApp:
// See MFCL225DCPclass.cpp for the implementation of this class
//

class CMFCL225DCPclassApp : public CWinApp
{
public:
	CMFCL225DCPclassApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL225DCPclassApp theApp;
