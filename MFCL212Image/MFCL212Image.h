
// MFCL212Image.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL212ImageApp:
// See MFCL212Image.cpp for the implementation of this class
//

class CMFCL212ImageApp : public CWinApp
{
public:
	CMFCL212ImageApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL212ImageApp theApp;
