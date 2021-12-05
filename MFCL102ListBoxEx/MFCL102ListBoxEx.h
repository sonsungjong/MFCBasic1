
// MFCL102ListBoxEx.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL102ListBoxExApp:
// See MFCL102ListBoxEx.cpp for the implementation of this class
//

class CMFCL102ListBoxExApp : public CWinApp
{
public:
	CMFCL102ListBoxExApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL102ListBoxExApp theApp;
