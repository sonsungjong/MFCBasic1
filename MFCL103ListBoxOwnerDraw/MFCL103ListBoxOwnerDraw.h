
// MFCL103ListBoxOwnerDraw.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCL103ListBoxOwnerDrawApp:
// See MFCL103ListBoxOwnerDraw.cpp for the implementation of this class
//

class CMFCL103ListBoxOwnerDrawApp : public CWinApp
{
public:
	CMFCL103ListBoxOwnerDrawApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCL103ListBoxOwnerDrawApp theApp;
