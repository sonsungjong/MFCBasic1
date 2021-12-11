
// MFCL104ListBoxOwnerDrawLib.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL104ListBoxOwnerDrawLibApp:
// See MFCL104ListBoxOwnerDrawLib.cpp for the implementation of this class
//

class CMFCL104ListBoxOwnerDrawLibApp : public CWinApp
{
public:
	CMFCL104ListBoxOwnerDrawLibApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL104ListBoxOwnerDrawLibApp theApp;
